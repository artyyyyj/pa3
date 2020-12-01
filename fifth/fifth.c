#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long power(long num, long times)
{
	long i = num;
	long result = num;

	if (times == 0)
	return 1;

	for (int x = 0; x < times-1; x++)
	{
		result = result*i;
	}
	
	return result;
}

int findLengthBinary(long num)
{
	if (num == 0 || num==1)
		return 1;

	int count = 0;

	while(num != 0)
	{
		num = num/2;
		count++;
	}

	return count;
}

int findLengthFraction(double num)
{
	if (num == 0)
		return 1;

	int count = 0;

	while (num < 1)
	{
		num = num*2;
		count++;
	}
	return count;
}
long* convertExp(long x, int expBits)
{
	if (x == 0)
	{
		long* arr = malloc(expBits *sizeof(long));
		for(int x = 0; x < expBits; x++)
		{
			arr[x] = 0;
		}	
		
		return arr;
	}

	if (x == 1)
	{
		long* arr = malloc(expBits*sizeof(long));
		for (int x = 0; x < expBits; x++)
		{
			arr[x] = 0;
		}	
		arr[expBits-1] = 1;

		return arr;
	}
	//int difference = expBits - findLengthBinary(x);	
	// int length = findLengthBinary(x) + difference;
	long* arr = malloc(expBits * sizeof(long));
	long count = expBits - 1;

	for (long x = 0; x < expBits; x++)
	{
		arr[x] = 0;
	}

	while (x != 0)
	{
		arr[count] = x % 2;
		x = x/2;
		count--;	
	}
	/*	
	printf("exponent : ");
	for (int x = 0; x < length; x++)
	{
		printf("%ld", arr[x]);
	}
	printf("\n"); */	
	return arr;
}

long* convert(long x)
{
	if (x == 0)
	{
		long* arr = malloc(sizeof(long));
		arr[0] = 0;
		return arr;
	}

	if (x == 1)
	{
		long* arr = malloc(sizeof(long));
		arr[0] = 1;
		return arr;
	}
	
	int length = findLengthBinary(x);
	long* arr = malloc(length * sizeof(long));
	long count = length - 1;

	for (long x = 0; x < length; x++)
	{
		arr[x] = 0;
	}

	while (x != 0)
	{
		arr[count] = x % 2;
		x = x/2;
		count--;	
	}
		
	return arr;
}

long* convertFraction(double fraction, int size)
{
	int length = size;
	long* arr = malloc(length * sizeof(long));

	for (int x = 0; x < length; x++)
	{
		arr[x] = 0;
	}

	for (int x = 0; x < length; x++)
	{
		fraction = fraction * 2;
		int temp = floor(fraction);
		if (temp <= 1)
		{
			arr[x] = temp;
		}
		fraction = fraction - temp;
	}	
	return arr;	
}

long* combine(long binary, double fraction, int size)
{
	long* p1 = convert(binary);
	long* p2 = convertFraction(fraction, size);	
	int l1 =  findLengthBinary(binary);
	int l2 = size;
/*
	printf("p1 is : ");
	for (int x = 0; x < l1; x++)
	{
		printf("%ld", p1[x]);
	}
	printf("\n");
	printf("p2 is : ");
	for (int x = 0; x < l2; x++)
	{
		printf("%ld", p2[x]);
	}
	printf("\n");
	*/
	int length = l1 + l2;
	long* arr = malloc(length * sizeof(long));
	for (int x = 0; x < length; x++)
	{
		arr[x] = 0;
	}
	for(int x = 0; x < l1; x++)
	{
		arr[x] = p1[x];
	}
	int count = 0;
	for(int x = l1; x < (l1 + l2); x++)
	{
		arr[x] = p2[count];
		count++;
	}

	free(p1);
	free(p2);
/*	
	printf("combined is : ");
	for (int x = 0; x < length; x++)
	{
		printf("%ld", arr[x]);
	}
	printf("\n");*/
	
	return arr;
}

long* makeExp(int n, int e, int expBits)
{
	int bias = power(2, n-1) - 1;
	int sum = e + bias;
	long* arr = convertExp(sum, expBits);
	return arr;
}

double convertDecimal(long* arr, int n)
{
	double result = 0;

	int count = 1;	
	for (int x = 0; x < n; x++)
	{
		if (arr[x] == 1)
		{
			double temp = 1.0/power(2, count);
			result += temp;
		}
		count++;
	}
	return result;
}

// returns 0 if regular, 1 for the special case
int roundingCheck(long* limitedF, long* fullF, int n)
{
	int allOne = 1;
	for (int x = 0; x < n; x++)
	{
		if (limitedF[x] == 0)
			allOne = 0;
	}
	//printf("all one is %d\n", allOne);	
	long* upperarr = malloc(n*sizeof(long));
	long* lowerarr = malloc(n*sizeof(long));
	for (int x = 0; x < n; x++)
	{
		upperarr[x] = limitedF[x];
		lowerarr[x] = limitedF[x];
	}	
	
	if (limitedF[n-1] == 0)
		upperarr[n-1] = 1;

	else
	{
		if (allOne == 1)
		{
			for (int x = 0; x < n; x++)
			{
				upperarr[x] = 0;
			}
		}
		else
		{
		int count = n - 1;
		while (limitedF[count] != 0)
		{
			upperarr[count] = 0;
			count--;
		}
		upperarr[count] = 1;
		}
	}
	
	double upper = convertDecimal(upperarr, n);
	if (allOne == 1)
		upper = 1.0;	
	double val = convertDecimal(fullF, 52);
	double lower = convertDecimal(lowerarr, n);
	double midpoint = (upper + lower)/2;
	//printf("upper: %lf value: %lf lower: %lf midpoint: %lf\n", upper, val, lower, midpoint);	
	if (val < midpoint)
	{
		free(upperarr);
	/*	printf("lower returned: ");
		for (int x = 0; x < n; x++)
		{
			printf("%ld", lowerarr[x]);
		}
		printf("\n");*/
		free(lowerarr);
		return 0;
	}
	
	else if (val > midpoint)
	{
		free(lowerarr);
		/*printf("upper returned : ");
		for (int x = 0; x < n; x++)
		{
			printf("%ld", upperarr[x]);
		}
		printf("\n");*/
		free(upperarr);
		if (allOne == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	else // this is if TIED
	{
		//printf("tied\n");	
		if (lowerarr[n-1] == 0)
		{
			free(upperarr);
			free(lowerarr);
			return 0;
		}
		else
		{
			free(lowerarr);
			free(upperarr);
			if (allOne == 1)
				return 1;
			else
			{	
			return 0;
			}
		}
	}	
			
}


long* rounding(long* limitedF, long* fullF, int n)
{
	int allOne = 1;
	for (int x = 0; x < n; x++)
	{
		if (limitedF[x] == 0)
			allOne = 0;
	}
	
	long* upperarr = malloc(n*sizeof(long));
	long* lowerarr = malloc(n*sizeof(long));
	for (int x = 0; x < n; x++)
	{
		upperarr[x] = limitedF[x];
		lowerarr[x] = limitedF[x];
	}	
	
	if (limitedF[n-1] == 0)
		upperarr[n-1] = 1;

	else
	{
		if (allOne == 1)
		{
			for (int x = 0; x < n; x++)
			{
				upperarr[x] = 0;
			}
		}
		else
		{
		int count = n - 1;
		while (limitedF[count] != 0)
		{
			upperarr[count] = 0;
			count--;
		}
		upperarr[count] = 1;
		}
	}
	
	double upper = convertDecimal(upperarr, n);
	if (allOne == 1)
		upper = 1.0;	
	double val = convertDecimal(fullF, 52);
	double lower = convertDecimal(lowerarr, n);
	double midpoint = (upper + lower)/2;
	//printf("upper: %lf value: %lf lower: %lf midpoint: %lf\n", upper, val, lower, midpoint);	
	if (val < midpoint)
	{
		free(upperarr);
	/*	printf("lower returned: ");
		for (int x = 0; x < n; x++)
		{
			printf("%ld", lowerarr[x]);
		}
		printf("\n");*/
		return lowerarr;
	}
	
	else if (val > midpoint)
	{
		free(lowerarr);
		/*printf("upper returned : ");
		for (int x = 0; x < n; x++)
		{
			printf("%ld", upperarr[x]);
		}
		printf("\n");*/
		return upperarr;
	}
	
	else // this is if TIED
	{
		//printf("tied\n");	
		if (lowerarr[n-1] == 0)
		{
			free(upperarr);
			return lowerarr;
		}
		else
		{
			free(lowerarr);
			return upperarr;
		}
	}	
			
}


int main(int argc, char* argv[argc + 1])
{
	FILE* f1 = fopen(argv[1], "r");

	double num = 0;
	int totalBits = 0;
	int expBits = 0;
	int fBits = 0;	
	while (fscanf(f1, "%lf %d %d %d\n", &num, &totalBits, &expBits, &fBits) != EOF)
	{
		long temp = 0;	
		if (num < 0)
		{
			temp = floor(-1*num);
		}
		else
		temp = floor(num);		
		double fraction = num - temp;
		if (num < 0)
		{
			fraction = (-1*num) - temp;
		}
		//printf("fraction is %lf\n", fraction);
		long* f = combine(temp, fraction, 53);
		

	       	int e = findLengthBinary(temp) - 1;
		if (temp == 0)
		{
			for (int x = 0; x < 54; x++)
			{
				if (f[x] == 1)
				{
					e = -1 * x;
					break;
				}
			}
		}	
		

		long* exp = makeExp(expBits, e, expBits);	
		int length = findLengthBinary(temp) + 53 + findLengthBinary(temp) + findLengthBinary(power(2, fBits-1) -1 + findLengthBinary(temp) - 1);
		long* arr = malloc(length*sizeof(long));
		for (int x = 0; x < length; x++)
		{
			arr[x] = 0;
		}
			
		if (num < 0)
		{
			arr[0] = 1;
		}
		else
		{
			arr[0] = 0;
		}	
		int count = 1;	
		for (int x = 0; x < expBits; x++)
		{
			arr[count] = exp[x];
			count++;
		}
		int count2 = 1;
		if (temp == 0)
		{
			for (int x = 0; x < 53; x++)
			{
				if (f[x] == 1)
				{
					count2 = x+1;
					break;
				}
			}
		}	
		for (int x = 1 + expBits; x < totalBits; x++)
		{	
			arr[x] = f[count2];
			count2++;
		}
		
		// garbage begins	
		count2 = 1+expBits;	
		long* limitedF = malloc(fBits * sizeof(long));
		for (int x = 0; x < fBits; x++)
		{
			limitedF[x] = arr[count2];
			count2++;
		}	
		long* fullDecimal = malloc(52*sizeof(long));
		for (int x = 0; x < 52; x++)
		{
			fullDecimal[x] = 0;
		}
		int beginpoint = 1;
		if (temp == 0)
		{	
			beginpoint = (-1*e) + 1;
		}
	
		int pos = 0;
	
		for (int x = beginpoint; x<52; x++)
		{
			fullDecimal[pos] = f[x];
			pos++;
		}
			
		/*printf("fulldecimal : ");
		for(int x = 0; x < 52; x++)
		{
			printf("%ld", fullDecimal[x]);
		}
		printf("\n");*/
		long* newEnd = rounding(limitedF, fullDecimal, fBits);
		int allOne = roundingCheck(limitedF, fullDecimal, fBits);
		count2 = 1 + expBits;
		for (int x = 0; x < fBits; x++)
		{
			arr[count2] = newEnd[x];
			count2++;
		}	
		
		//printf("all one is %d \n", allOne);	
		if (allOne == 1)
		{
		     int count = expBits;
	             while (arr[count] != 0)
		     {
		         arr[count] = 0;
		         count--;
		     }
	     		arr[count] = 1;	     
		}		     
			
		for (int x = 0; x < totalBits; x++)
		{
			printf("%ld", arr[x]);
		}
		printf("\n");		
		free(arr);
		free(exp);
		free(f);
		free(limitedF);
		free(fullDecimal);
		free(newEnd);
	}
	return EXIT_SUCCESS;

}

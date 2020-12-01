#include <stdio.h>
#include <stdlib.h>

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
		int temp = (int) fraction;
		if (temp <= 1)
		{
			arr[x] = temp;
		}

		fraction = fraction -temp;

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
	printf("\n");
	*/
	return arr;
}

int main(int argc, char* argv[argc + 1])
{
	FILE* f1 = fopen(argv[1], "r");

	
	double num = 0;
	long size = 0;

	while (fscanf(f1, "%lf %ld\n", &num, &size) != EOF)
	{
		long temp = (long) num;
		double fraction = num - temp;	
		long* arr = combine(temp, fraction, size+1);
		int l1 =  findLengthBinary(temp);
		int l2 = size + 1;	
		int length = l1+l2;

		if (temp == 0)
		{
			int count = 0;
			for (int x = 0; x < length; x++)
			{
				if (arr[x] == 1)
				{
					count = x;
					break;
				}
			}
			
			int f = 0; 
			for (int x = count; x < length && f<size; x++)
			{
				printf("%ld" , arr[x]);
				if (x == count)
				printf(".");

				f++;
			}
			
			while (f < size+1)
			{
				printf("0");
				f++;
			}

			printf(" %d\n", -1*count);
				
		}

		else
		{
		printf("1.");
		int count = 0;		       
		for (int x = 1; x < length && count < size; x++)
		{
			printf("%ld", arr[x]);
			count++;
		}
		
		while (count < size)
		{
			printf("0");
			count++;
		}
		
		int e = findLengthBinary(temp) - 1;
		printf(" %d\n", e);
		}	
		free(arr);
	}
/*	long* f = convert(6);
	for (int x = 0; x < 3; x++)
	{
		printf("%ld", f[x]);
	}
	printf("\n");
	*/
	
	return EXIT_SUCCESS;
}

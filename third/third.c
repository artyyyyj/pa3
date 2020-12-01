#include <stdlib.h>
#include <stdio.h>

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

long* convertPositive(long num, long w)
{	
	long* arr = malloc(w * sizeof(long));

	for (int x = 0; x < w; x++)
	{
		arr[x] = 0;
	}

	long temp = power(2, w-1) - 1;

	if (num >= temp)
	{
		for (int x = 1; x < w; x++)
		{
			arr[x] = 1;
		}
		return arr;
	}
	
	long count = w - 1;
	long entered = 0;

	while (num != 0 && entered < w)
	{
		arr[count] = num % 2;
		num = num/2;
		count--;
		entered++;
	}

	arr[0] = 0;
	return arr;
}


long* convertNegative(long num, long w)
{
	long* arr = malloc(w * sizeof(long));
	
	for(int x = 0; x < w; x++)
	{
		arr[x] = 0;
	}
	arr[0] = 1;

	int f = w -1;
	long temp = power(2, f);

	if (-1*num >= temp)
	{
		return arr;
	}		

	num = temp - (-1 *num);

	long count = w -1;
	long entered = 0;

	while (num != 0 && entered < w)
	{
		arr[count] = num%2;
		num = num/2;
		count--;
		entered++;
	}

	arr[0] = 1;
	return arr;

}



long* makeU(long num, long w)
{
	long* arr = malloc(w * sizeof(long));
	long count = w - 1;
	long entered = 0;

	for (long x = 0; x < w; x++)
	{
		arr[x] = 0;
	}

	while (num != 0 && entered < w)
	{
		arr[count] = num % 2;
		num = num/2;
		count--;
		entered++;	
	}
	
	return arr;

}

long* makeS(long num, long w)
{
	long* arr = 0;
	if (num > 0)
	{
		arr = convertPositive(num, w);
	}
	
	else
	arr = convertNegative(num, w);

	return arr;	
}

long readasS(long* arr, long w)
{
	long result = 0;

	if (arr[0] == 0)
	{
		int count = 0;
		for (int x = w-1; x >= 1; x--)
		{
			if (arr[x] == 1)
			{
				result += power(2, count);
			}
			count++;
		}
		free(arr);
		return result;
	}

	result = -1*power(2, w-1);

	int count = 0;
	for (int x = w-1; x >= 1; x--)
	{
		if (arr[x] == 1)
		{
			result += power(2, count);
		}
		count++;
	}
	free(arr);
	return result;
}



long readasU(long* arr, long w)
{
	int count = 0;
	long result = 0;

	/*
	for (int x = 0; x < w; x++)
	{
		printf("%ld", arr[x]);
	}
	
	printf("\n");
	*/

	for (int x = w-1; x >= 0; x--)
	{
		if(arr[x] == 1)
		{	
			result += power(2, count);
		}
		count++;
	}

	free(arr);
	return result;
}	

int main(int argc, char* argv[argc + 1])
{
	FILE* f1 = fopen(argv[1], "r");

	long num = 0;
	long w = 0;
	char i = 0;
	char o = 0;

	while (fscanf(f1, "%ld %ld %c %c\n", &num, &w, &i, &o) != EOF)
	{
		if (i == 's')
		printf("%ld\n", readasU(makeS(num, w), w));

		else
		printf("%ld\n", readasS(makeU(num, w), w)); 	
	}

	return EXIT_SUCCESS;
}

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


int main(int argc, char* argv[argc + 1])
{
		
/*	long* arr = convertPositive(16, 4);
	for (int x = 0; x < 4; x++)
	{
		printf("%ld", arr[x]);
	}
	printf("\n"); */

	FILE* f1 = fopen(argv[1], "r");
	long num = 0;
	long w = 0;

	while(fscanf(f1, "%ld %ld\n", &num, &w) != EOF)
	{
		long* arr = 0;

		if (num < 0)
		{
			arr = convertNegative(num, w);
		}

		else
		{
			arr = convertPositive(num, w);
		}

		for (int x = 0; x < w; x++)
		{
			printf("%ld", arr[x]);
		}
		free(arr);
		printf("\n");	

	}

	return EXIT_SUCCESS;
}

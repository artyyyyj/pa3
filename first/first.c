#include <stdlib.h>
#include <stdio.h>


long* convert(long x, long bits)
{
	long* arr = malloc(bits * sizeof(long));
	long count = bits - 1;
	long entered = 0;

	for (long x = 0; x < bits; x++)
	{
		arr[x] = 0;
	}

	while (x != 0 && entered < bits)
	{
		arr[count] = x % 2;
		x = x/2;
		count--;
		entered++;	
	}
	
	return arr;
}


int main(int argc, char* argv[argc + 1])
{
	FILE* f1 = fopen(argv[1], "r");

	long num = 0;
	long w = 0;

	while (fscanf(f1, "%ld %ld\n", &num, &w) != EOF)
	{	
		long* arr = convert(num, w);
	
		for (long x = 0; x < w; x++)
		{
			printf("%ld", arr[x]);
		}
		free(arr);
		printf("\n");
	}
	
	return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double findPower(long num, long times)
{
	if (num < 0)
	{
		num*=-1;
	}
	        double i = num;
		        double result = num;

			        if (times == 0)
					        return 1;

				        for (int x = 0; x < times-1; x++)
						        {
								                result = result*i;
										        }

					        return result;
}


long convertDecimal(long* arr, int n)
{
	double result = 0;

	int count = 0;	
	for (int x = n-1; x >= 0; x--)
	{
		if (arr[x] == 1)
		{
			double temp = findPower(2, count);
			result += temp;
		}
		count++;
	}
	return result;
}



long* binary(long x, long bits)
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
/*	
	printf("binary : ");
	for (int x = 0; x < bits; x++)
	{
		printf("%ld", arr[x]);
	}
	printf("\n");*/	
	return arr;
}


long* convert(char* arr, int n)
{
	//printf("n is %d\n", n);
	int length = n*4;
	//printf("length is %d\n", length);
	long* converted = malloc(length*sizeof(long));
	for (int x = 0; x < length; x++)
	{
		converted[x] = 0;
	}
	
	int count = 0;
	for (int x = 0; x < n; x++)
	{
		char temp = arr[x];
		long* tempBinary = 0;		
		switch(temp)
		{
			case '0':
			tempBinary = binary(0, 4);
			break;
			
			case '1':
			tempBinary = binary(1, 4);
			break;

			case '2':
			tempBinary = binary(2, 4);
			break;
			
			case '3':
			tempBinary = binary(3, 4);
			break;
			
			case '4':
			tempBinary = binary(4, 4);
			break;
			
			case '5':
			tempBinary = binary(5, 4);
			break;
		
			case '6':
			tempBinary = binary(6, 4);
			break;
			
			case '7': 
			tempBinary = binary(7, 4);
			break;
			
			case '8':
			tempBinary = binary(8, 4);
			break;
			
			case '9':
			tempBinary = binary(9, 4);
			break;
			
			case 'a':
			tempBinary = binary(10, 4);
			break;
			
			case 'b':
			tempBinary = binary(11, 4);
			break;
			
			case 'c':
			tempBinary = binary(12, 4);
			break;
			
			case 'd':
			tempBinary = binary(13, 4);
			break;
			
			case 'e':
			tempBinary = binary(14, 4);
			break;
			
			case 'f':
			tempBinary = binary(15, 4);
			break;
		}
		//printf("done with switch case\n");
		for (int x = 0; x < 4 && count < (n*4); x++)
		{
			converted[count] = tempBinary[x];
			count++;
		}
		free(tempBinary);
				
	}

	return converted;	
}

long* getieee(char* hex, int totalBits, int length)
{
	long* converted = convert(hex, length);
	long* arr = malloc(totalBits*sizeof(long));
	int count = (length*4) - 1;
	for (int x = totalBits-1; x >= 0; x--)
	{
		arr[x] = converted[count];
		count--;	
	}
/*	
	printf("total converted : ");
	for (int x = 0; x < length*4; x++)
	{
		printf("%ld", converted[x]);
	}
	printf("\n"); */
	/*printf("ieee : ");
	for(int x = 0; x < totalBits; x++)
	{
		printf("%ld", arr[x]);
	}
	printf("\n");
	*/


	free(converted);
	free(hex);
	return arr;
}

int findLength(char str[100])
{
	int count = 0;
		while (str[count] != '\0')
		{
			count++;
		}
	return count;
}

int main(int argc, char* argv[argc + 1])
{
	FILE* f = fopen(argv[1], "r");

	int totalBits = 0;
	int expBits = 0;
	int fBits = 0;
	char str[100];
	int prec = 0;
	while (fscanf(f, "%d %d %d %s %d\n", &totalBits, &expBits, &fBits, str, &prec) != EOF)
	{
		int count = findLength(str);
		char* hex = malloc((count-2) * sizeof(char));
		int temp = 2;
		for (int x = 0; x < count-2; x++)
		{
			hex[x] = str[temp];
			temp++;
		}
	//	printf("copied hex\n");
	/*	for (int x = 0; x < count -2; x++)
		{
			printf("%c", hex[x]);
		}
		printf("\n");*/
		long* ieee = getieee(hex, totalBits, count-2);	
		int bias = findPower(2, expBits - 1) - 1;
		//printf("bias is %d\n", bias);	
		// shift = exp - bias
		//printf("made ieee\n");	
		long* exp = malloc(expBits * sizeof(long));
		temp = 0;
		for (int x = 1; x < expBits +1; x++)
		{
			exp[temp] = ieee[x];
			temp++;
		}
			
		long expDecimal = convertDecimal(exp, expBits);
		
		//printf("exp is %ld\n", expDecimal);
		int shift = expDecimal - bias;
		//printf("shift is %d\n", shift);
		
		long* f = malloc(fBits * sizeof(long));
		int pos = expBits + 1;
	       	for (int x = 0; x < fBits; x++)
		{
			f[x] = ieee[pos];
			pos++;
		}
		//printf("fraction ");
		/*
		for (int x = 0; x < fBits; x++)
		{
			printf("%ld", f[x]);
		}
		printf("\n");
		*/
		double fractionPart = 0;
		int pow = 1;
		for(int x= 0; x < fBits; x++)
		{
			if (f[x] == 1)
			{
				double temp = 1.0/findPower(2, pow);
				//printf("temp is %lf\n", temp);
				fractionPart += temp;
			}
			pow++;	
		}
		
		
		int sign = 1;
		if (ieee[0] == 1)
			sign = -1;
		
		double result = 0;
		if (expDecimal >0)
		{
			if (shift > 0)
			{
				fractionPart++;
				//printf("fraction part %lf\n", fractionPart);
				//printf("1.\n");
				result = fractionPart * sign * findPower(2, shift);
			}
			
			else
			{
				fractionPart++;
				/*
				printf("fraction part %lf\n", fractionPart);
				printf("shift is %d\n", shift);
				printf("2.\n");
				printf("sign is %d\n", sign);
				printf("%lf\n", findPower(2, -1*shift));*/
				result = fractionPart * sign * 1.0/findPower(2, -1*shift);
			}
		}
			
		else
		{
			shift = 1- bias;
			if ( shift > 0)
			{
				//printf("fraction part %lf\n", fractionPart);
				//	printf("3.\n");
				result = fractionPart * sign * findPower(2, shift);
			}
			else
			{
				//printf("fraction part %lf\n", fractionPart);
				//printf("4.\n");
				result = fractionPart * sign * 1.0/findPower(2,-1*shift);
			}
		}


		free(ieee);
		free(f);
		free(exp);
		printf("%.*lf\n", prec, result);	
		/*	
		if (shift >= 0)
		{
			long double result = 0;	
			long* mantissa = malloc((fBits +1)*sizeof(long));
			mantissa[0] = 1;
			int f = expBits + 1;
			for (int x = 1; x < (fBits +1); x++)
			{
				mantissa[x] = ieee[f];
				f++;
			}
			
			if (shift >= fBits)
			{
				int pow = shift - fBits;
				for (int x = fBits; x>=0; x--)
				{
					if (mantissa[x] == 1)
						result += findPower(2, pow);

					pow++;
				}
			}

			else
			{
				int pow = 0;
				for (int x = shift; x>=0; x--)
				{
					if (mantissa[x] == 1)
						result += findPower(2, pow);
					pow++;
				}
				pow = 1;
				for (int x = shift+1; x < fBits +1; x++)
				{
					if (mantissa[x] == 1)
						result += 1.0/findPower(2,pow);
					pow++;
				}	
			}	
			
			if (ieee[0] == 1)
				printf("-");

			free(ieee);
			free(exp);
			free(mantissa);
			printf("%.*Lf\n", prec, result);
			
		} */
		/*
		else
		{
			shift *= -1;
			long double result = 0;
			
			if (expDecimal !=  0)
			{
				
				int pow = shift;
				long* mantissa = malloc((fBits +1)*sizeof(long));
		                mantissa[0] = 1;
				int f = expBits + 1;
			       	for (int x = 1; x < (fBits +1); x++)
				{
					mantissa[x] = ieee[f];
					f++;
				 }
	       						
				printf("mantissa :");
				for (int x = 0; x < fBits + 1; x++)
				{
					printf("%ld", mantissa[x]);
				}
				printf("\n");	
				for (int x = 0; x < fBits + 1; x++)
				{
					if (mantissa[x] == 1)
					result += 1.0/findPower(2, pow);
					//printf("result is %Lf\n", result);
					pow++;
				}			
			free(mantissa);		
			}	
		
		 	else
			{
			
			int pow = shift;	
			// might be wrong	
			for (int x = fBits + 1; x < totalBits; x++)
			{
				if (ieee[x] == 1)
					result += 1.0/findPower(2, pow);	
				pow++;
			}
			}

			if (ieee[0] == 1)
				printf("-");	
			free(ieee);
			free(exp);
			 printf("%.*Lf\n", prec, result);
			 
			
		}*/
	}

	return EXIT_SUCCESS;
}

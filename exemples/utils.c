#include "utils.h"
#define printf() my_printf(format, ...);

int ajouter(int a , int b)
{
	return a + b;
}

int  fctABC()
{
	int a  = 5;
	int b = 6;

	return ajouter(a, b);
}

int my_printf(const char * format, ...)
{
	printf("6278187 --- : ");
} 


// Predict your age!

#include <math.h>

int predictAge(int age1, int age2, int age3, int age4, int age5, int age6, int age7, int age8)
{
	int ages[8]{ age1, age2, age3, age4, age5, age6, age7, age8 };
	int i, sum = 0;

	for (i = 0; i < 8; i++)
	{
		sum += ages[i] * ages[i];
	}

	return sqrt(sum) / 2;
}
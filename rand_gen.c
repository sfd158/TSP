#include "rand_gen.h"
#include <limits.h>
#include <float.h>
#include <stdlib.h>
unsigned int getUnsignedShort()
{
	return (rand()<<1) | (rand() & 1);
}
unsigned int getUnsignedRand()
{
	return (rand() << 17) | (rand() << 2) | (rand() & 3);
}
unsigned int getLargeRand(AB_t(const unsigned int))
{
	unsigned int x = getUnsignedRand();
	return x%(b-a+1)+a;
}
double getDoubleRand()
{
	return (double)getUnsignedRand() / ULONG_MAX;
}
double getDoubleRandRange(AB_t(const double))
{
	double x = getDoubleRand();
	return x*(b-a)+a;
}


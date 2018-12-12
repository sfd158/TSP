#ifndef RAND_GEN_H
#define RAND_GEN_H
#include "global.h"
unsigned int getUnsignedShort();
unsigned int getUnsignedRand();
unsigned int getLargeRand(AB_t(const unsigned int));
double getDoubleRand();
double getDoubleRandRange(AB_t(const double));

#endif

#ifndef SIMULATE_ANNEAL_H
#define SIMULATE_ANNEAL_H
#include "TSP.h"
int Simulate(TSPTimesPara_t,
const double init_T, const double final_T, const double alpha,
void changeFunc(struct Order*,const int,const int,const int));

#endif

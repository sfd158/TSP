#ifndef GENETIC_H
#define GENETIC_H
#include "global.h"
#define CrossPara const struct Order *input_0, const struct Order *input_1,\
struct Order *ans_0, struct Order *ans_1,\
const int order_len, const int min_cross, const int max_cross

void partialMappedCrossover(CrossPara);
#endif

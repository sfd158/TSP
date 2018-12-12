#ifndef _TESTTSP_H
#define _TESTTSP_H
#include "global.h"

#define TSP_t struct TSP *tsp
#define ORDER_t struct Order * order
#define CntLenPara_t const int order_cnt, const int order_len
#define OrderPara_t ORDER_t, CntLenPara_t
#define OrderTimesPara_t OrderPara_t, const int times
#define TSPPara_t TSP_t, OrderPara_t
#define TSPTimesPara_t TSP_t, OrderTimesPara_t

#define CntLen_i order_cnt, order_len
#define OrderPara_i order, CntLen_i
#define OrderTimesPara_i OrderPara_i, times
#define TSPPara_i tsp, OrderPara_i
#define TSPTimesPara_i tsp, OrderTimesPara_i


struct TSP
{
	int dim;
	struct Point * points;
	int * nearest;
	double **dist;
	struct Order *bestans;
	double bestlen;
};
void swap(AB_t(int*));
int * genIntArr(const int len);
void genRandOrder(OrderPara_t);
void genSequenceOrder(OrderPara_t);
void copyOrder(struct Order * dest, const struct Order *source, CntLenPara_t);
struct Order * genOrder(CntLenPara_t);
void genGreedyOrder(TSPPara_t, const int *start_nodes);
void initTSP(TSP_t);
void TSP_free(TSP_t);
void Order_free(ORDER_t, const int order_cnt);
void calcNearPoint(TSP_t);
int isOrderLegel(const ORDER_t, const int order_len);
void calcDist(TSPPara_t, double * ans);
void calcOrderDist(TSPPara_t);
double dist2(AB_t(const struct Point*));
double dist(AB_t(const struct Point *));
void calcPointsDist(TSP_t);
struct Order * readOrder(const char *filename);
struct TSP * readPoint(const char * filename);
void outputTSPInput(const TSP_t);
void outputOrder(const OrderPara_t);
struct TSP *genBlankTSP(const int dim);
struct Order * orderFromSmallest(const OrderPara_t);

void mutation(OrderTimesPara_t);
int getrand(const int l, const int r);

void orderReverse(OrderTimesPara_t);
void OutputOrderDist(OrderPara_t);
#endif

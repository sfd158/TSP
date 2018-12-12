#include "SimulateAnneal.h"
#include "TSP.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include "rand_gen.h"
int Simulate(TSPTimesPara_t,
const double init_T, const double final_T, const double alpha,
void changeFunc(struct Order*,const int,const int,const int))
{
	int j, best_place=0;
	double T = init_T, finalAns = DBL_MAX;
	struct Order * order_1 = genOrder(order_cnt, order_len);
	struct Order * order_2 = genOrder(order_cnt, order_len);
	struct Order * bestOrder = genOrder(order_cnt, order_len);
	copyOrder(order_2, order, order_cnt, order_len);
	copyOrder(bestOrder, order, order_cnt, order_len);
	while(T > final_T)
	{
		/*printf("T = %.2lf\n", T);*/
		copyOrder(order_1, order_2, order_cnt, order_len);
		changeFunc(order_1,order_cnt,order_len,times);
		calcOrderDist(tsp,order_1,order_cnt,order_len);
		for(j=0; j<order_cnt; j++)
		{
			int flag = 0;
			if (order_1[j].ans < order_2[j].ans)
			{
				flag = 1;
				if(order_1[j].ans < bestOrder[j].ans)
				{
					copyOrder(bestOrder+j,order_1+j,1,order_len);
				}
			}
			else
			{
				double p=exp((order_2[j].ans - order_1[j].ans)/T);
				/*printf("p=%lf\n",p);*/
				if(p > getDoubleRand())
				{
					flag = 1;
				}
			}
			if(flag)
			{
				copyOrder(order_2+j,order_1+j,1,order_len);
			}
		}
		T *= alpha;
	}
	for(j=0; j<order_cnt; j++)
	{
		if(finalAns > bestOrder[j].ans)
		{
			finalAns = bestOrder[j].ans;
			best_place = j;
		}
	}
	copyOrder(order,bestOrder,order_cnt,order_len);
	Order_free(order_1,order_cnt);
	Order_free(order_2,order_cnt);
	Order_free(bestOrder, order_cnt); 
	return best_place;
}

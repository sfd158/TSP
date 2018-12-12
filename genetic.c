#include "genetic.h"
#include "TSP.h"
#include "rand_gen.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
double *genSufficiency(OrderPara_t)
{
	double *s = (double*)malloc(sizeof(double)*order_len);
	int j;
	for(j=0;j<order_cnt;j++)
	{
		s[j] = 1/order[j].ans;
	}
	return s;
}
double* getArrSum(const double *s, const int order_len)
{
	double *sum = (double*)malloc(sizeof(double)*order_len);
	int j;
	sum[0] = s[0];
	for(j=1;j<order_len;j++)
	{
		sum[j] = sum[j-1] + s[j];
	}
	return sum;
}
int geneticGenOne(OrderPara_t, double *Suff, double *sum,
int(GenMethod)(struct Order*,const int,const int,double*,double*)) 
{
	double *new_Suff, *new_sum;
	int select;
	if(Suff == NULL)
	{
		new_Suff = genSufficiency(OrderPara_i);
		new_sum = getArrSum(new_Suff,order_len);
	}
	else
	{
		new_Suff = Suff;
		new_sum = sum;
	}
	select = GenMethod(OrderPara_i,new_Suff,new_sum); 
	if(Suff == NULL)
	{
		free(new_Suff);
		free(new_sum); 
	}
	return select;
}
int RouletteWheelSelection(OrderPara_t, double *Suff, double * sum)
{
	double p = getDoubleRand();
	int select;
	for(select=0; select<order_cnt; select++)
	{
		if(sum[select] >= p)
		{
			break;
		}
	}
	return select;
}
int StochasticTournament(OrderPara_t, double* Suff, double *sum)
{
	int p1,p2;
	p1 = RouletteWheelSelection(OrderPara_i,Suff,sum);
	p2 = RouletteWheelSelection(OrderPara_i,Suff,sum);
	if (order[p1].ans > order[p2].ans)
	{
		return p2;
	}
	else return p1;
}

void Genetic(TSPTimesPara_t, const int maxGenCnt,
const double cross_p, const double mutation_p)
{
	int GenCnt = 0,j;
	double p;
	for(GenCnt=0; GenCnt<maxGenCnt; GenCnt++)
	{
		for(j=0; j<order_cnt; j++)
		{
			p = getDoubleRand();
			if(p > mutation_p)
			{
				mutation(OrderTimesPara_i);
			}
		}
	}
}
void partialMappedCrossover(CrossPara)/*checked*/
{
	int i,j,repeat_head,repeat_tail[2]={0,0};
	int cross = getrand(min_cross,max_cross);
	int left = getrand(0,order_len-cross);
	int *vis[2];
	int *repeat_node[2];
	const struct Order *input[2] = {input_0,input_1};
	struct Order *ans[2] = {ans_0, ans_1};
	#ifdef LOCAL
		printf("Before partial mapped crossover:\n");
		printf("Left = %d, Cross = %d\n",left,cross);
		for(j=0;j<2;j++)
		{
			outputOrder(input[j],1,order_len);
		}
		
	#endif
	for(j=0;j<2;j++)
	{
		vis[j] = genIntArr(order_len);
		repeat_node[j] = genIntArr(order_len);
		for(i=0; i<order_len; i++)
		{
			int *t = &(ans[j]->l[i]);
			if(left <= i && i < left + cross)
				*t = input[j]->l[i];
			else *t = input[1-j]->l[i];
			vis[j][*t]++;
			if(vis[j][*t] == 2)
			{
				repeat_node[j][repeat_tail[j]++] = *t;
			}
		}
	}
	#ifdef LOCAL
		printf("After change ,before map\n");
		for(j=0;j<2;j++)
		{
			outputOrder(ans[j],1,order_len);
		}
		printf("Map table:\n");
		for(j=0;j<2;j++)
		{
			for(i=0;i<repeat_tail[j];i++)
			{
				printf("%d ",repeat_node[j][i]);
			}
			putchar('\n');
		}
	#endif
	for(j=0;j<2;j++)
	{
		repeat_head = 0;
		for(i=0; i<order_len;i++)
		{
			int *t=&(ans[j]->l[i]);
			if(*t == repeat_node[j][repeat_head] && repeat_head < repeat_tail[j])
			{
				*t = repeat_node[1-j][repeat_head++];
			}
		}
	}
	#ifdef LOCAL
		printf("After partial mapped crossover:\n");
		for(j=0;j<2;j++)
		{
			outputOrder(ans[j],1,order_len);
		}
	#endif
	for(j=0;j<2;j++)
	{
		free(repeat_node[j]);
		free(vis[j]);
	}
}

static void backfill(const int order_len, const int j,
const struct Order *input, struct Order *ans, int *vis)
{
	int i,k=0;
	for(i=0;i<order_len;i++)
	{
		if(ans[j].l[i] != -1)continue;
		while(!vis[input[1-j].l[k]] && k<order_len)
		{
			k++;
		}
		vis[input[1-j].l[k]] = 1;
		ans[j].l[i] = input[1-j].l[k];
	}
}
void orderCrossover(CrossPara)
{
	int cross = getrand(min_cross,max_cross);
	int i,j;
	int * vis = (int *)malloc(sizeof(int)*(order_len));
	int left = getrand(0,order_len-cross);
	for(j=0;j<2;j++)
	{
		memset(vis,0,sizeof(int)*(order_len));
		memset(ans[j].l,-1,sizeof(int)*(order_len));
		for(i=left;i<left+cross;i++)
		{
			ans[j].l[i] = input[j].l[i];
			vis[ans[j].l[i]]=1;
		}
		backfill(order_len,j,input,ans,vis);
	}
	free(vis);
}
void circleCrossOver(CrossPara)
{
	
}
void subtourExchangeCrossOver(CrossPara)
{
	const int cross = getrand(min_cross,max_cross);
	int i,j;
	const int left = getrand(0,order_len-cross);
	const int seriesPa = getrand(0,1);
	const int dispersePa = 1-seriesPa;
	int * dispersePlace = (int*)malloc(sizeof(int)*order_len);
	int * disperseList = (int*)malloc(sizeof(int)*cross);
	for(j=0;j<2;j++)
	{
		memcpy(ans[j].l,input[j].l,sizeof(int)*order_len);	
	}
	for(i=0;i<order_len;i++)
	{
		dispersePlace[input[dispersePa].l[i]] = i;
	}
	for(i=left;i<left+cross;i++)
	{
		disperseList[i-left] = dispersePlace[input[seriesPa].l[i]];
		printf("%d ",disperseList[i-left]);
	}

}
void positionBasedCrossover(CrossPara)
{
	const int cross = getrand(min_cross,max_cross);
	int i,p,j;
	int * vis = (int *)malloc(sizeof(int)*(order_len));
	int * crossPlace = (int *)malloc(sizeof(int)*cross);

	memset(vis,0,sizeof(int)*order_len);
	for(i=0;i<cross;i++)
	{
		do
		{
			p = rand() % (order_len);
		}while(vis[p] == 0);
		vis[p] = 1;
		crossPlace[i] = p;
	}
	for(j=0;j<2;j++)
	{
		memset(vis,0,sizeof(int)*(order_len));
		memset(ans[j].l,-1,sizeof(int)*(order_len));
		for(i=0;i<cross;i++)
		{
			ans[j].l[crossPlace[i]] = input[j].l[crossPlace[i]];
			vis[ans[j].l[crossPlace[i]]] = 1;
		}
		backfill(order_len,j,input,ans,vis);
	}
	free(vis);
	free(crossPlace);
}



#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<float.h>
#include"TSP.h"

struct forRand
{
	int val;
	int randnum;
};
void swap(AB_t(int*))
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

static int forRandSort(AB_t(const void *))
{
	const struct forRand * _a=(const struct forRand*)a, *_b=(const struct forRand*)b;
	return _a->randnum - _b->randnum;
}

int * genIntArr(const int len)
{
	int * t = (int*)malloc(sizeof(int)*len);
	memset(t,0,sizeof(int)*len);
	return t;
}
void genRandOrder(OrderPara_t)
{
	struct forRand * l = (struct forRand *)malloc(sizeof(struct forRand)*(order_len));
	int i,j;
	for(i=0;i<order_len;i++)
		l[i].val = i;
	
	for(j=0;j<order_cnt;j++)
	{
		for(i=0;i<order_len;i++)
			l[i].randnum = rand();
		qsort(l,order_len,sizeof(struct forRand),forRandSort);
		for(i=0;i<order_len;i++)
		{
			order[j].l[i] = l[i].val;
		}
	}
	free(l);
}
void genSequenceOrder(OrderPara_t)
{
	int i,j;
	for(j=0;j<order_cnt;j++)
	{
		for(i=0;i<order_len;i++)
		{
			order[j].l[i] = i;
		}
	}
}
void copyOrder(struct Order * dest, const struct Order *source, CntLenPara_t)
{
	int j;
	for(j=0; j<order_cnt; j++)
	{
		memcpy(dest[j].l, source[j].l, sizeof(int)*order_len);
		dest[j].ans = source[j].ans;
	}
}
struct Order * genOrder(CntLenPara_t)
{
	struct Order * order = (struct Order *)malloc(sizeof(struct Order)*order_cnt);
	int i;
	for(i=0;i<order_cnt;i++)
	{
		order[i].l = (int*)malloc(sizeof(int)*order_len);
		memset(order[i].l,0,sizeof(int)*order_len);
		order[i].ans = DBL_MAX;
	}
	return order;
}
void genGreedyOrder(TSPPara_t, const int *start_nodes)
{
	int * start = (int*)malloc(sizeof(int)*order_cnt);
	int i,j,k,node;
	double min_d;
	if(start_nodes == NULL)
	{
		for(i=0;i<order_cnt;i++)
		{
			start[i] = getrand(0,order_len-1);
			printf("%d ",start[i]);
		}
		putchar('\n');
	}
	else memcpy(start,start_nodes,sizeof(int)*order_cnt);
	int * vis = (int*)malloc(sizeof(int)*order_len);
	for(j=0;j<order_cnt;j++)
	{
		node = start[j];
		memset(vis,0,sizeof(int)*order_len);
		for(i=0;i<order_len;i++)
		{
			 order[j].l[i] = node;
			 vis[node] = 1;
			 min_d = DBL_MAX;
			 for(k=0;k<order_len;k++)
			 {
		 		if(i==k || vis[k])continue;
		 		if(min_d > tsp->dist[i][k])
				{
					node=k;
					min_d = tsp->dist[i][k]; 	
				} 
			 }
		}
	}
	calcOrderDist(TSPPara_i);
	free(vis);
	free(start);
}
 
void initTSP(TSP_t)
{
	tsp->points = (struct Point*)malloc(sizeof(struct Point)*(tsp->dim));
	tsp->dist = (double**)malloc(sizeof(double*)*(tsp->dim));
	tsp->nearest = (int*)malloc(sizeof(int)*(tsp->dim));
	int i;
	for(i=0;i<tsp->dim;i++)
	{
		tsp->dist[i] = (double*)malloc(sizeof(double)*(tsp->dim));
	}
	tsp->bestans = NULL;
}
void TSP_free(TSP_t)
{
	free(tsp->points);
	free(tsp->bestans);
	free(tsp->nearest);
	int i;
	for(i=0;i<tsp->dim;i++)
	{
		free(tsp->dist[i]);
	}
	free(tsp->dist);
}

void Order_free(ORDER_t, const int order_cnt)
{
	int j;
	for(j=0; j<order_cnt; j++)
	{
		free(order[j].l);
	}
	free(order);
}
void calcNearPoint(TSP_t)
{
	int i,j,p;
	double min_d;
	for(i=0;i<tsp->dim;i++)
	{
		min_d = DBL_MAX;
		for(j=0;j<tsp->dim;j++)
		{
			if(j==i) continue;
			if(tsp->dist[i][j] < min_d)
			{
				min_d = tsp->dist[i][j];
				p=j;
			}
		}
		tsp->nearest[i]=p;
	}
}
int isOrderLegel(const ORDER_t, const int order_len)
{
	int *t = (int*)malloc(sizeof(int)*order_len);
	memset(t,0,sizeof(int)*(order_len));
	int i,flag=1;
	for(i=0;i<order_len;i++)
	{
		t[order->l[i]]++;
	}
	for(i=0;i<order_len;i++)
	{
		if(t[i]!=1)
		{
			flag=0;
			break;
		}
	}
	free(t);
	return flag;
}
void calcDist(TSPPara_t, double * ans)
{
	int j;
	calcOrderDist(TSPPara_i);
	for(j=0;j<order_cnt;j++)
	{
		ans[j] = order[j].ans;
	}
}
void calcOrderDist(TSPPara_t)
{
	int i,j;
	for(j=0; j<order_cnt; j++)
	{
		order[j].ans = 0;
		for(i=0;i<order_len-1;i++)
		{
			order[j].ans += tsp->dist[order[j].l[i]][order[j].l[i+1]];
		}
		order[j].ans += tsp->dist[order[j].l[order_len-1]][order[j].l[0]];
	}
}
double dist2(AB_t(const struct Point *))
{
	const double dx=(a->x)-(b->x), dy=(a->y)-(b->y);
	return dx*dx+dy*dy;
}
double dist(AB_t(const struct Point *))
{
	return sqrt(dist2(a,b));
}
static int calcint(const char * s)
{
	int x=0;
	const char * p = s;
	while((*p) != '\0' && !isdigit(*p))
	{
		p++;
	}
	while(isdigit(*p))
	{
		x=x*10+(*p)-'0';
		p++;
	}
	return x;
}
void calcPointsDist(TSP_t)
{
	int i,j;
	for(i=0;i<tsp->dim;i++)
	{
		for(j=0;j<tsp->dim;j++)
		{
			if(i==j)
			{
				tsp->dist[i][j] = 0;
			}
			else tsp->dist[i][j] = dist(&(tsp->points[i]),&(tsp->points[j]));
		}
	}
}
struct Order * readOrder(const char *filename)
{
	struct Order * order = (struct Order*)malloc(sizeof(struct Order));
	FILE * f = fopen(filename,"r");
	char buf[1024];
	int i,order_len,cnt=0;
	for(i=0;i<4;i++)
		fgets(buf,1000,f);
	order_len = calcint(buf);
	fgets(buf,1000,f);
	order->l = (int*)malloc(sizeof(int)*order_len);
	while(fscanf(f,"%d",&i)==1 && i!=-1)
	{
		order->l[cnt++] = i-1;
	}
	
	fclose(f);
	return order;
}
struct TSP * readPoint(const char * filename)
{
	struct TSP * tsp = (struct TSP*)malloc(sizeof(struct TSP));
	FILE * f = fopen(filename,"r");
	char buf[1024];
	int i;
	for(i=0; i<3; i++)
	{
		fgets(buf,1000,f);
	}
	fgets(buf,1000,f);
	tsp->dim = calcint(buf);
	initTSP(tsp);
	for(i=0;i<2;i++)
		fgets(buf,1000,f);
	for(i=0;i<tsp->dim;i++)
	{
		int idx;
		struct Point p;
		fscanf(f,"%d%lf%lf",&idx,&p.x,&p.y);
		(tsp->points)[i] = p;
	}
	fclose(f);
	calcPointsDist(tsp);
	return tsp;
}

void outputTSPInput(const TSP_t)
{
	int i;
	for(i=0;i<tsp->dim;i++)
	{
		printf("%.lf %.lf\n",tsp->points[i].x, tsp->points[i].y);
	}
}

void outputOrder(const OrderPara_t)
{
	int i,j;
	for(i=0; i<order_cnt; i++)
	{
		printf("Order %d: dist: ",i);
		if(order[i].ans < DBL_MAX)
			printf("%.5lf\n", order[i].ans);
		else printf("+INF\n");
		for(j=0; j<order_len; j++)
		{
			printf("%d ",order[i].l[j]);
		}
		putchar('\n');
	}
}

struct TSP *genBlankTSP(const int tsp_dim)
{
	struct TSP * tsp = (struct TSP *)malloc(sizeof(struct TSP));
	tsp->bestans = NULL;
	tsp->dist = NULL;
	tsp->nearest = NULL;
	tsp->dim = tsp_dim;
	tsp->points = NULL;
	tsp->bestlen = DBL_MAX;
	return tsp;
}

struct Order * orderFromSmallest(const OrderPara_t)
{
	struct Order * new_order = (struct Order*)malloc(sizeof(struct Order)*order_cnt);
	int min_p, min_v, i,cnt,j;
	for(j=0; j<order_cnt; j++)
	{
		min_p = 0;
		min_v = order_len+1;
		cnt = 0;
		new_order[j].l = (int*)malloc(sizeof(int)*order_len);
		for(i=0;i<order_len;i++)
		{
			if(order[j].l[i] < min_v)
			{
				min_v = order[j].l[i];
				min_p = i; 
			}
		}
		for(i=min_p;i<order_len;i++)
		{
			new_order[j].l[cnt++] = order[j].l[i];
		}
		for(i=0;i<min_p;i++)
		{
			new_order[j].l[cnt++] = order[j].l[i];
		}
	}
	return new_order;
}

int compareOrder(const struct Order *order_1, const int len_1, 
const struct Order* order_2, const int len_2,
struct Order **cooked_1, struct Order **cooked_2)
{
	struct Order *tp_1, *tp_2;
	int i, flag=0;
	if(len_1 != len_2)
	{
		return len_1 - len_2;
	}
	tp_1 = orderFromSmallest(order_1, len_1, 1);
	tp_2 = orderFromSmallest(order_2, len_2, 1);
	if(cooked_1 != NULL)
	{
		*cooked_1 = tp_1; 
	}
	if(cooked_2 != NULL)
	{
		*cooked_2 = tp_2;
	}
	for(i=0; i<len_1; i++)
	{
		if(tp_1->l[i] != tp_2->l[i] )
		{
			flag = tp_1->l[i] - tp_2->l[i];
			break;
		} 
	}
	if(cooked_1 == NULL)
	{
		free(tp_1->l);
		free(tp_1);
	}
	if(cooked_2 == NULL)
	{
		free(tp_2->l);
		free(tp_2);
	}
	return flag;
} 

void mutation(OrderTimesPara_t)
{
	int i,p1,p2,j;
	for(j=0; j<order_cnt; j++)
	{
		for(i=0;i<times;i++)
		{
			p1 = rand()%order_len;
			do
			{
				p2 = rand()%order_len;
			}while(p1 == p2);
			swap(&(order[j].l[p1]),&(order[j].l[p2]));
		}
		#ifdef LOCAL
			printf("Mutation Order:%d p1: %d, p2: %d\n",j,p1,p2);
			for(i=0;i<order_len;i++)
			{
				printf("%d ",order[j].l[i]);
			}
			putchar('\n');
			getchar();
		#endif
	}
}

int getrand(const int l, const int r)
{
	return rand()%(r-l+1)+l;
}

void orderReverse(OrderTimesPara_t)
{
	int j,p1,p2,i,k;
	for(j=0; j<order_cnt; j++)
	{
		for(k=0;k<times;k++)
		{
			p1 = getrand(0, order_len-1);
			do
			{
				p2 = getrand(0, order_len-1);
			}while(p1 == p2);
			if(p1 > p2) swap(&p1, &p2);
		
			for(i=0; i<((p2-p1)>>1)+1; i++)
			{
				swap(&order[j].l[p1+i], &order[j].l[p2-i]);
			}
			#ifdef LOCAL
				printf("Order:%d p1: %d, p2: %d\n",j,p1,p2);
				for(i=0;i<order_len;i++)
				{
					printf("%d ",order[j].l[i]);
				}
				putchar('\n');
			#endif
		} 
	}
}

void OutputOrderDist(OrderPara_t)
{
	int j;
	for(j=0;j<order_cnt;j++)
	{
		printf("Order %d-th ans=",j);
		if(order[j].ans < DBL_MAX)
		{
			printf("%.5lf\n",order[j].ans);
		}
		else printf("+INF\n");
	}
}

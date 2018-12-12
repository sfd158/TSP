#include "TSP.h"
#include "dictTree.h"
#include "SimulateAnneal.h"
#include<stdio.h> 
#include<time.h>
#include<stdlib.h>
#include "genetic.h"
#include "rand_gen.h"
void testTSP()
{
	const int order_cnt = 10;
	struct TSP * tsp = readPoint("D:/msys64/home/song/tsp/a280.tsp");
	struct Order * order = genOrder(order_cnt,tsp->dim);
	struct Order * best = readOrder("D:/msys64/home/song/tsp/a280.opt.tour");
	
	calcOrderDist(tsp,best,1,tsp->dim);
	printf("Best Order:\n");
	outputOrder(best, 1,tsp->dim);
	
	/*calcOrderDist(tsp,bestFromSmall,1,tsp->dim);
	printf("\nBest Order From Smallest:\n");
	outputOrder(bestFromSmall, 1, tsp->dim);*/
	
/*	genSequenceOrder(order,order_cnt,tsp->dim);
	calcOrderDist(tsp,order,order_cnt,tsp->dim);
	printf("\nSequence Order dist:\n");
	OutputOrderDist(order,order_cnt,tsp->dim);*/
	/*outputOrder(order,order_cnt,tsp->dim);*/
	
	genRandOrder(order,order_cnt,tsp->dim);
	calcOrderDist(tsp,order,order_cnt,tsp->dim);
	printf("\nRand Order:\n");
	OutputOrderDist(order,order_cnt,tsp->dim);
	/*outputOrder(order,order_cnt,tsp->dim);*/
	
	int best_place = Simulate(tsp,order,order_cnt,tsp->dim,1,1e4,1e-6,1-1e-4,orderReverse);
	/*模拟退火真是相当看脸，这组参数只对a280.tsp比较有效*/ 
	printf("Best: %d\n",best_place);
	OutputOrderDist(order,order_cnt,tsp->dim);
	
	genGreedyOrder(tsp,order,order_cnt,tsp->dim,NULL);
	calcOrderDist(tsp,order,order_cnt,tsp->dim);
	printf("\nGreedy Order:\n");
	OutputOrderDist(order,order_cnt,tsp->dim);
	
	best_place = Simulate(tsp,order,order_cnt,tsp->dim,1,10000,0.0001,0.99,orderReverse);
	printf("Best: %d\n",best_place);
	OutputOrderDist(order,order_cnt,tsp->dim);
	
	/*outputOrder(order,order_cnt,tsp->dim); */
	TSP_free(tsp);
}

void testDictTree()
{
	struct dictWordTree* tree = initDictWordTree(26);
	insertDictWordTree(tree,"hello", 2);
	insertDictWordTree(tree,"helloworld", 3);
	insertDictWordTree(tree,"hel", 4);
	insertDictWordTree(tree,"worldhello", 5);
	struct dictWordTreeNode* ans = findDictWordTree(tree, "hello", NULL);
	printf("ans hasnode:%d value:%d\n",ans->has_node,ans->value);
	removeFromDictTree(tree,"hello");
	ans = findDictWordTree(tree, "hello", NULL);
	printf("ans hasnode:%d value:%d\n",ans->has_node,ans->value);
	outputDictTree(tree,1);
	destroyDictWordTree(tree);
}

void testOrder()
{
	const int order_cnt = 5, order_len = 10;
	struct Order * order = genOrder(order_cnt, order_len);
	struct Order * ans = genOrder(order_cnt, order_len);
	int p1,p2;
	/*genSequenceOrder(order,order_cnt,order_len);
	outputOrder(order,order_cnt,order_len);
	printf("\nAfter reverse:\n");
	orderReverse(order,order_cnt,order_len,1);
	genSequenceOrder(order,order_cnt, order_len);*/
	genRandOrder(order,order_cnt,order_len);
	p1=1; p2=3;
	int cross_min=2,cross_max=4;
	partialMappedCrossover(order+p1,order+p2,ans+p1,ans+p2,order_len,cross_min,cross_max);
}
int main(int argc, char **argv)
{
	/*freopen("log.txt","w",stdout);*/
	printf("%d\n",RAND_MAX);
	srand(time(NULL));
	/*testDictTree();*/
	/*testTSP(); */
	testOrder();
	/*testRandGen();*/
	return 0;
} 

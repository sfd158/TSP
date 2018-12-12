#ifndef ANT_COLONY_H
#define ANT_COLONY_H

struct ANTS{
	struct TSP * tsp;
	double **yita;
	/*能见度为距离的倒数, 在我们的算法里不适合*/ 
	double **tau;
	double alpha;
	double beta;
	double rho;
};

#endif

#ifndef ANT_COLONY_H
#define ANT_COLONY_H

struct ANTS{
	struct TSP * tsp;
	double **yita;
	/*�ܼ���Ϊ����ĵ���, �����ǵ��㷨�ﲻ�ʺ�*/ 
	double **tau;
	double alpha;
	double beta;
	double rho;
};

#endif

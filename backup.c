/*
void orderCrossover(CrossPara, const int isLeftChange)
{
	int cross = getrand(min_cross,max_cross);
	int i,j,k;
	int * vis = (int *)malloc(sizeof(int)*(tsp_dim));
	int left = getrand(0,tsp_dim-cross);
	for(j=0;j<2;j++)
	{
		memset(vis,0,sizeof(int)*(tsp_dim));
		memset(ans[j].l,-1,sizeof(int)*(tsp_dim));
		if(isLeftChange)
		{
			left = getrand(0,tsp_dim-cross);
		}
		memcpy(&(ans[j].l[left]),&(input[j].l[left]),sizeof(int)*cross);
		k=0;
		for(i=0;i<tsp_dim;i++)
		{
			if(ans[j].l[i] != -1)continue;
			while(!vis[input[1-j].l[k]] && k<tsp_dim)
			{
				k++;
			}
			vis[input[1-j].l[k]] = 1;
			ans[j].l[i] = input[1-j].l[k];
		}
	}
	free(vis);
}
void positionBasedCrossover(CrossPara)
{
	int cross = getrand(min_cross,max_cross);
	int i,p,j,k;
	int * vis = (int *)malloc(sizeof(int)*(tsp_dim));
	for(j=0;j<2;j++)
	{
		memset(vis,0,sizeof(int)*(tsp_dim));
		memset(ans[j].l,-1,sizeof(int)*(tsp_dim));
		for(i=0;i<cross;i++)
		{
			do
			{
				p = rand() % (tsp_dim);
			}while(vis[p] == 0);
			vis[p] = 1;
			ans[j].l[p] = input[j].l[p];
		}
	
		k=0;
		for(i=0;i<tsp_dim;i++)
		{
			if(ans[j].l[i] != -1)continue;
			while(!vis[input[1-j].l[k]] && k<tsp_dim)
			{
				k++;
			}
			vis[input[1-j].l[k]] = 1;
			ans[j].l[i] = input[1-j].l[k];
		}
	}
	
	free(vis);
}
*/

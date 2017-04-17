#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

int findMin(int **G, int n, int vertex, bool *flag)
{
	int min = INT_MAX;
	int index = -1;
	for (int i = 0; i < n; ++i) {
		//printf("%d\n", *(*(G+vertex)+i));
		if (flag[i] == false) 
			if (  *(*(G+vertex)+i) < min) {
				min = *(*(G+vertex)+i);
				index = i;
			}
	}
	return index;
}

void print(int *path, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", path[i]);
	}
	printf("\n");
	return;
}


int calculateTotalDistance(int **G, int *path,int n)
{
	int totalDistance = 0;
	for (int i = 0; i < n-1; ++i)
	{
		totalDistance += G[path[i]][path[i+1]];
	}
	return totalDistance;
}

int *twoOptSwappedRoute(int *path, int start, int end,int length)
{
	int *temp_path = (int *)malloc(length * sizeof(int));
	for (int i = 0; i < length; ++i)
	{
		if(i < start || i > end)
			temp_path[i] = path[i];
		else
			temp_path[i] = path[start+end-i];
	}
	return temp_path;
}


int *twoOptSwap(int **G, int *path, int n)
{
	start_again:
	int best_distance = calculateTotalDistance(G,path,n);
	for (int i = 1; i < n-1; ++i)
	{
		for (int k = i+1; k < n; ++k)
		{
			int *new_path = twoOptSwappedRoute(path,i,k,n);
			int new_distance = calculateTotalDistance(G,new_path,n);
			if(new_distance < best_distance)
			{
				int *temp = path;
				path = new_path;
				free(temp);
				goto start_again;
			}
			else
				free(new_path);
		}
	}
	return path;
}



int twoOptTspRun(int **G, int n)
{
	bool flag[n];
	int *path = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		flag[i] = false;
	int curr_loc = 0;
	path[0] = 0;
	for (int i = 0; i < n; ++i) {
		flag[curr_loc] = true;
		path[i] = curr_loc;
		curr_loc = findMin(G, n, curr_loc, flag);
	}

	print(path, n);

	path = twoOptSwap(G,path,n);

	print(path, n);

	return 0;

}


int main()
{

	int **G;
	int n;
	printf("Enter the size of Graph\n");
	scanf("%d", &n);
	G = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; ++i)
		G[i] = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		//printf("Enter  for %dth vertex\t :  ", i);
		for (int j = i; j < n; j++)
		{
			scanf("%d", &G[i][j]);
			G[j][i] = G[i][j];
		}
	}
	twoOptTspRun(G,n);
	
	return 0;
}



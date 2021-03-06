#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>

//Returns  the Nearest neighbourhood unvisited vertex for a given vertex

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

//Give Output of Final Path in Given order of nodes
void print(int *path, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", path[i]);
	}
	return;
}

//Returns the distance Of given Order on nodes in path array of size n
int calculateTotalDistance(int **G, int *path,int n)
{
	int totalDistance = 0;
	for (int i = 0; i < n-1; ++i)
	{
		totalDistance += G[path[i]][path[i+1]];
	}

	return totalDistance;
}


//Make anew route by reverting order of nodes between start to end

int *twoOptSwappedRoute(int *path, int start, int end,int length)
{

	int *temp_path = (int *)malloc((length+2) * sizeof(int));
	for (int i = 0; i < length; ++i)
	{
		if(i < start || i > end)
		temp_path[i] = path[i];
		else
			temp_path[i] = path[start+end-i];
	}
	return temp_path;
}

//Two-Opt Algorithm by Swapping couple of Edges

int *twoOptSwap(int **G, int *path, int n)
{
	start_again:
	int best_distance = calculateTotalDistance(G,path,n);
	for (int i = 1; i < n-2; ++i)
	{
		for (int k = i+1; k < n-1; ++k)
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


//Two-Opt algorithm
//First Creates a path based on Nearest neighbourhood 
//Then applies Two-Opt algorithm on given path
int twoOptTspRun(int **G, int n)
{
	bool flag[n];
	int *path = (int *)malloc((n+2) * sizeof(int));
	for (int i = 0; i < n-1; ++i)
		flag[i] = false;
	int curr_loc = 0;
	path[n-1] = 0;
	for (int i = 0; i < n-1; ++i) {
		flag[curr_loc] = true;
		path[i] = curr_loc;
		curr_loc = findMin(G, n-1, curr_loc, flag);
	}
	path[n] = 0;

	//print(path, n);

	path = twoOptSwap(G,path,n);

	print(path, n);

	return 0;

}

//Main Function

int main()
{

	int **G;
	//Number of nodes
	int n;
	//printf("Enter the size of Graph\n");
	scanf("%d", &n);
	G = (int **)malloc((n+2) * sizeof(int *));
	for (int i = 0; i < n+2; ++i)
		G[i] = (int *)malloc((n+2) * sizeof(int));

	//Enter the Upper Triangular Distance Matrix
	//First line consist of distances of 1st, 2nd, 3rd ....., nth nodes from First nodes
	//Second line consists of distances of 2nd, 3rd ....., nth nodes from Second nodes
	//third line consists of distances of 3rd, 4th ....., nth nodes from Third nodes
	//And So on up to nth node

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			scanf("%d", &G[i][j]);
			G[j][i] = G[i][j];
		}
	}
	twoOptTspRun(G,n+1);
	
	return 0;
}


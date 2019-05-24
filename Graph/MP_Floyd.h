#ifndef MP_FLOYD_H
#define MP_FLOYD_H
#define MAX 10000
#include "tree_ls.h"
#include "graph.h"

template<typename T>
void floyd_marshall(adjacentMatrixGraph<T>& G, T** edges, int** path)
{
	int n = G.numberOfVertices();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (G.existsEdge(i, j))
			{
				edges[i][j] = G.edgeWeight(i, j);
				path[i][j] = j;
			}
			else
			{
				edges[i][j] = MAX;
				path[i][j] = -1;
			}
		}
		edges[i][i] = 0;
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (edges[i][j]>edges[i][k] + edges[k][j])
				{
					edges[i][j] = edges[i][k] + edges[k][j];
					path[i][j] = path[i][k];
				}
			}
}

void printPath(int** path, int i, int j)
{
	if (i == j)
		cout << i << endl;
	else if (path[i][j] == -1)
		cout << "不能到达！" << endl;
	else
	{
		int k = path[i][j];
		cout << i << "->";
		while (k != j)
		{
			cout << k << "->";
			k = path[k][j];
		}
		cout << j << endl;
	}
}

template<typename T>
void showEdges(T** edges, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << edges[i][j] << " ";
		}
		cout << endl;
	}
}

void showPath(int** path, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << path[i][j] << " ";
		}
		cout << endl;
	}
}

#endif // !MP_FLOYD_H

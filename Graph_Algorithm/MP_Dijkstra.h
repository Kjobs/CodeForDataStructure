#ifndef MP_DIJKSTRA_H
#define MP_DIJKSTRA_H
#include "tree_ls.h"
#include "graph.h"

template<typename T>
void dijkstra(adjacentMatrixGraph<T>& G, int s, int* path, T* dist)
{
	int n = G.numberOfVertices();
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
	{
		dist[i] = INT_MAX;
		path[i] = -1;
		visited[i] = false;
	}
	path[s] = s;
	dist[s] = 0;
	visited[s] = true;

	for (int i = 0; i < n; i++)
	{
		if (G.existsEdge(s, i))
		{
			path[i] = s;
			dist[i] = G.edgeWeight(s, i);
		}
	}

	for (int i = 0; i < n - 1; i++)
	{
		T min; int u = 0;
		while (visited[u]) u++;
		min = dist[u];
		for (int j = 0; j < n; j++)
		{
			if (dist[j] < min && !visited[j])
			{
				min = dist[j];
				u = j;
			}
		}
		if (path[u] == -1)
			break;
		visited[u] = true;
		for (int j = 0; j < n; j++)
		{
			if (!visited[j] && G.existsEdge(u, j) && dist[u] + G.edgeWeight(u, j) < dist[j])
			{
				dist[j] = dist[u] + G.edgeWeight(u, j);
				path[j] = u;
			}
		}
	}
}

void printPath(int* path, int s, int t)
{
	if (path[t] == -1)
		cout << "不能到达";
	else
	{
		Stack<int> A;
		int u = t;
		while (u != s)
		{
			A.push(u);
			u = path[u];
		}
		A.push(u);
		while (!A.empty())
		{
			cout << A.top() << " ";
			A.pop();
		}
	}
}


#endif // !MP_DIJKSTRA_H


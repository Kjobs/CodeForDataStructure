#ifndef MST_KRUSKAL_H
#define MST_KRUSKAL_H
#include "graph.h"
#include "PriorQueue.h"

template<typename T>
edgeSet<T> MST_Kruskal(adjacentMatrixGraph<T>& G)
{
	int n = G.numberOfVertices();
	edgeSet<T> A;
	minHeap<edge<T>> heap;
	edge<T> temp;
	A.E = new edge<T>[n];
	int* h = new int[n];
	for (int i = 0; i < n; i++) h[i] = i;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (G.existsEdge(i, j))
			{
				temp.v1 = i;
				temp.v2 = j;
				temp.weight = G.edgeWeight(i, j);
				heap.push(temp);
			}
		}
	}
	while (A.size < n - 1)
	{
		temp = heap.top();
		heap.pop();
		if (find(temp.v1, h) != find(temp.v2, h))
		{
			A.E[A.size++] = temp;
			h[temp.v1] = temp.v2;
		}
	}
	return A;
}

int find(int i, int f[])
{
	return f[i] == i ? i : find(f[i], f);
}

#endif // !MST_KRUSKAL_H

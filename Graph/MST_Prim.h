#ifndef MST_PRIM_H
#define MST_PRIM_H
#include "graph.h"
#include "PriorQueue.h"

template<typename T>
edgeSet<T> MST_Prim(adjacentMatrixGraph<T>& G, int start)
{
	edgeSet<T> A; edge<T> temp;
	minHeap<edge<T>> heap;
	int n = G.numberOfVertices();
	A.E = new edge<T>[n];
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++) visited[i] = false;
	visited[start] = true;
	for (int i = 0; i < n; i++)
	{
		if (G.existsEdge(start, i))
		{
			temp.v1 = start;
			temp.v2 = i;
			temp.weight = G.edgeWeight(start, i);
			heap.push(temp);
		}
	}
	while (A.size < n - 1)
	{
		edge<T> x = heap.top();
		heap.pop();
		if (visited[x.v1] && visited[x.v2]) continue;
		A.E[A.size++] = x;
		int cur = visited[x.v1] ? x.v2 : x.v1;
		visited[cur] = true;
		for (int i = 0; i < n; i++)
		{
			if (G.existsEdge(cur, i) && !visited[i])
			{
				temp.v1 = cur;
				temp.v2 = i;
				temp.weight = G.edgeWeight(cur, i);
				heap.push(temp);
			}
		}
	}
	return A;
}



#endif // !MST_PRIM_H


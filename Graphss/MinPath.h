#ifndef MINPATH_H
#define MINPATH_H

#include <iostream>
#include "DGraph.h"
#define infinity 666

template<class T>
class DGraph_prac
{
public:
	DGraph_prac();
	void WeightM();
	void floyd();
	void dijkstra();
private:
	DGraph<T> *g = new DGraph<T>;
	int cost[MAX][MAX];
	int prev[MAX];
	int distd[MAX];
	int dist[MAX][MAX];
	int path[MAX][MAX];
};

template<class T>
DGraph_prac<T>::DGraph_prac()
{
	g->CreatDGraph();
}

template<class T>
void DGraph_prac<T>::WeightM()
{//权值矩阵
	int i, j;
	int count = 0;
	Enode *p;
	for (i = 0; i < g->Vnum; i++)
		for (j = 0; j < g->Vnum; j++)
			cost[i][j] = infinity ;
	for (i = 0; i < g->Vnum; i++)
	{
		p = g->mVexs[i].firstEdge;
		if (p)
 			j = p->ivex;
		while (p)
		{
			if (p->ivex == j )
				cost[i][j] =  g->Wedge[count++].weight;
			p = p->nextEdge;
			if (p)
				j = p->ivex;
		}
	}
}

template<class T>
void DGraph_prac<T>::floyd()
{
	int i, j, k;
	int tmp;
	for (i = 0; i < g->Vnum; i++) {
		for (j = 0; j < g->Vnum; j++) {
			dist[i][j] = cost[i][j];   // "顶点i"到"顶点j"的路径长度为"i到j的权值"。 
			path[i][j] = j;             // "顶点i"到"顶点j"的最短路径是经过顶点j。
		}
	}
	for (k = 0; k < g->Vnum; k++)
	{
		for (i = 0; i < g->Vnum; i++)
		{
			for (j = 0; j < g->Vnum; j++)
			{// 如果经过下标为k顶点路径比原两点间路径更短，则更新dist[i][j]和path[i][j]
				tmp = (dist[i][k] == infinity || dist[k][j] == infinity) ? infinity : (dist[i][k] + dist[k][j]);
				if (dist[i][j] > tmp)
				{
					dist[i][j] = tmp;
					path[i][j] = path[i][k];
				}
			}
		}
	}
	for (i = 0; i < g->Vnum; i++)
		cout << g->vexs[i] << "   ";
	cout << endl;
	cout << "floyd(" << g->mVexs[0].data << "): " << endl;
	for (j = 0; j < g->Vnum; j++)
			cout << dist[0][j] << " ";
	cout << endl;
}


template<class T>
void DGraph_prac<T>::dijkstra()
{
	int i, j, k;
	int min;
	int tmp;
	int flag[MAX];// flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
	int vs = 0;
	for (i = 0; i < g->Vnum; i++)
	{
		flag[i] = 0;                // 顶点i的最短路径还没获取到。
		//prev[i] = 0;                // 顶点i的前驱顶点为0。
		distd[i] = cost[vs][i];  // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
	}
	flag[vs] = 1;
	distd[vs] = infinity;
	for (i = 1; i < g->Vnum; i++)
	{
		min = infinity;
		for (j = 0; j < g->Vnum; j++)
		{
			if (flag[j] == 0 && distd[j]<min)
			{
				min = distd[j];
				k = j;
			}
		}

		flag[k] = 1;

		for (j = 0; j < g->Vnum; j++)
		{
			tmp = cost[k][j];
			tmp = (tmp == infinity ? infinity : (min + tmp)); 
			if (flag[j] == 0 && (tmp  < distd[j]))
			{
				distd[j] = tmp;
				//prev[j] = k;
			}
		}
	}
	cout << "dijkstra(" << g->mVexs[vs].data << "): " << endl;
	for (i = 0; i < g->Vnum; i++)
		cout << g->vexs[i] << "   ";
	cout << endl;
	for (i = 0; i < g->Vnum; i++)
		cout << distd[i] <<" ";
}

#endif //单源最短路径floyd和dijkstra实现
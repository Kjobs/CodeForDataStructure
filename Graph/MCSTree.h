#ifndef MCSTREE_H
#define MCSTREE_H

#include <iostream>
#include "UGraph.h"
#define infinity 666

template<class T>
class Graph_prac 
{
public:
	Graph_prac();
	void WeightM();
	//int GetWeight(int v1, int v2);
	void Prim();
	void Kruskal();
	void Sort();
private:
	UGraph<T> *g=new UGraph<T>;
	int cost[MAX][MAX];
};

template<class T>
Graph_prac<T>::Graph_prac()
{
	g->CreatGraph();
}

template<class T>
void Graph_prac<T>::WeightM()
{//权值矩阵
	int i, j;
	int count = 0;
	Enode *p;	
	for (i = 0; i < g->Vnum; i++)
		for (j = 0; j < g->Vnum; j++)
			cost[i][j] = infinity - 1;
	for (i = 0; i < g->Vnum; i++)
	{
			p = g->mVexs[i].firstEdge;
			j = p->ivex;
			while (p)
			{
				if (p->ivex == j && i < j)
					cost[i][j] = cost[j][i] = g->Wedge[count++].weight;
				p = p->nextEdge;
				if (p)
					j = p->ivex;
			}
	}
}


template<class T>
void Graph_prac<T>::Prim()
{//U表示生成树顶点集，根据权值依次加入U中顶点最小权值的边
	int *lowcost = new int[g->Vnum + 1];
	int *closest = new int[g->Vnum + 1];
	int i, j, k;
	int length = 0;
	for (i = 1; i<g->Vnum; i++)
	{
		lowcost[i] = cost[0][i];
		closest[i] = 0;
	}
	for (i = 1; i<g->Vnum; i++)
	{
		int min;		
		min = lowcost[i];
		k = i;
		for (j = 1; j<g->Vnum; j++)
		{//遍历得到最小权值的边
			if (lowcost[j]<min)
			{
				min = lowcost[j];
				k = j;
			}
		}
		lowcost[k] = infinity;//infinity表示已经加入
		cout << "(" << g->mVexs[closest[k]].data << "," << g->mVexs[k].data << ")" << " ";
		int v1 = closest[k];
		int v2 = k;
		length += cost[v1][v2];
		for (j = 1; j<g->Vnum; j++)
		{
			if (cost[k][j] < lowcost[j] && lowcost[j] != infinity)
			{
				lowcost[j] = cost[k][j];
				closest[j] = k;
			}
		}
	}
	cout << endl;
	cout << "Prim's Length=" << length;
}

template<class T>
void Graph_prac<T>::Sort()
{
	int i, j;
	int count = 0;
	for (i = 0; i < g->Enum; i++)
	{
		for (j = i+1; j < g->Enum; j++)
		{
			if (g->Wedge[i].weight >g->Wedge[j].weight )
			{
				swap(g->Wedge[i],g->Wedge[j]);
			}
		}
	}
}
int find(int father[], int temp)
{
	int f = temp;
	while (father[f]>0)
		f = father[f];
	return f;
}

template<class T>
void Graph_prac<T>::Kruskal()
{
	int *father = new int[g->Enum];
	int bnf, edf, i;
	Edge rets[MAX];
	int index = 0;
	for (i = 0; i<g->Enum; i++)
		father[i] = 0;
	for (i = 0; i<g->Enum; i++)
	{
		bnf = find(father, g->Wedge[i].v1);
		edf = find(father, g->Wedge[i].v2);
		if (bnf != edf)
		{	
			father[bnf] = edf;
			rets[index++] = g->Wedge[i];
		}
	}
	for (int i = 0; i < index; i++)
		cout << "(" << g->vexs[rets[i].v1] << "," << g->vexs[rets[i].v2] << ")" << " ";
	cout << endl;
	int length = 0;
	for (i = 0; i < index; i++)
		length += rets[i].weight;
	cout << "Kruskal's Length=" << length << endl;
}

#endif //Minimum Cost Spanning Tree

#include <iostream>
#include "UGraph.h"
#include "DGraph.h"
#include "MCSTree.h"
#include "MinPath.h"
using namespace std;

void UGraph_test()
{
	UGraph<char> *g = new UGraph<char>();
	g->CreatGraph();
	g->PrintGraph();
	cout << "深度优先搜索: ";
	g->DFS();
	cout << "广度优先搜索: ";
	g->BFS();
	cout << endl;
	if(g->IsConnected())
		cout << "无向图连通性满足!" << endl;
}

void DGraph_test()
{
	DGraph<char> *g = new DGraph<char>();
	g->CreatDGraph();
	cout << "深度优先搜索: ";
	g->PrintDGraph();
	g->solve();
	if (g->IsStronglyCon())
		cout << "有向图连通性满足!" << endl;
	else
		cout << "不是强连通图！" << endl;
}

void MinSpanningTree_test()
{
	Graph_prac<char> *g=new Graph_prac<char>();
	g->WeightM();
	cout << "Prim算法MCST:" << endl;
	g->Prim();
	cout << endl; cout << endl;
	cout << "Kruskal算法MSCT:" << endl;
	g->Sort();
	g->Kruskal();
	cout << endl;
}

void MinPath_prac()
{
	DGraph_prac<char> *g = new DGraph_prac<char>();
	g->WeightM();
	cout << "floyd算法-MinPath:" << endl;
	g->floyd();
	cout << endl;
	cout << "djikstra算法-MinPath:" << endl;
	g->dijkstra();
	cout << endl;
}

int main()
{
	cout << "UGraph_test():" << endl;
	UGraph_test();
	cout << endl;

	cout << "DGraph_test():" << endl;
	DGraph_test();
	cout << endl;

	cout << "MinSpanningTree_test:" << endl;
	MinSpanningTree_test();
	cout << endl;

	cout << "MinPath_prac:" << endl;
	MinPath_prac();
	cout << endl;

	system("pause");
	return 0;
}


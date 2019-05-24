#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "VGraph.h"
#include "Queue.h"
using namespace std;
#define MAX  30

struct Enode
{
	int ivex;//����ָ��Ķ���λ��
	Enode  *nextEdge;//ָ����һ������ָ��
};

struct Edge
{
	int weight;
	int v1;//ָ��ߵĽ��
	int v2;//��ָ��Ľ��
};

template<class T>
struct Vnode
{
	T data;
	Enode *firstEdge;//����ָ��ĵ�һ����
};

template<class T>
class UGraph : public Vgraph<T>
{
public:
	UGraph();
	void CreatGraph();
	void PrintGraph();
	int getPosition(T val, int Vnum, Vnode<T> *mVexs);
	void LinkLast(Enode *list, Enode *node);
	bool IsConnected();
	int IsDFS[MAX];
	void DFS();
	void BFS();

//protected:
	int Vnum;				//ͼ�Ķ�����Ŀ
	T vexs[MAX];			//��������
	int Enum;				//ͼ�ıߵ���Ŀ
	T edges[MAX][2];	//�ߵ�����
	Edge Wedge[MAX];//��Ȩֵ��
	Vnode<T> mVexs[MAX];//�ڽӱ�AdjList�Ķ���ṹ������
	void DFS(int i, int *visited, Vnode<T> mVexs[]);
};

template<class T>
UGraph<T>::UGraph()
{
	int i;
	cout << "�����붥�����Ŀ:";
	cin >> Vnum;
	cout << "������ߵ���Ŀ:";
	cin >> Enum;
	cout << "���������붥��: " << endl;
	for (i = 0; i < Vnum; i++)
		cin >> vexs[i];
	cout << "����������߼�Ȩֵ:" << endl;
	for (i = 0; i < Enum; i++)
		cin >> edges[i][0] >> edges[i][1] >> Wedge[i].weight;
}

template<class T>
void UGraph<T>::CreatGraph()
{
	int i;
	T c1, c2;
	int p1, p2;
	Enode *node1, *node2;
	for (i = 0; i < Vnum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}
	for (i = 0; i < Enum; i++)
	{
		c1 = edges[i][0];
		c2 = edges[i][1];
		p1 = getPosition(c1, Vnum, mVexs);
		Wedge[i].v1 = p1;
		p2 = getPosition(c2, Vnum, mVexs);
		Wedge[i].v2 = p2;
		node1 = new Enode();
		node1->ivex = p2;
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			LinkLast(mVexs[p1].firstEdge, node1);
		node2 = new Enode();
		node2->ivex = p1;
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			LinkLast(mVexs[p2].firstEdge, node2);
	}
}

template<class T>
int UGraph<T>::getPosition(T val, int Vnum, Vnode<T> mVexs[])
{
	int i;
	for (i = 0; i < Vnum; i++)
	{
		if (mVexs[i].data == val)
			return i;
	}
	return -1;
}

template<class T>
void UGraph<T>::LinkLast(Enode *list, Enode *node)
{
	Enode *p = list;
	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

template<class T>
void UGraph<T>::PrintGraph()
{
	int i;
	Enode *p;
	cout << "����ӱ���ʽ�����" << endl;
	for (i = 0; i < Vnum; i++)
	{
		cout << "(" << i << ")" << mVexs[i].data;
		p = mVexs[i].firstEdge;
		if (p == NULL)
			cout << "Null��";
		while (p != NULL)
		{
			cout << "->" << mVexs[p->ivex].data;
			p = p->nextEdge;
		}
		cout << endl;
	}
}

template<class T>
bool UGraph<T>::IsConnected()
{
	int i;
	for (i = 0; i < Vnum; i++)
	{
		if (IsDFS[i] == 0)
			return false;
	}
	return true;
}

template<class T>
void UGraph<T>::DFS()
{
	int i;
	int visited[MAX];
	for (i = 0; i < Vnum; i++)
	{
		visited[i] = 0;
	}
	for (i = 0; i < Vnum; i++)
	{
		if (visited[i] == 0)
			DFS(i, visited, mVexs);
	}
	cout << endl;
}

template<class T>
void UGraph<T>::DFS(int i, int *visited, Vnode<T> mVexs[])
{
	int j = 0;
	Enode *p;
	cout << mVexs[i].data << " ";
	IsDFS[j++] = 1;
	visited[i] = 1;
	p = mVexs[i].firstEdge;
	while (p != NULL)
	{
		if (visited[p->ivex] == 0)
			DFS(p->ivex, visited, mVexs);
		p = p->nextEdge;
	}
}

template<class T>
void UGraph<T>::BFS()
{
	Enode *p;
	int front = 0;
	int rear = 0;
	int queue[MAX];
	int visited[MAX];
	int i, j;
	for (i = 0; i < Vnum; i++)
	{
		visited[i] = 0;
	}
	for (i = 0; i < Vnum; i++)
	{
		if (visited[i] == 0)
		{
			visited[i] = 1;
			cout << mVexs[i].data << " ";
			queue[rear] = i;
			rear = (rear + 1) % MAX;
		}
		while (front != rear)
		{
			j = queue[front];
			front = (front + 1) % MAX;
			p = mVexs[j].firstEdge;
			while (p != NULL)
			{
				if (visited[p->ivex] == 0)
				{
					visited[p->ivex] = 1;
					cout << mVexs[p->ivex].data << " ";
					queue[rear] = p->ivex;
					rear = (rear + 1) % MAX;
				}
				else
				{
					p = p->nextEdge;
				}
			}
		}
	}
}

#endif
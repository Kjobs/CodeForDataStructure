#ifndef DGRAPH_H
#define DGRAPH_H

#include <iostream>
#include "Stack.h"
#include "UGraph.h"

template<class T>
class DGraph
{
public:
	DGraph();
	~DGraph();
	void CreatDGraph();
	void PrintDGraph();
	int getPosition(T val, int Vnum, Vnode<T> *mVexs);
	void LinkLast(Enode *list, Enode *node);
	void Tarjan(int i);
	void solve();//��Tajan�㷨������ͼ��ǿ��ͨ����
	bool IsStronglyCon();

//protected:
	int Vnum;				//ͼ�Ķ�����Ŀ
	T vexs[MAX];			//��������
	int Enum;				//ͼ�ıߵ���Ŀ
	T edges[MAX][2];	//�ߵ�����
	Edge Wedge[MAX];//��Ȩֵ��
	int DFN[MAX];//������ȱ��
	int Low[MAX];
	int Index = 0;
	int Bcnt;//ǿ��ͨ��������
	Stack<int> Stack;
	bool InStack[MAX];
	Vnode<T> mVexs[MAX];//�ڽӱ�AdjList�Ķ���ṹ������
};

template<class T>
DGraph<T>::DGraph()
{
	int i;
	cout << "�����붥�����Ŀ��";
	cin >> Vnum;
	cout << "������ߵ���Ŀ��";
	cin >> Enum;
	cout << "���������붥��: " << endl;
	for (i = 0; i < Vnum; i++)
		cin >> vexs[i];
	cout << "����������߼�Ȩֵ: " << endl;
	for (i = 0; i < Enum; i++)
		cin >> edges[i][0] >> edges[i][1] >> Wedge[i].weight;
}

template<class T>
DGraph<T>::~DGraph()
{
	delete[] DFN;
	delete[] vexs;
	delete[] edges[][2];
	delete[] mVexs;
}

template<class T>
void DGraph<T>::CreatDGraph()
{
	int i;
	T c1, c2;
	int p1, p2;
	Enode *node1;
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
	}
}

template<class T>
int DGraph<T>::getPosition(T val, int Vnum, Vnode<T> mVexs[])
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
void DGraph<T>::LinkLast(Enode *list, Enode *node)
{
	Enode *p = list;
	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

template<class T>
void DGraph<T>::solve()
{
	int i;
	memset(DFN, 0, sizeof(DFN));
	memset(Low, 0, sizeof(Low));
	memset(InStack, 0, sizeof(InStack));
	for (i = 0; i < Vnum; i++)
		if (!DFN[i])
			Tarjan(i);
}

template<class T>
void DGraph<T>::Tarjan(int i)
{
	int j;
	Enode *p;
	p = mVexs[i].firstEdge;
	Low[i] = DFN[i] = (++Index);
	Stack.Push(i);
	InStack[i] = true;
	while(p)
	{
		j = p->ivex;
		if (!DFN[j])
		{
			Tarjan(j);
			if (Low[j] < Low[i])
				Low[i] = Low[j];
		}
		else if (InStack[j] && DFN[j] < Low[i])
			Low[i] = DFN[j];
		p = p->nextEdge;
	}
	if (DFN[i] == Low[i])
	{
		Bcnt++;
		do{
			j = Stack.Top();
			InStack[j] = false;
		} while (j != i);
	}
}

template<class T>
bool DGraph<T>::IsStronglyCon()
{
	return this->Bcnt == 1;
}

template<class T>
void DGraph<T>::PrintDGraph()
{
	int i;
	Enode *p;
	cout << "����ӱ���ʽ�����" << endl;
	for (i = 0; i < Vnum; i++)
	{
		cout << "(" << i << ")" << mVexs[i].data;
		p = mVexs[i].firstEdge;
		if (p == NULL)
			cout << "->" << "Null��";
		while (p != NULL)
		{
			cout << "->" << mVexs[p->ivex].data;
			p = p->nextEdge;
		}
		cout << endl;
	}
}

#endif
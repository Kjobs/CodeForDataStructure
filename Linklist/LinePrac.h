#ifndef LINEPRAC_H
#define LINEPRAC_H

#include <iostream>
#include <string>
#include "LinkList.h"

void GetNext(string& s, int *next)
{
	int i, j;
	i = 1;
	j = 0;
	next[1] = 0;
	while (i < s.size())
	{
		while (j > 0 && s[i] != s[j])
			j = next[j];
		if (s[i] == s[j])
			next[i + 1] = j + 1;
		else
			next[i + 1] = j;
		i++;
	}
}

int KMP(string& s, string& t)
{
	int i, j;
	i = 0;
	j = 0;
	int n = s.size();
	int *next = new int[n];
	GetNext(t, next);
	while (i < s.size() && j < t.size())
	{
		if (j == 0 || s[i] == t[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j >= t.size())
	{
		int index = i - t.size();
		cout << "Matching Successed!" << endl;
		cout << "Return pos:" << index << endl;
		return index;
	}
	else
	{
		cout << "Matching Failed!" << endl;
		return -1;
	}
}

#define MAXSIZE 15//最大容量
using namespace std;

class PriQueue
{
public:
	PriQueue();
	void MaxInsert(int item);
	void MinInsert(int item);
	int GetPriorElement();
	int Max_Delete();
	int Min_Delete();
	void Print();
private:
	int  Elements[MAXSIZE];
	int n;//堆元素个数
};

PriQueue::PriQueue()
{
	n = 0;
}
void PriQueue::MaxInsert(int item)
{
	int i;
	if (n != MAXSIZE)
	{
		i = n + 1;
		while (i != 1 && item > Elements[i / 2])
		{
			Elements[i] = Elements[i / 2];
			i = i / 2;
		}
		Elements[i] = item;
		n++;
	}
}

int PriQueue::Max_Delete()
{
	int parent = 1, child = 2;
	int element, tmp;
	if (n != 0)
	{
		element = Elements[1];
		tmp = Elements[n--];
		while (child <= n)
		{
			if (child < n && Elements[child] < Elements[child + 1])
				child++;
			if (tmp > Elements[child])
				break;
			Elements[parent] = Elements[child];
			parent = child;
			child = child * 2;
		}
		Elements[parent] = tmp;
		return element;
	}
}

void PriQueue::MinInsert(int item)
{
	int i;
	if (n != MAXSIZE)
	{
		i = n + 1;
		while (i != 1 && item < Elements[i / 2])
		{
			Elements[i] = Elements[i / 2];
			i = i / 2;
		}
		Elements[i] = item;
		n++;
	}
}

int PriQueue::Min_Delete()
{
	int parent = 1, child = 2;
	int element, tmp;
	if (n != 0)
	{
		element = Elements[1];
		tmp = Elements[n--];
		while (child <= n)
		{
			if (child < n && Elements[child] > Elements[child + 1])
				child++;
			if (tmp < Elements[child])
				break;
			Elements[parent] = Elements[child];
			parent = child;
			child = child * 2;
		}
		Elements[parent] = tmp;
		return element;
	}
}

int PriQueue::GetPriorElement()
{
	return Elements[1];
}

void PriQueue::Print()
{
	int i;
	cout << "Order Print:";
	for (i = 1; i <= n; i++)
	{
		cout << Elements[i] << " ";
	}
	cout << endl;
}


#endif
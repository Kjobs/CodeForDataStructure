#ifndef LINKLIST_HEAD
#define LINKLIST_HEAD

#include "Line.h"
#include <iostream>
using namespace std;

template<typename T>
struct Node
{
	T Data;
	Node* next = NULL;
};

template<typename T>
class LinkList : public Line<T>
{
	Node<T>* head;
public:
	LinkList();
	bool empty();
	void Insert(T val, int position);
	void Delete(T val, int position);
	int Searchindex(T val);
	T Searchval(int position);
	int getSize();
	void Print();
private:
	int num;
};

template<typename T>
LinkList<T>::LinkList()
{
	num = 0;
}

template<typename T>
bool LinkList<T>::empty()
{
	if (num == 0)
		return true;
	return false;
}

template<typename T>
void LinkList<T>::Insert(T val, int position)
{
	int i = 0;
	Node<T>* tmp;
	Node<T>* p = head;
	if (p == NULL)
	{
		p = new Node<T>;
		p->Data = val;
		head = p;
		num += 1;
		return;
	}
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		i = i + 1;
		if (i == num)
		{
			p = tmp;
			p->next = new Node<T>;
			p->next->Data = val;
			p = p->next->next;
			num = num + 1;
			return;
		}
		if (p != NULL)
		{
			if (i == position  && num > position)
			{
				p = tmp;
				tmp = new Node<T>;
				tmp->next = p->next;
				tmp->Data = val;
				p->next = tmp;
				num = num + 1;
				return;
			}
		}
	}
}

template<typename T>
void LinkList<T>::Delete(T val, int position)
{
	int i = 0;
	Node<T> *p, *tmp;
	p = head;
	while (p != NULL)
	{	
		if (position == 0)
		{
			if (p->next == NULL)
			{
				num--;
				head = NULL;
				return;
			}
			else
			{
				tmp = p->next;
				delete p;
				num--;
				head = tmp;
				return;
			}
		}
		if ( i == position - 1 )
		{
			tmp = p->next;
			p->next = p->next->next;
			num--;
			delete tmp;
		}
		p = p->next;
		i = i + 1;
	}
}
template<typename T>
int LinkList<T>::Searchindex(T val)
{
	Node<T> *p = head;
	int i = 0;
	while (p != NULL)
	{
		if (p->Data == val)
			return i;
		p = p->next;
		i = i + 1;
	}
	cout << "搜索失败！" << endl;
	return -1;
}

template<typename T>
T LinkList<T>::Searchval(int position)
{
	Node<T> *p = head;
	int i = 0;
	while (p != NULL)
	{
		if (i == position)
			return p->Data;
		p = p->next;
		i = i + 1;
	}
	cout << "搜索失败！" << endl;
	return NULL;
}

template<typename T>
int LinkList<T>::getSize()
{
	return num;
}

template<typename T>
void LinkList<T>::Print()
{
	Node<T> *p;
	p = head;
	while (p != NULL)
	{
		cout << p->Data << " ";
		p = p->next;
	}
	cout << endl;
}


#endif

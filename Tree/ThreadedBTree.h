#ifndef THREADEDBINARYTREE_H
#define  THREADEDBINARYTREE_H

#include <iostream>
#include "LinkBinaryTree.h"

template<class T>
class HNode
{
public:
	T val;
	HNode *lchild;
	HNode *rchild;
	bool ltag, rtag;
	HNode();
};

template<class T>
HNode<T>::HNode()
{
	lchild = rchild = NULL;
	ltag = rtag = false;
}

template<class T>
class ThreadedBTree
{
public:
	ThreadedBTree();
	bool Empty();
	int Size();
	void CreatHBT();	
	void Insert(T x);
	void visit(HNode<T> *p);
	void pre_threading(HNode<T> *p);
	void preOrder_threading();
	HNode<T>* preNext(HNode<T> *p);
	void preOrder();
	void post_threading(HNode<T> *p);
	void postOrder_threading();
	HNode<T>* GetParent(HNode<T> *p);
	HNode<T>* postNext(HNode<T> *p);
	void postOrder();
	
private:
	HNode<T> *head;
	HNode<T> *root;
	HNode<T> *current;
	int HBTsize;
};

template<class T>
ThreadedBTree<T>::ThreadedBTree()
{
	head = new HNode<T>;
	head->lchild = head->rchild = head;
	head->ltag = false;
	head->rtag = false;
	root = NULL;
}

template<class T>
bool ThreadedBTree<T>::Empty()
{
	return HBTsize == 0;
}

template<class T>
int ThreadedBTree<T>::Size()
{
	return HBTsize;
}

template<class T>
void ThreadedBTree<T>::Insert(T x)
{
	if (root == NULL)
	{
		root = new HNode<T>;
		head->lchild = root;
		root->val = x;
		head->ltag = true;
	}
	else
	{
		HNode<T> *p = root;
		Queue<HNode<T>*> Queue;
		Queue.EnQueue(p);
		HNode<T> *q = NULL;
		while (!Queue.empty())
		{
			if (p->lchild == NULL || p->rchild == NULL)
			{
				q = p;
				break;
			}
			if (p->lchild != NULL && p->rchild != NULL)
			{
				p = p->lchild;
				Queue.EnQueue(p);
			}
		}
		if (q->lchild == NULL)
		{
			q->lchild = new HNode<T>;
			q->lchild->val = x;
			q->ltag = true;
			q = q->lchild;
			q->lchild = q->rchild = NULL;
		}
		else
		{
			q->rchild = new HNode<T>;
			q->rchild->val = x;
			q->rtag = true;
			q = q->rchild;
			q->lchild = q->rchild = NULL;
		}
	}
	HBTsize++;
}

template<class T>
void ThreadedBTree<T>::visit(HNode<T> *p)
{
	cout << p->val << " ";
}

template<class T>
void ThreadedBTree<T>::pre_threading(HNode<T> *p)
{
	if (p)
	{
		if (p->lchild == NULL)
		{
			p->ltag = false;
			p->lchild = current;
		}
		if (current->rchild == NULL)
		{
			current->rtag = false;
			current->rchild = p;
		}
		current = p;
		if (p->ltag == true)
			pre_threading(p->lchild);
		if (p->rtag == true)
			pre_threading(p->rchild);
	}
}

template<class T>
void ThreadedBTree<T>::preOrder_threading()
{
	head->ltag = true;
	head->rtag = false;
	head->rchild = head;
	if (root == NULL)
		head->lchild = head;
	else
	{
		head->lchild = root;
		current = head;
		pre_threading(root);
		head->rchild = head;
	}
}

template<class T>
void ThreadedBTree<T>::preOrder()
{
	HNode<T> *p;
	p = head->lchild;
	cout << "Output the PreOrder-ThreadedBTree:";
	while (p != head && p != NULL)
	{
		visit(p);
		if (p->ltag == true)
			p = p->lchild;
		else
			p = p->rchild;
	}
	cout << endl;
}

template<class T>
void ThreadedBTree<T>::post_threading(HNode<T> *p)
{
	if (p)
	{
		post_threading(p->lchild);
		post_threading(p->rchild);
		if (p->lchild == NULL)
		{
			p->ltag = false;
			p->lchild = current;
		}
		if (current->rchild == NULL)
		{
			current->rtag = false;
			current->rchild = p;
		}
		current = p;
	}
}

template<class T>
void ThreadedBTree<T>::postOrder_threading()
{
	head->ltag = true;
	head->rtag = false;
	head->rchild = head;
	if (root == NULL)
	{
		head->lchild = head;
	}
	else
	{
		head->lchild = root;
		current = head;
		post_threading(root);
		head->rchild = current;
	}
}
template<class T>
HNode<T>* ThreadedBTree<T>::GetParent(HNode<T> *p)
{
	HNode<T> *temp = head;
	if (head->lchild == p)
		return temp;
	temp = temp->lchild;
	while (temp->lchild != p && temp->rchild != p)
	{
		if (temp->rtag == true)
			temp = temp->rchild;
		else
			temp = temp->lchild;
	}
	return temp;
}

template<class T>
void ThreadedBTree<T>::postOrder()
{
	HNode<T> *p,*par;
	p = head->lchild;
	cout << "Output the PostOrder-ThreadedBTree:";
	while (true)
	{
		while (p->ltag == true)
			p = p->lchild;
		if (p->rtag == true)
			p = p->rchild;
		else
			break;
	}
	while (p != head)
	{
		visit(p);
		par = GetParent(p);
		if (par == head)
			break;
		else if (par->rchild == p || par->rtag == false)
		{
			p = par;
		}
		else{
			while (par->rtag == true)
			{
				par = par->rchild;
				while (par->ltag == true)
				{
					par = par->lchild;
				}
			}
			p = par;
		}
	}
	cout << endl;
}

#endif
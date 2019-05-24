#ifndef LINKBINARYTREE_H
#define LINKBINARYTREE_H

#include "BinaryTree.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
using namespace std;

template<typename T>
class BTNode
{
public:
	T val;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
	BTNode();
	BTNode(T element);
};

template<class T>
BTNode<T>::BTNode()
{
	val = NULL;
	lchild = rchild = NULL;
}

template<class T>
BTNode<T>::BTNode(T element)
{
	this->val = element;
	lchild = rchild = NULL;
}

template<class T>
class LinkBinaryTree : public BinaryTree
{
public:
	LinkBinaryTree();
	LinkBinaryTree(BTNode<T> *t);
	~LinkBinaryTree();
	bool Empty() const;
	int Size() const;
	void visit(BTNode<T>* t);
	void preOrder(){ preOrder(root); }
	void inOrder(){ inOrder(root); }
	void postOrder(){ postOrder(root); }
	void levelOrder(){ levelOrder(root); }
	BTNode<T> * reRoot();
private:
	BTNode<T> *root;
	int BTsize;
	void CreateBT(BTNode<T> **t);
	void preOrder(BTNode<T>* t);
	void inOrder(BTNode<T>* t);
	void postOrder(BTNode<T>* t);
	void levelOrder(BTNode<T>* t);
};

template<class T>
LinkBinaryTree<T>::LinkBinaryTree()
{
	CreateBT(&root);
}

template<class T>
LinkBinaryTree<T>::LinkBinaryTree(BTNode<T> *t)
{
	root = t;
}

template<class T>
LinkBinaryTree<T>::~LinkBinaryTree()
{
	delete[] root;
	BTsize = 0;
}

template<class T>
bool LinkBinaryTree<T>::Empty() const
{
	return BTsize == 0;
}

template<class T>
int LinkBinaryTree<T>::Size() const
{
	return BTsize;
}

template<class T>
void LinkBinaryTree<T>::CreateBT(BTNode<T> **t)
{
	T data; 
	cin.clear();
	cin.sync();
	if (cin >> data)
	{
		*t = new BTNode<T>(data);
		BTsize++;
		if (*t != NULL)
		{
			CreateBT(&((*t)->lchild));
			CreateBT(&((*t)->rchild));
		}
		else
			exit(-1);
	}
	else
	{
		*t = NULL;
	}
}

template<class T>
BTNode<T> * LinkBinaryTree<T>::reRoot()
{
	return root;
}

template<class T>
void LinkBinaryTree<T>::visit(BTNode<T>* t)
{
	cout << t->val << " ";
}

template<class T>
void LinkBinaryTree<T>::preOrder(BTNode<T>* t)
{
	if (t != NULL)
	{
		visit(t);
		preOrder(t->lchild);
		preOrder(t->rchild);
	}
}

template<class T>
void LinkBinaryTree<T>::inOrder(BTNode<T>* t)
{
	if (t != NULL)
	{
		inOrder(t->lchild);
		visit(t);
		inOrder(t->rchild);
	}
}

template<class T>
void LinkBinaryTree<T>::postOrder(BTNode<T>* t)
{
	if (t != NULL)
	{
		postOrder(t->lchild);
		postOrder(t->rchild);
		visit(t);
	}
}

template<class T>
void LinkBinaryTree<T>::levelOrder(BTNode<T>* t)
{
	BTNode<T> *p;
	Queue<BTNode<T>*> Queue;
	Queue.EnQueue(t);
	while (!Queue.empty())
	{
		p = Queue.GetFirst();
		visit(p);
		if (p->lchild != NULL)
			Queue.EnQueue(p->lchild);
		if (p->rchild != NULL)
			Queue.EnQueue(p->rchild);
	}
}

#endif
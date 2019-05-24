#ifndef EXCHANGETREE_H
#define EXCHANGETREE_H

template<class T>
class Node
{
	T data;
	int parent;
	int lchild;
	int brother;
};

template<class T>
class Tree
{
public:
	Tree();
	void CreateTree(){CreateTree(root)};
	void Insert(T val);
private:
	Node<T>* root;
	void CreateTree(Node<T> *root);
	Node<T> *array;
	int size;
};

template<class T>


#endif
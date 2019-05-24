#ifndef BINARYTREE_H
#define BINARYBTREE_H

class BinaryTree
{
	virtual bool Empty() const = 0;
	virtual int Size() const = 0;
	virtual void preOrder() = 0;
	virtual void inOrder() = 0;
	virtual void postOrder() = 0;
	virtual void levelOrder() = 0;
};

#endif
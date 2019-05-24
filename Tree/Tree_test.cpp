#include "LinkBinaryTree.h"
#include "ThreadedBTree.h"
#include "Huffman.h"
#include <iostream>
using namespace std;

void BTtest()
{
	LinkBinaryTree<int> *t = new LinkBinaryTree<int>();
	cout << "PreOrder  :";
	t->preOrder();
	cout << endl;
	cout << "InOrder   :";
	t->inOrder();
	cout << endl;
	cout << "PostOrder :";
	t->postOrder();
	cout << endl;
	cout << "LevelOrder:";
	t->levelOrder();
	int n;
	n = t->Size();
	cout << endl << n << endl;
}

void HBTpretest()
{
	ThreadedBTree<int> ht;
	ht.Insert(90);
	ht.Insert(45);
	ht.Insert(56);
	ht.Insert(65);
	ht.Insert(75);
	cout << "Input Numbers:90 45 56 65 75" << endl;
	ht.preOrder_threading();
	ht.preOrder();
}

void HBTposttest()
{
	ThreadedBTree<int> ht;
	ht.Insert(90);
	ht.Insert(45);
	ht.Insert(56);
	ht.Insert(65);
	ht.Insert(75);
	cout << "Input Numbers:90 45 56 65 75" << endl;
	ht.postOrder_threading();
	ht.postOrder();
}
void Huffmantest()
{
	HuffmanT T;
	HuffCode HC;
	int n;
	InitHT(T);
	CalInf(T, n);
	CreatHT(T, n);
	CreatHCode(T, HC, n);
	EditCode(T, HC, n);
	DeCode(T, HC, n);
}

int main()
{
	cout << "BinaryTree_test():" << endl;
	BTtest();
	cout << endl;
	
	cout << "PreThreaded-Binary-Tree_test():" << endl;
	HBTpretest();
	cout << endl;
	
	cout << "PostThreaded-Binary-Tree_rest():" << endl;
	HBTposttest();
	cout << endl;

	cout << "Huffman-Encode_test():" << endl;
	Huffmantest();
	cout << endl;

	system("pause");
	return 0;
}
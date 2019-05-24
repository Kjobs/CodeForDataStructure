#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <fstream>
#include "LinePrac.h"
#define N 100       //设置叶节点最大数
#define M 2*(N)-1   //根据叶节点得到结点总数
#define MAX 20      //哈夫曼编码长度最大值
using namespace std;

struct HTnode
{
	char value;
	int  weight;
	int lchild;
	int rchild;
	int parent;
};
typedef HTnode HuffmanT[M];

struct Hcode
{//哈夫曼编码结构，存储字符编码表
	char Bits[MAX];//编码字符集
	int start;
	char val;
	int len;
};
typedef Hcode HuffCode[N];

void InitHT(HuffmanT T)
{//初始化哈夫曼树
	int i;
	for (i = 0; i < N; i++)
	{
		T[i].weight = 0;
		T[i].lchild = -1;
		T[i].parent = -1;
		T[i].rchild = -1;
		T[i].value = -1;
	}
}

void CalInf(HuffmanT &T, int &n)
{//读取“read.txt”文件，统计字符数量和每个字符出现的次数
	int i, j, k, isrep;
	ifstream infile("read.txt");
	if (!infile)
	{
		cout << "openerror!";
		exit(0);
	}
	char ch;
	i = 0;
	infile >> noskipws;
	while (infile >> ch)
	{
		isrep = 0;
		for (j = 0; j < i; j++)
		{
			if (ch == T[j].value)
			{
				isrep = 1;
				k = j;
				break;
			}
		}
		if (isrep == 1)//表示出现重复的字符
			T[k].weight += 1;
		else
		{
			T[i].value = ch;
			T[i].weight += 1;
			i++;
		}
	}
	n = i;
	infile.close();
}

void SelecteMin(HuffmanT &T, int num, int &p1, int &p2)
{
	PriQueue q;
	int m,n, i;
	for (i = 0; i <= num; i++)
		if (T[i].parent == -1)
			q.MinInsert(T[i].weight);
	m = q.Min_Delete();
	for (i = 0; i <= num; i++)
	{
		if (m == T[i].weight)
			p1 = i;
	}
	n = q.Min_Delete();
	for (i = 0; i <= num; i++)
	{
		if (n == T[i].weight && i != p1)
			p2 = i;
	}
}
void CreatHT(HuffmanT &T, int n)
{
	int i, p1, p2;
	for (i = n; i < 2 * n - 1; i++)
	{
		SelecteMin(T, i - 1, p1, p2);
		T[p1].parent = T[p2].parent = i;
		T[i].lchild = p1;
		T[i].rchild = p2;
		T[i].weight = T[p1].weight + T[p2].weight;
	}
}
void CreatHCode(HuffmanT T, HuffCode HC, int n)
{
	int i, j, child, parent;
	Hcode *cd;
	cd = new Hcode;
	for (i = 0; i < n; i++)
	{
		cd->start = 0;
		cd->val = T[i].value;
		child = i;
		parent = T[child].parent;
		while (parent != -1)
		{
			if (T[parent].lchild == child)
				cd->Bits[cd->start] = '0';
			else
				cd->Bits[cd->start] = '1';
			cd->start += 1;
			child = parent;
			parent = T[child].parent;
		}
		cout << cd->val << ":";
		cd->len = cd->start;
		for (j = cd->start - 1; j >= 0; j--)
		{
			HC[i].Bits[cd->start - j - 1] = cd->Bits[j];
			cout << cd->Bits[j];
		}
		cout << endl;
		HC[i].len = cd->len;
		HC[i].start = cd->start;
		HC[i].val = cd->val;
	}
}
void EditCode(HuffmanT T, HuffCode HC, int n)
{
	int i, j;
	char ch;
	ifstream  infile("read.txt");
	if (!infile)
	{
		cout << "Open Error!";
		exit(1);
	}
	ofstream outfile("Editcode.txt");
	if (!outfile)
	{
		cout << "Output Error!";
		exit(1);
	}
	infile >> noskipws;
	while (infile >> ch)
	{
		for (i = 0; i < n; i++)
		{
			if (ch == HC[i].val)
				for (j = 0; j < HC[i].len; j++)
					outfile << HC[i].Bits[j];
		}
		outfile << " ";
	}
	infile.close();
	outfile.close();
}
void DeCode(HuffmanT T, HuffCode HC, int n)
{
	char ch;
	int i;
	ifstream infile("Editcode.txt");
	if (!infile)
	{
		cout << "Open Error!";
		exit(1);
	}
	ofstream outfile("Decode.txt");
	if (!outfile)
	{
		cout << "Output Error!";
		exit(1);
	}
	i = 2 * n - 2;
	infile >> noskipws;
	while (infile >> ch)
	{
		if (ch != ' ')
		{
			if (ch == '0')
				i = T[i].lchild;
			else if (ch == '1')
				i = T[i].rchild;
			if (T[i].lchild == -1)
			{
				outfile << T[i].value;
				i = 2 * n - 2;
			}
		}
	}
	infile.close();
	outfile.close();
}

#endif
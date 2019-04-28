#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include "TheSameFunc.h"


template<class T>
void Swap(T &x, T &y)
{
	T temp;
	temp = x;
	x = y;
	y = temp;
}

template<class T>
int FindPivot(T Num[], int i, int j, bool (*Compare)(T x, T y))
{//寻找基准元素，并返回其在序列中下标位置
	T firstkey;
	int k;
	firstkey = Num[i];
	for (k = i + 1; k <= j; k++)
	{
		if (Compare(Num[k],firstkey))
			return k;
		else if (!Compare(Num[k], firstkey))
			return i;
	}
	return -1;
}

template<class T>
int Partition(T Num[], int i, int j, T pivot, bool (*Compare)(T x, T y))
{//序列划分，返回划分位置下标
	int l, r;
	l = i; r = j;
	do{
		Swap(Num[l], Num[r]);//根据基准元素大小进行置换
		while (!Compare(Num[l], pivot))
			l = l + 1;
		while (Compare(Num[r], pivot))
			r = r - 1;
	} while (l <= r);
	return l;
}

template<class T>
void QuickSort(T Num[], int i, int j, bool(*Compare)(T x, T y))
{//快速排序
	T pivot;
	int pivotindex;
	int k;
	pivotindex = FindPivot(Num, i, j, Compare);
	if (pivotindex != -1)
	{
		pivot = Num[pivotindex];
		k = Partition(Num, i, j, pivot, Compare);
		QuickSort(Num, i, k - 1,Compare);
		QuickSort(Num, k, j,Compare);
	}
}
#endif

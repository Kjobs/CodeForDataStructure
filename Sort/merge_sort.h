#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
#include "TheSameFunc.h"

template<class T>
void Merge(int s, int m, int t, T A[], T B[])
{
	int i = s;
	int j = m + 1;
	int k = s;
	while (i <= m && j <= t)
		B[k++] = (A[i] <= A[j]) ? A[i++] : A[j++];
	while (i <= m) 
		B[k++] = A[i++];
	while (j <= t) 
		B[k++] = A[j++];
}

template<class T>
void MergePass(int n, int h, T A[], T B[])
{
	int i, t;
	for (i = 0; i + 2 * h - 1 <= n; i += 2 * h)
		Merge(i, i + h - 1, i + 2 * h - 1, A, B);
	if (i + h - 1< n)
		Merge(i, i + h - 1, n, A, B);
	else 
		for (t = i; t <= n; t++)
			B[t] = A[t];
}

template<class T>
void MergeSort(int n, T A[])
{
	int h = 1;
	int B[MAX];
	while (h< n)
	{
		MergePass(n, h, A, B);
		h = 2 * h;
		MergePass(n, h, B, A); 
		h = 2 * h;
	}
}

#endif

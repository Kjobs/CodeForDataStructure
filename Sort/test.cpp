#include <iostream>
#include "quick_sort.h"
#include "merge_sort.h"
#include "the_same_func.h"
using namespace std;



int main()
{
	int n = 30000;
	int num[MAX];

	clock_t t1, t2;	
	CreatRand(num, n);
	t1 = clock();
	QuickSort(num, 0, n-1,com);
	t2 = clock();
	cout << "快速排序运行时间：" << t2 - t1 << endl;

	clock_t t3,t4;
	CreatRand(num, n);
	t3 = clock();
	MergeSort(n-1,num);
	t4 = clock();
	cout << "归并排序运行时间：" << t4 - t3 << endl;


	system("pause");
	return 0;
}

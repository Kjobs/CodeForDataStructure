#include "Array.h"
#include "LinkList.h"
#include "Queue.h"
#include "Stack.h"
#include "LinePrac.h"
#include <string>
#define N 15


void Array_test()
{
	Array<int> L1;
	int i, m;
	for (i = 0; i < N; i++)
	{
		m = rand() % 100 + 1;
		L1.Insert(m, i);
	}
	cout << "The number of the Array is:" << L1.getSize() << endl;
	L1.Print();
	cout << "After delete the first elements" << endl;
	L1.Delete(L1.Getval(0), 0);
	L1.Print();
}

void LinkList_test()
{
	LinkList<int> L2;
	int i, m;
	for (i = 0; i < N; i++)
	{
		m = rand() % 500 + 1;
		L2.Insert(m, i);
	}
	cout << "The number of the Array is:" << L2.getSize() << endl;
	L2.Print();
	cout << "After delete the first elements" << endl;
	L2.Delete(L2.Searchval(0), 0);
	L2.Print();
}

void KMP()
{
	string str1, str2;
	str1 = "ly abcdfsd";
	str2 = "abcd";
	KMP(str1, str2);
}

void MAX_PriorityQueue()
{
	PriQueue Q;
	Q.MaxInsert(4);
	Q.MaxInsert(25);
	Q.MaxInsert(3);
	Q.MaxInsert(35);
	Q.MaxInsert(152);
	Q.MaxInsert(45);
	Q.MaxInsert(76);
	Q.MaxInsert(18);
	Q.Print();
	int x = Q.GetPriorElement();
	cout << "Output the prior element:" << x << endl;
	x = Q.Max_Delete();
	cout << "After delete : " << x << endl;
	Q.Print();
	cout << endl;
}

void Min_PriorityQueue()
{
	PriQueue Q;
	Q.MinInsert(4);
	Q.MinInsert(25);
	Q.MinInsert(3);
	Q.MinInsert(35);
	Q.MinInsert(152);
	Q.MinInsert(45);
	Q.MinInsert(76);
	Q.MinInsert(18);
	Q.Print();
	int y = Q.GetPriorElement();
	cout << "Output the prior element:" << y << endl;
	y = Q.Min_Delete();
	cout << "After delete : " << y << endl;
	Q.Print();
	cout << endl;
}

int main()
{
	cout << "Array_test() :" << endl;
	Array_test();
	cout << endl;

	cout << "LinkList_test():" << endl;
	LinkList_test();
	cout << endl;

	cout << "KMP_test():" << endl;
	KMP();
	cout << endl;

	cout << "PriorityQueue_test():" << endl;
	MAX_PriorityQueue();
	cout << endl;
	Min_PriorityQueue();
	cout << endl;

	system("pause");
	return 0;
}
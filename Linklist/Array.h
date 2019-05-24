#ifndef ARRAY_H
#define ARRAY_H

#include "Line.h"
#include <iostream>
#define maxsize 15
using namespace std;

template<typename T>
class Array :public Line<T>
{
public:
	Array() :num(0){};
	bool empty();
	void Insert(T val, int position);
	void Delete(T val, int position);
	int GetPos(T val);
	T Getval(int position);
	void Print();
	int getSize();
private:
	int elements[maxsize];
	int num;
};

template<typename T>
bool Array<T>::empty()
{
	if (num == 0)
		return true;
	return false;
}

template<typename T>
void Array<T>::Insert(T val ,int position)
{
	int i;
	if (position > num)
		return;
	for (i = num; i > position; i--)
	{
		elements[i] = elements[i - 1];
	}
	elements[position] = val;
	num++;
}

template<typename T>
void Array<T>::Delete(T val, int position)
{
	int i;
	if (position > num)
		return;
	for (i = position; i < num; i++)
	{
		elements[i] = elements[i + 1];
	}
	num--;
}

template<class T>
T Array<T>::Getval(int position)
{
	return elements[position];
}

template<typename T>
int Array<T>::GetPos(T val)
{
	int mid , max , min;
	min = 0;
	max = num - 1;
	while (min != max)
	{
		mid = (min + max) / 2;
		if (val < elements[mid])
			max = mid - 1;
		else if (val > elements[mid])
			min = mid + 1;
		else
			return mid;
	}
}

template<typename T>
int Array<T>::getSize()
{
	return num;
}

template<typename T>
void Array<T>::Print()
{
	int i;
	for (i = 0; i < num; i++)
	{
		cout << elements[i] << " ";
	}
	cout << endl;
}
#endif
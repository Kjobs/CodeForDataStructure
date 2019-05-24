#ifndef QUEUE_HEAD
#define QUEUE_HEAD

#include "LinkList.h"

template<typename T>
class Queue
{
public:
	Queue();
	bool empty();
	void EnQueue(T val);
	void DeQueue();
	T GetFirst();
	int getSize();
private:
	int QEleNum;
	LinkList<T> L;
};

template<typename T>
Queue<T>::Queue()
{
	QEleNum = 0;
}
template<typename T>
bool Queue<T>::empty()
{
	if (QEleNum == 0)
		return true;
	return false;
}

template<typename T>
void Queue<T>::EnQueue(T val)
{
	L.Insert(val, QEleNum);
	QEleNum += 1;
}

template<typename T>
void Queue<T>::DeQueue()
{
	L.Delete(L.Searchval(0), 0);
	QEleNum--;
}

template<typename T>
T Queue<T>::GetFirst()
{
	T m;
  	QEleNum -= 1;
	m = L.Searchval(0);
	L.Delete(m, 0);
	return m;
}

template<typename T>
int Queue<T>::getSize()
{
	return QEleNum;
}

#endif

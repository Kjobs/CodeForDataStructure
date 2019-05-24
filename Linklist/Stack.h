#ifndef STACK_HEAD
#define STACK_HEAD

#include "LinkList.h"

template<typename T>
class Stack
{
public:
	Stack();
	bool empty();
	int Getsize();
	void Push(T val);
	void Pop();
	T Top();
	void PrintS();
private:
	int EleNum;
	LinkList<T> L;
};

template<typename T>
Stack<T>::Stack()
{
	EleNum = 0;
}

template<typename T>
bool Stack<T>::empty()
{
	if (EleNum == 0)
		return true;
	return false;
}

template<typename T>
int Stack<T>::Getsize()
{
	return EleNum;
}

template<typename T>
void Stack<T>::Push(T val)
{
	L.Insert(val, EleNum);
	EleNum += 1;	
}

template<typename T>
T Stack<T>::Top()
{
	T m;
	m = L.Searchval(--EleNum);
	L.Delete(m, EleNum);
	return m;
}

template<typename T>
void Stack<T>::Pop()
{
	T m;
	m = L.Searchval(--EleNum);
	L.Delete(m, EleNum);
}

#endif

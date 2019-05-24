#ifndef LINEAR_H
#define LINEAR_H

/*线性表Line.h头文件，包含线性表Line类
*成员函数GetSize获取线性表长度
*其他的如函数名所示
*/

template<typename T>
class Line
{
public:
	virtual bool empty() = 0;
	virtual void Insert(T val, int position) = 0;
	virtual void Delete(T val, int position) = 0;
	virtual int getSize() = 0;
	virtual void Print() = 0;
};

#endif

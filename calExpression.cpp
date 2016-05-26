/*
*C++
*链表应用
*表达式求值
*/
#include <iostream>
#include <string>
#define maxlength 20
using namespace std;

//定义一个char类型的栈，存储结构用数组实现
struct STACK
{
	int top;
	char eleData[maxlength];
};

//定义一个double类型的栈，存储结构用数组实现
struct numStack
{
	int top;
	double element[maxlength];
};

void MakeNull(STACK &S)
{
  //char数组置空
	S.top=maxlength;
}

void MakeNull(numStack &S)
{
  //double数组置空
	S.top=maxlength;
}

bool Empty(STACK S)
{
	if (S.top>maxlength-1)
		return 1;
	else 
		return 0;
}

bool Empty(numStack S)
{
	if (S.top>maxlength-1)
		return 1;
	else 
		return 0;
}

void PushNum(double x, numStack &S)
{
	if (S.top==0)
		cout << "Stack is full!"<<endl;
	else
		S.top = S.top -1;
	   S.element[S.top]=x;
}
void Push(char x, STACK &S)
{
	if (S.top==0)
		cout << "Stack is full!"<<endl;
	else
		S.top = S.top -1;
	   S.eleData[S.top]=x;
}
char Pop(STACK S)
{
	char x;
	if (Empty(S))
        return NULL;
	else 
		x = S.eleData[S.top];
	   S.top=S.top+1;
		return x;
}
double PopNum(numStack & S)
{
	double x;
	if (Empty(S))
        return NULL;
	else 
		x = S.element[S.top];
	   S.top=S.top+1;
		return x;
}
/*设定各个运算符的优先级大小*/
int  Priority(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 0;break;
	case '*':
	case '/':
		return 1;break;
	default:
		return -1;break;
	}
}
/*中缀表达式转换为后缀表达式：用数组实现堆栈，将运算符压栈入栈，
两个表达式分别用char数组infixstr和poststr表示，传入参数m用以计算后缀表达式长度*/
void InfixtoPostfix(char infixstr[] , char poststr[],int n,int &m)
{
	int  i , j=0;
	STACK S;
	MakeNull(S);
	for (i = 0; i < n; i++)
	{
		if (infixstr[i] >= '0' && infixstr[i] <= '9'||infixstr[i]=='.')
		{
			poststr[j++] = infixstr[i];
			m++;
		}
		/*处理运算符'+''-''*''/'*/
		else if (infixstr[i] == '+' || infixstr[i] == '-' || infixstr[i] == '*' || infixstr[i] == '/')
		{
			poststr[j++] = ' ';
			m++;
			if (Empty(S)||Priority(infixstr[i])>Priority(S.eleData[S.top]))
				{
					Push(infixstr[i],S);
				}
				else
				{
					while (Priority(infixstr[i]) <= Priority(S.eleData[S.top])||!Empty(S))
					{
						poststr[j++] = Pop(S);
						m++;
						S.top=S.top+1;
					}
					Push(infixstr[i],S);
				}
		}
		/*处理括号*/
		else if (infixstr[i] == '(')
			Push(infixstr[i],S);
		else if (infixstr[i] == ')')
		{
			while (S.eleData[S.top] != '(')
			{
				poststr[j++] = S.eleData[S.top];
				m++;
				S.top=S.top+1;
			}
			S.top=S.top+1;
		}
  	}
	/*最后将运算符依次出栈*/
	while (!Empty(S))
	{
		poststr[j++] = S.eleData[S.top];
		m++;
		S.top=S.top+1;
	}
}
/*定义一个取数的函数以便处理小数和多位数*/
double Getnum(char str[],int *i)
{
	double n=0;
	int count=0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (str[(*i)] == '.')
	{
		(*i)++;
		while (str[*i] >= '0'&&str[*i] <= '9')
		{
			count -= 1;
			n +=(str[*i]-'0') * pow(10, count) ;
			(*i)++;
		}
	}
	return n;
}
/*函数GetPostVal求后缀表达式的值*/
double GetPostVal(char poststr[],int m)
{
	numStack S;
	MakeNull(S);
	int i=0;
	double value=0,x,y,z;
	while (i != m)
	{
		if (poststr[i] >= '0'&& poststr[i] <= '9')
		{ 
			z=Getnum(poststr,&i);
			PushNum(z,S);
		}
		else if (poststr[i] == ' ')
			i++;
		else if (poststr[i] == '+')
		{
			x = PopNum(S);
			y = PopNum(S);
			value=y+x;
			PushNum(value,S);
			i++;
		}
		else if (poststr[i] == '-')
		{
			if (i == 0 || poststr[i - 1] == '(')
			{
				i++;
				z = Getnum(poststr,&i);
				PushNum(z,S);
			}
			x = PopNum(S);
			y = PopNum(S);
			value=y-x;
			PushNum(value,S);
			i++;
		}
		else if (poststr[i] == '*')
		{
			x = PopNum(S);
			y = PopNum(S);
			value=y*x;
			PushNum(value,S);
			i++;
		}
		else if (poststr[i] == '/')
		{
			x = PopNum(S);
			y = PopNum(S);
			value=y/x;
			PushNum(value,S);
			i++;
		}
	}
	value = PopNum(S);
	MakeNull(S);
	return value;
}

int main()
{
	int n,i,m;//n为中缀表达式长度，m为后缀表达式长度
	double result;
	char    chr;
	char    inExp[maxlength];        /*中缀表达式*/
	char    postExp[maxlength];   /*后缀表达式*/
	chr='y';
	while (chr =='y'||chr=='Y')
	{
		cout << "请确定是否输入表达式,'y'或'Y'表示确定：";
		cin>>chr;
		if (chr == 'n' || chr == 'N')
			break;
		cin>>inExp;
		m=0;
		i=0;
		//计算中缀表达式长度n
	while (inExp[i] != '\0')
		i++;
	n=i;
    InfixtoPostfix(inExp,postExp,n,m);
	for (i=0;i<m;i++)
	cout<<postExp[i];
	cout<<endl;
	result = GetPostVal(postExp,m );
	cout<<result<<endl;
	}	
	return 0;
}

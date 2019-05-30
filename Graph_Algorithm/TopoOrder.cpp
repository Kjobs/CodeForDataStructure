#include <iostream>
#include <stack>
using namespace std;
#define MAX  30

/*定义边弧节点结构*/
struct Enode
{
    int ivex;//弧所指向的顶点位置
    Enode  *nextEdge;//指向下一条弧的指针
};
/*定义邻接表的顶点结构*/
struct Vnode
{
    char data;//顶点信息
    int indegree;//入度信息
    Enode *firstEdge;//顶点的第一条弧
};
/*定义图结构*/
struct AdjList
{
    int Vnum;//图的顶点数目
    int Enum;//图的边的数目
    Vnode mVexs[MAX];//邻接表的顶点结构体数组
};
void linkLast(Enode *list, Enode *node);
int getPosition(char ch,int Vnum,Vnode mVexs[]);

/*邻接表结构存储图，参数为顶点数组、顶点数和边的数组、边的数目*/
void CreatGraph(char vexs[], int Vnum, char edges[][2], int Enum,Vnode mVexs[])
{
    char c1, c2;
    int i, p1, p2;
    Enode *node;
    for(i=0; i<Vnum; i++)
    {
        //将顶点存入顶点数组，并将其邻接表第一条弧初始化
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = NULL;
        mVexs[i].indegree=0;
    }
    for (i = 0; i < Enum; i++)
    {
        c1 = edges[i][0];
        c2 = edges[i][1];
        p1 = getPosition(c1,Vnum,mVexs);
        p2 = getPosition(c2,Vnum,mVexs);
        mVexs[p2].indegree += 1;
        node = new Enode();
        node->ivex = p2;
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node;
        else
            linkLast(mVexs[p1].firstEdge, node);
    }
}
void linkLast(Enode *list, Enode *node)
{
    //将node节点链接到list后
    Enode *p=list;
    while(p->nextEdge)
        p = p->nextEdge;
    p ->nextEdge = node;
}
int getPosition(char ch,int Vnum,Vnode mVexs[])
{
    //返回字符在顶点数组中的位置
    int i;
    for(i=0; i<Vnum; i++)
        if(mVexs[i].data==ch)
            return i;
    return -1;
}
void PrintAdj(int Vnum,Vnode mVexs[])
{
    int i;
    Enode *p;
    for (i = 0; i < Vnum; i++)
    {
        cout <<"("<<i<<")"<< mVexs[i].data ;
        p = mVexs[i].firstEdge;
		if (p==NULL)
            cout << "Null！";
        while (p != NULL)
        {
            cout << "->"<< mVexs[p->ivex].data ;
            p=p->nextEdge;
        }
        cout << endl;
    }
}

void TopoOrder(int Vnum,Vnode mVexs[])
{
    stack<Vnode>  stack;
    Vnode p;
    Enode *t;
    int v,w;
    int nodecount;
    for (v = 0; v < Vnum; v++)
    {
        //将入度为0的顶点入栈
        if (mVexs[v].indegree == 0)
            stack.push(mVexs[v]);
    }
    nodecount=0;
    while (!stack.empty())
    {
        //栈不空时，依次将栈中顶点所指向下一个顶点的弧删去，得到新的入度为0的顶点，然后压栈
        p = stack.top();
        stack.pop();
        cout << p.data << " ";
        nodecount += 1;
        t = p.firstEdge;
        while (t != NULL)
        {
            mVexs[t->ivex].indegree -= 1;
            w=mVexs[t->ivex].indegree;
            if (w==0)
                stack.push(mVexs[t->ivex]);
            t=t->nextEdge;
        }
    }
    if (nodecount<0)
        cout << "There is cycle on the disgraph!";
}
int main()
{
    char vexs[MAX] ;
    char edges[MAX][2];
    AdjList *g=NULL;
    int i,Vnum,Enum;
    cout << "请输入顶点的数目：";
    cin >> Vnum;
    cout << "请输入边的数目：";
    cin >> Enum;
    cout << "请依次输入顶点: "<<endl;
    for (i = 0; i < Vnum; i++)
        cin >> vexs[i];
    cout << "请依次输入边: "<<endl;
    for (i = 0; i < Enum; i++)
        cin >> edges[i][0]>>edges[i][1];

    Vnode mVexs[MAX];
    CreatGraph(vexs,Vnum,edges,Enum,mVexs);
    cout << "输出邻接表如下："<<endl;
    PrintAdj(Vnum,mVexs);
    cout << "拓扑排序：";
    TopoOrder(Vnum,mVexs);
    return 0;
}

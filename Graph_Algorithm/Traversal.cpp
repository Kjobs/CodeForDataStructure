#include <iostream>
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
    Enode *node1, *node2;
    for(i=0; i<Vnum; i++)
    {
        //将顶点存入顶点数组，并将其邻接表第一条弧初始化
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = NULL;
    }
    for (i = 0; i < Enum; i++)
    {
        c1 = edges[i][0];
        c2 = edges[i][1];
        p1 = getPosition(c1,Vnum,mVexs);
        p2 = getPosition(c2,Vnum,mVexs);
        node1 = new Enode();
        node1->ivex = p2;
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
        node2 = new Enode();
        node2->ivex = p1;
        if(mVexs[p2].firstEdge == NULL)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
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
/*深度优先搜索递归实现*/
void DFS(int i, int *visited, Vnode mVexs[])
{
    Enode *p;
    cout << mVexs[i].data << " ";
    visited[i]=1;
    p = mVexs[i].firstEdge;
    while (p != NULL)
    {
        //递归地访问下一条边的信息
        if (visited[p->ivex]==0)
            DFS(p->ivex,visited,mVexs);
        p=p->nextEdge;
    }
}
void DFS(int Vnum,Vnode mVexs[])
{
    int i;
    int visited[MAX];
    for (i = 0; i < Vnum; i++)
    {
        visited[i]=0;
    }
    for (i = 0; i < Vnum; i++)
    {
        if (visited[i]==0)
            DFS(i,visited,mVexs);//引用递归实现的函数DFS，传入访问指针和标记数组
    }
    cout << endl ;
}
/*深度优先搜索非递归实现*/
void NDFS(int Vnum,Vnode mVexs[])
{
    Enode *p,*temp,*t;
    int i,j;
    int visited[MAX];
    for (i = 0; i < Vnum; i++)
    {
        visited[i]=0;
    }
    for (j = 0; j < Vnum; j++)
    {
        if (visited[j] == 0)
        {
            cout << mVexs[j].data << " ";
            p = mVexs[j].firstEdge;
            visited[j]=1;
            while (p!=NULL)
            {
                //如果第一条边存在，则访问该弧指向的下一个顶点，并判断下一条边的指针是否存在，以此循环
                temp=p;//用temp保存第一个顶点所连的顶点，以便能够依次访问
                if (visited[p->ivex] == 0)
                {
                    cout << mVexs[p->ivex].data << " ";
                    visited[p->ivex]=1;
                    t=mVexs[p->ivex].firstEdge;//建立新的顶点访问
                    while (t != NULL)
                    {
                        //循环以上步骤
                        if (visited[t->ivex] == 0)
                        {
                            cout << mVexs[t->ivex].data << " ";
                            visited[t->ivex]=1;
                            t = mVexs[t->ivex].firstEdge;
                        }
                        t=t->nextEdge;
                    }
                }
                p=temp;
                p=p->nextEdge;
            }
        }
    }
    cout << endl ;
}
/*广度优先搜索实现*/
void BFS(int Vnum,Vnode mVexs[])
{
    Enode *p;
    int front=0;
    int rear=0;
    int queue[MAX];//引入循环队列用以保存节点信息
    int visited[MAX];
    int i,j;
    for (i = 0; i < Vnum; i++)
    {
        visited[i]=0;
    }
    for (i = 0; i < Vnum; i++)
    {
        if (visited[i] == 0)
        {
            visited[i]=1;
            cout << mVexs[i].data << " ";
            queue[rear]=i;
            rear = (rear+1)%MAX;
        }
        while (front != rear)
        {
            j = queue[front];
            front = (front+1)%MAX;
            p = mVexs[j].firstEdge;
            while (p != NULL)
            {
                if (visited[p->ivex] == 0)
                {
                    visited[p->ivex]=1;
                    cout << mVexs[p->ivex].data << " ";
                    queue[rear]=p->ivex;
                    rear = (rear+1)%MAX;
                }
                else
                {
                    p=p->nextEdge;
                }
            }
        }
    }
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
int main()
{
    char vexs[MAX] ;
    char edges[MAX][2] ;
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
    cout << "深度优先搜索(递归): " ;
    DFS(Vnum,mVexs);
    cout << "深度优先搜索(非递归): ";
    NDFS(Vnum,mVexs);
    cout << "广度优先搜索: ";
    BFS(Vnum,mVexs);
    return 0;
}

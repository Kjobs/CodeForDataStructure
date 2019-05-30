#include <iostream>
using namespace std;
#define  MAX 16 

struct Vex                                 
{//图顶点类型
	 int farmer;
	 int sheep;
	 int wolf;
	 int veg;
}; 

struct  GraphNode                              
{//图结点类型
	 int Vexs;                         //顶点个数
	 Vex vertex[MAX];                  //顶点向量
	 int Matrix[MAX][MAX];             //图的邻接矩阵用于存储图的边，矩阵元素个数取决于顶点个数
}; 
typedef GraphNode *Graph;                           //存储路径数组
bool flags[MAX] = {false};
int path[MAX] = {-1};


int Search(Graph &G,int f,int s,int w,int v)   //查找顶点（R，L，Y，C）在顶点向量中的位置函数
{  
	 int i;
	 for(i = 0 ; i < G->Vexs ; i++)
	 {
	  if(G->vertex[i].farmer == f && G->vertex[i].sheep == s && G->vertex[i].wolf == w && G->vertex[i].veg == v)
		 return i;                          //存在则返回当前位置
	 }
	 return -1;                             //没有找到此顶点
}
bool  Safe(int f,int w,int s,int v)        
{//判断路径是否可行，农夫与羊不在一起且狼与羊或羊与白菜在一起时不安全
	 if( f != s &&(w == s || s == v) )       
		 return false; //不安全返回错误
	 else                                    
		 return true; //安全时返回正确                          
}
int PassRiver(Graph &G,int i,int j)        
{
	 int k = 0;
	 //以下三个条件不同时满足两个且农夫状态改变时可交换,即农夫每次只能带一件东西过河
	 if(G->vertex[i].wolf != G->vertex[j].wolf)
		 k++;
	 if(G->vertex[i].sheep != G->vertex[j].sheep)
		 k++;
	 if(G->vertex[i].veg != G->vertex[j].veg)
		 k++;
	 if(G->vertex[i].farmer != G->vertex[j].farmer && k <= 1)
		return 1;//可交换
	 else 
		return 0;//不可交换
}
void CreatGraph(Graph &G)                      
{ //生成图的邻接矩阵及顶点向量函数
	 int i = 0,j,f,w,s,v;
	 for (f = 0; f <= 1; f++)
	 {
		 for (w = 0; w <= 1; w++)
		 {
			 for (s = 0; s <= 1; s++)
			 {
				 for (v = 0; v <= 1; v++)
				 {
					 if (Safe(f, w, s, v))
					 {
						 G->vertex[i].farmer = f;
						 G->vertex[i].wolf = w;
						 G->vertex[i].sheep = s;
						 G->vertex[i].veg = v ;						 
						 i++;
					 }
				 }				
			  }
			}
		 }
	 G->Vexs=i;
	 for (i = 0; i < G->Vexs; i++)
   		 for (j = 0; j < G->Vexs; j++)
		 {
			 if (PassRiver(G, i, j))
				 G->Matrix[i][j] = G->Matrix[j][i] = 1;
			 else
				 G->Matrix[i][j] = G->Matrix[j][i] = 0;
		 }
}
void PrintPath(Graph &G,int start,int end)               
{//输出路径 
	 int i=start;
	 cout << "农夫" << "  狼" << "  羊" << "  白菜" << "('0'表示左岸,'1'表示右岸):" << endl;
	 while (i != end)
	 {
		 cout << G->vertex[i].farmer << "    " << G->vertex[i].wolf
          << "   " << G->vertex[i].sheep << "    " << G->vertex[i].veg ;     
        cout << endl;
        i = path[i];
	 }
	 cout <<  G->vertex[i].farmer << "    " <<G->vertex[i].wolf
     << "   " <<G->vertex[i].sheep << "    " <<G->vertex[i].veg ;
     cout << endl; 
}
void Traversal(Graph &G,int u,int v)         
{ //深度优先搜索(递归)实现领接矩阵中的路径
	 int j,k = 0;
	 flags[u] = 1;
	 for(j = 0;j < G->Vexs;j++)
	       if(G->Matrix[u][j] && !flags[j] && !flags[v])
	      {
		       path[u]=j;                                     
		       Traversal(G,j,v);  
	      }
}
int main()                                
{
	int i,j;
	int flags[MAX];
	int path[MAX];
	Graph G;
	G=new GraphNode;         
	CreatGraph(G);             
	i = Search(G,0,0,0,0);       //查找(0,0,0,0)的位置
	j = Search(G,1,1,1,1);       //查找(1,1,1,1)的位置
	Traversal(G,i,j);             //查找i到j的路径
	if(flags[j])
		PrintPath(G,i,j);       
	return 0;
} 

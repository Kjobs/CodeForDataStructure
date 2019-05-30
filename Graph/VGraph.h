#ifndef VIRTUALGRAPH_H
#define VIRTUALGRAPH_H

template<class T>
class Vgraph
{
public:
	virtual void CreatGraph() = 0;
	virtual void PrintGraph() = 0;
	virtual void DFS() = 0;
	virtual void BFS() = 0;
};

#endif

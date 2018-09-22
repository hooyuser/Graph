#include<iostream>
#include"Graph.h"
#include"Graphmatrix.h"

using namespace std;


template<typename Tv, typename Te>
void DisplayMatrix(GraphMatrix<Tv, Te>* graph)
{
	cout << "\t";
	for (int i = 0; i < graph->Graph<Tv, Te>::n; i++)
	{
		cout << graph->vertex(i) << "\t";
	}
	cout << endl;
	for (int i = 0; i < graph->Graph<Tv, Te>::n; i++)
	{
		cout << graph->vertex(i) << "\t";
		for (int j = 0; j < graph->Graph<Tv, Te>::n; j++)
		{
			if (graph->exists(i, j))
			{
				cout << graph->weight(i, j);
			}
			else
			{
				cout << 0;
			}
			cout << "\t";
		}
		cout << endl;
	}
}

int main()
{
	GraphMatrix<char, char> Network;  //构造一个带权有向图
	Network.insert('S');
	for (int i = 0; i < 7; i++)
	{
		Network.insert('A' + i);
	}
	Network.insert(0, 9, 0, 1);
	Network.insert(0, 14, 0, 3);
	Network.insert(0, 15, 0, 6);
	Network.insert(0, 25, 1, 2);
	Network.insert(0, 2, 2, 4);
	Network.insert(0, 30, 3, 4);
	Network.insert(0, 18, 3, 2);
	Network.insert(0, 11, 4, 5);
	Network.insert(0, 16, 4, 7);
	Network.insert(0, 6, 5, 2);
	Network.insert(0, 6, 5, 7);
	Network.insert(0, 20, 6, 4);
	Network.insert(0, 40, 6, 7);

	DisplayMatrix(&Network);  //打印邻接矩阵
	cout << endl;

	/*优先级搜索算法的特例：最短路径树*/
	Network.dijkstra(0); //priority记录S到各点的最短路径长度，parent记录最短路径树

	cout << "min_len";
	for (int i = 0; i < Network.Graph<char, char>::n; i++)
	{
		cout << "\t" << Network.priority(i);  //输出S到各点的最短路径长度
	}
	cout << endl;

	/*优先级搜索算法的特例：最小支撑树*/
	Network.prim(0);  //生成最小支撑树
	int s = 0;
	for (int i = 0; i < Network.Graph<char, char>::n; i++)
	{
		s += Network.priority(i);  //输出最小边权和
	}
	cout << "最小边权和 = " << s << endl;

	/*广度优先搜索*/
	cout << "广度优先搜索序列：";
	Network.bfs(0);
	cout << endl;

	/*深度优先搜索*/
	cout << "深度优先搜索序列：";
	Network.dfs(0);
	cout << endl;

	/*有向无环图拓扑排序*/
	Network.remove(2, 4);
	Network.remove(5, 2);
	Stack<char>* TopoStack = Network.tSort(0);
	cout << "拓扑排序结果：";
	TopoStack->inverseTraverse([](char & ch) { cout << ch << " "; });
	delete TopoStack;

	return 0;
}
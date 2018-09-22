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
	GraphMatrix<char, char> Network;  //����һ����Ȩ����ͼ
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

	DisplayMatrix(&Network);  //��ӡ�ڽӾ���
	cout << endl;

	/*���ȼ������㷨�����������·����*/
	Network.dijkstra(0); //priority��¼S����������·�����ȣ�parent��¼���·����

	cout << "min_len";
	for (int i = 0; i < Network.Graph<char, char>::n; i++)
	{
		cout << "\t" << Network.priority(i);  //���S����������·������
	}
	cout << endl;

	/*���ȼ������㷨����������С֧����*/
	Network.prim(0);  //������С֧����
	int s = 0;
	for (int i = 0; i < Network.Graph<char, char>::n; i++)
	{
		s += Network.priority(i);  //�����С��Ȩ��
	}
	cout << "��С��Ȩ�� = " << s << endl;

	/*�����������*/
	cout << "��������������У�";
	Network.bfs(0);
	cout << endl;

	/*�����������*/
	cout << "��������������У�";
	Network.dfs(0);
	cout << endl;

	/*�����޻�ͼ��������*/
	Network.remove(2, 4);
	Network.remove(5, 2);
	Stack<char>* TopoStack = Network.tSort(0);
	cout << "������������";
	TopoStack->inverseTraverse([](char & ch) { cout << ch << " "; });
	delete TopoStack;

	return 0;
}
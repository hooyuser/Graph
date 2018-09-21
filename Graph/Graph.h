#pragma once
#include "Stack.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //���ڱ�����������������

template <typename Tv, typename Te> //�������͡�������
class Graph  //ͼGraph������ģ��
{
private:
	void reset()  //���ж��㡢�ߵĸ�����Ϣ��λ
	{
		for (int i = 0; i < n; i++)  //���ж����
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1; //״̬��ʱ���ǩ
			parent(i) = -1;
			priority(i) = INT_MAX; //���ڱ������еģ����ڵ㣬���ȼ���
			for (int j = 0; j < n; j++) //���бߵ�
			{
				if (exists(i, j))
				{
					type(i, j) = UNDETERMINED; //����
				}
			}
		}
	}
	void BFS(int, int&); //����ͨ�򣩹�����������㷨
	void DFS(int, int&); //����ͨ��������������㷨
	void BCC(int, int&, Stack<int>&); //����ͨ�򣩻���DFS��˫��ͨ�����ֽ��㷨
	bool TSort(int, int&, Stack<Tv>*); //����ͨ�򣩻���DFS�����������㷨
	template <typename PU> void PFS(int, PU); //����ͨ�����ȼ��������
public:
	// ����
	int n; //��������
	virtual int insert(Tv const&) = 0; //���붥�㣬���ر��
	virtual Tv remove(int) = 0; //ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex(int) = 0; //����v�����ݣ��ö����ȷ���ڣ�
	virtual int inDegree(int) = 0; //����v����ȣ��ö����ȷ���ڣ�
	virtual int outDegree(int) = 0; //����v�ĳ��ȣ��ö����ȷ���ڣ�
	virtual int firstNbr(int) = 0; //����v���׸��ڽӶ���
	virtual int nextNbr(int, int) = 0; //����v�ģ�����ڶ���j�ģ���һ�ڽӶ���
	virtual VStatus& status(int) = 0; //����v��״̬
	virtual int& dTime(int) = 0; //����v��ʱ���ǩdTime
	virtual int& fTime(int) = 0; //����v��ʱ���ǩfTime
	virtual int& parent(int) = 0; //����v�ڱ������еĸ���
	virtual int& priority(int) = 0; //����v�ڱ������е����ȼ���

 // �ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	int e; //������
	virtual bool exists(int, int) = 0; //��(v, u)�Ƿ����
	virtual void insert(Te const&, int, int, int) = 0; //�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0; //ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType & type(int, int) = 0; //��(v, u)������
	virtual Te& edge(int, int) = 0; //��(v, u)�����ݣ��ñߵ�ȷ���ڣ�
	virtual int& weight(int, int) = 0; //��(v, u)��Ȩ��

 // �㷨
	void bfs(int); //������������㷨
	void dfs(int); //������������㷨
	void bcc(int); //����DFS��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int); //����DFS�����������㷨
	void prim(int); //��С֧����Prim�㷨
	void dijkstra(int); //���·��Dijkstra�㷨
	template <typename PU> void pfs(int, PU); //���ȼ��������
};




/*Graphģ����ʵ��*/

template <typename Tv, typename Te> //�����������BFS�㷨��������ͨ��
void Graph<Tv, Te>::BFS(int v, int& clock) //assert: 0 <= v < n 
{
	Queue<int> Q; //���븨������
	status(v) = DISCOVERED;
	Q.enqueue(v); //��ʼ�����
	while (!Q.empty())  //��Q���֮ǰ������
	{
		int v = Q.dequeue();  //ȡ�����׶���v
		dTime(v) = ++clock;
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //ö��v�������ھ�u
		{
			if (UNDISCOVERED == status(u)) //��u��δ�����֣���
			{
				status(u) = DISCOVERED;  //���ָö���
				Q.enqueue(u);
				type(v, u) = TREE;
				parent(u) = v; //����������չ֧����
			}
			else //��u�ѱ����֣����������ѷ�����ϣ���
			{
				type(v, u) = CROSS; //��(v, u)�����ڿ��
			}
		}
		status(v) = VISITED; //���ˣ���ǰ����������
	}
}


template <typename Tv, typename Te> //�����������BFS�㷨��ȫͼ��
void Graph<Tv, Te>::bfs(int s)  //assert: 0 <= s < n
{
	reset();
	int clock = 0;
	int v = s; //��ʼ��
	do //��һ������ж���
	{
		if (UNDISCOVERED == status(v)) //һ��������δ���ֵĶ���
		{
			BFS(v, clock);//���Ӹö����������һ��BFS
		}
	} while (s != (v = (++v % n))); //����ż�飬�ʲ�©����
}


template <typename Tv, typename Te> //�����������DFS�㷨��������ͨ��
void Graph<Tv, Te>::DFS(int v, int& clock)  //assert: 0 <= v < n
{
	dTime(v) = ++clock;
	status(v) = DISCOVERED; //���ֵ�ǰ����v
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //ö��v�������ھ�u
	{
		switch (status(u))  //������״̬�ֱ���
		{
		case UNDISCOVERED: //u��δ���֣���ζ��֧�������ڴ���չ
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED: //u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
			type(v, u) = BACKWARD;
			break;
		default: //u�ѷ�����ϣ�VISITED������ͼ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock; //���ˣ���ǰ����v����������
}

template <typename Tv, typename Te> //�����������DFS�㷨��ȫͼ��
void Graph<Tv, Te>::dfs(int s)  //assert: 0 <= s < n
{
	reset(); int clock = 0; int v = s; //��ʼ��
	do //��һ������ж���
	{
		if (UNDISCOVERED == status(v)) //һ��������δ���ֵĶ���
			DFS(v, clock); //���Ӹö����������һ��DFS
	} while (s != (v = (++v % n))); //����ż�飬�ʲ�©����
}


template <typename Tv, typename Te>
template <typename PU> //���ȼ�������ȫͼ��
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)  //assert: 0 <= s < n
{
	reset();
	int v = s; //��ʼ��
	do //��һ������ж���
	{
		if (UNDISCOVERED == status(v)) //һ��������δ���ֵĶ���
			PFS(v, prioUpdater); //���Ӹö����������һ��PFS
	} while (s != (v = (++v % n))); //����ż�飬�ʲ�©����
}

template <typename Tv, typename Te>
template <typename PU> //�������͡������͡����ȼ�������
void Graph<Tv, Te>::PFS(int s, PU prioUpdater)  //���ȼ�������������ͨ��
{
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1; //��ʼ�������s����PFS����
	while (1)  //����һ����ͱ߼���PFS����
	{
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w)) //ö��s�������ھ�w
			prioUpdater(this, s, w); //���¶���w�����ȼ����丸����
		for (int shortest = INT_MAX, w = 0; w < n; w++)
			if (UNDISCOVERED == status(w)) //����δ����������Ķ�����
				if (shortest > priority(w)) //ѡ����һ��
				{
					shortest = priority(w);
					s = w;
				} //���ȼ���ߵĶ���s
		if (VISITED == status(s))
			break; //ֱ�����ж�����Ѽ���
		status(s) = VISITED;
		type(parent(s), s) = TREE; //��s�����丸�����߼��������
	}
} //ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

template <typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s) //����DFS��BCC�ֽ��㷨
{
	reset(); int clock = 0; int v = s; Stack<int> S; //ջS���Լ�¼�ѷ��ʵĶ���
	do
		if (UNDISCOVERED == status(v)) //һ������δ���ֵĶ��㣨����ͨ������
		{
			BCC(v, clock, S); //���Ӹö����������һ��BCC
			S.pop(); //�������غ󣬵���ջ�����һ�����㡪����ǰ��ͨ������
		}
	while (s != (v = (++v % n)));
}

#define hca(x) (fTime(x)) //���ô˴����õ�fTime[]�䵱hca[]
template <typename Tv, typename Te> //�������͡�������
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S) //assert: 0 <= v < n 
{
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v); //v�����ֲ���ջ
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //ö��v�������ھ�u
		switch (status(u))  //����u��״̬�ֱ���
		{
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			BCC(u, clock, S); //�Ӷ���u������
			if (hca(u) < dTime(v)) //�������غ�������u��ͨ������ߣ���ָ��v��������
				hca(v) = min(hca(v), hca(u)); //��v������
			else
			{ //������vΪ�ؽڵ㣨u���¼���һ��BCC�������ж����ʱ��������ջS�Ķ�����
				printf("BCC rooted at %c:", vertex(v));
				Stack<int> temp;
				do
				{
					temp.push(S.pop());
					print(vertex(temp.top()));
				} while (v != temp.top());
				while (!temp.empty())
					S.push(temp.pop());
				while (v != S.pop()); //���ε�����ǰBCC�еĽڵ㣬��ɸ���ʵ������ת���������ṹ
				S.push(v); //���һ�����㣨�ؽڵ㣩������ջ������̯����һ��
				printf("\n");
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD; //���(v, u)�������ա�ԽСԽ�ߡ���׼��
			if (u != parent(v))
				hca(v) = min(hca(v), dTime(u)); //����hca[v]
			break;
		default: //VISITED (digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	status(v) = VISITED; //��v�ķ��ʽ���
}
#undef hca

template <typename Tv, typename Te> //����DFS�����������㷨
Stack<Tv>* Graph<Tv, Te>::tSort(int s) //assert: 0 <= s < n
{
	reset();
	int clock = 0;
	int v = s;
	Stack<Tv>* S = new Stack<Tv>; //��ջ��¼���򶥵�
	do {
		if (UNDISCOVERED == status(v))
			if (!TSort(v, clock, S))  //clock���Ǳ���
			{
				/*DSA*/print(S);
				while (!S->empty()) //��һ��ͨ���༴��ͼ����DAG
					S->pop();
				break; //�򲻱ؼ������㣬��ֱ�ӷ���
			}
	} while (s != (v = (++v % n)));
	return S; //������ΪDAG����S�ڸ������Զ�������򣻷��򣨲������������򣩣�S��
}

template <typename Tv, typename Te> //����DFS�����������㷨�����ˣ�
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S)
{ //assert: 0 <= v < n
	dTime(v) = ++clock;
	status(v) = DISCOVERED; //���ֶ���v
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) //ö��v�������ھ�u
		switch (status(u))
		{ //����u��״̬�ֱ���
		case UNDISCOVERED:
			parent(u) = v;
			type(v, u) = TREE;
			if (!TSort(u, clock, S)) //�Ӷ���u��������������
				return false; //��u��������������������ȫͼ�����ˣ����ʷ��ز�����
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD; //һ�����ֺ���ߣ���DAG������
			return false; //�������룬�ʷ��ز�����
		default: //VISITED (digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	status(v) = VISITED;
	S->push(vertex(v)); //���㱻���ΪVISITEDʱ���漴��ջ
	return true; //v������������������
}

template <typename Tv, typename Te> //Prim�㷨��������ͨͼ�����߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
void Graph<Tv, Te>::prim(int s) //assert: 0 <= s < n 
{
	reset();
	priority(s) = 0;
	for (int i = 0; i < n; i++)  //��������n�������n-1����
	{
		status(s) = VISITED;
		if (-1 != parent(s))
		{
			type(parent(s), s) = TREE; //���뵱ǰ��s
		}
		for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //ö��s�������ھ�j
		{
			if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) //���ڽӶ���j���ɳ�
			{
				priority(j) = weight(s, j);
				parent(j) = s;
			} //��Dijkstra�㷨Ψһ�Ĳ�֮ͬ��
		}
		for (int shortest = INT_MAX, j = 0; j < n; j++) //ѡ����һ���̿��
		{
			if ((status(j) == UNDISCOVERED) && (shortest > priority(j)))
			{
				shortest = priority(j); s = j;
			}
		}
	}
}

template <typename Tv, typename Te> //���·��Dijkstra�㷨��������һ�������ͼ
void Graph<Tv, Te>::dijkstra(int s)  //assert: 0 <= s < n
{
	reset();
	priority(s) = 0;
	for (int i = 0; i < n; i++)  //��������n�������n-1����
	{
		status(s) = VISITED;
		if (-1 != parent(s))
			type(parent(s), s) = TREE; //���뵱ǰ��s
		for (int j = firstNbr(s); -1 < j; j = nextNbr(s, j)) //ö��s�������ھ�j
		{
			if ((status(j) == UNDISCOVERED) && (priority(j) > priority(s) + weight(s, j))) //���ڽӶ���j���ɳ�
			{
				priority(j) = priority(s) + weight(s, j);
				parent(j) = s;
			} //��Prim�㷨Ψһ�Ĳ�֮ͬ��
		}
		for (int shortest = INT_MAX, j = 0; j < n; j++) //ѡ����һ�������
		{
			if ((status(j) == UNDISCOVERED) && (shortest > priority(j)))
			{
				shortest = priority(j);
				s = j;
			}
		}
	}
} //����������ͨͼ������ÿһ���߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
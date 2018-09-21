#ifndef QUEUE_H_
#define QUEUE_H_
#include "List.h" //��ListΪ����

template <typename T> class Queue : public List<T> //����ģ���ࣨ�̳�Listԭ�нӿڣ�
{ 
public: //size()��empty()�Լ��������Žӿھ���ֱ������
	void enqueue(T const& e) 
	{ 
		this->insertAsLast(e);  //��ӣ�β������
	}
	T dequeue() 
	{ 
		return remove(this->first()); //���ӣ��ײ�ɾ��
	}
	T& front() 
	{ 
		return this->first()->data;  //����
	}
};

#endif
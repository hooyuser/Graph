#ifndef STACK_H_
#define STACK_H_

#include "vector.h"

template <typename T>
class Stack :public Vector<T>
{
public:
	void push(T const& e)
	{
		this->insert(this->size(), e);
	}

	T pop()
	{
		return this->remove(this->size() - 1);
	}

	T& top()
	{
		return (*this)[this->size() - 1];
	}

	void inverseTraverse(void(*visit) (T&)) //��������ָ�����
	{
		for (int i = this->_size - 1; i >= 0; i--)
			visit(this->_elem[i]);
	} //��������

	template <typename VST> //Ԫ�����͡�������
	void inverseTraverse(VST& visit) //���������������
	{
		for (int i = this->_size - 1; i >= 0; i--)
			visit(this->_elem[i]);
	} //��������
};



#endif // STACK_H_

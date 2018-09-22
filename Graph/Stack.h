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

	void inverseTraverse(void(*visit) (T&)) //借助函数指针机制
	{
		for (int i = this->_size - 1; i >= 0; i--)
			visit(this->_elem[i]);
	} //遍历向量

	template <typename VST> //元素类型、操作器
	void inverseTraverse(VST& visit) //借助函数对象机制
	{
		for (int i = this->_size - 1; i >= 0; i--)
			visit(this->_elem[i]);
	} //遍历向量
};



#endif // STACK_H_

#include "MinStack.h"

template<typename T>
MinStack<T>::MinStack()
{
	// 因为 T 是基础的数字类型，初始化为0 
	MinElement = 0;

	DataList = std::list<T>();
}

template<typename T>
T MinStack<T>::GetMin()
{
	return MinElement;
}

template<typename T>
void MinStack<T>::Push(T element)
{
	DataList.push_back(element);

	SetMinElement();
}

template<typename T>
T MinStack<T>::Top()
{
	return DataList.back();
}

template<typename T>
T MinStack<T>::Pop()
{
	T topElement = DataList.back();
	DataList.pop_back();

	SetMinElement();

	return topElement;
}

template<typename T>
void MinStack<T>::SetMinElement()
{
	typename std::list<T>::iterator itr = DataList.begin();
	MinElement = *(itr++);

	for (; itr != DataList.end(); ++itr)
	{
		if (*itr < MinElement)
			MinElement = *itr;
	}
}
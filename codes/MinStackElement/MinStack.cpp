#include "MinStack.h"

template<typename T>
MinStack<T>::MinStack()
{
}

template<typename T>
MinStack<T>::~MinStack()
{
	Node<T>* pNode = nullptr;
	while (pTail)
	{
		pNode = pTail;
		pTail = pTail->front;

		delete pNode;
	}

	pNode = nullptr;
}

template<typename T>
T MinStack<T>::GetMin()
{
	return pMin->data;
}

template<typename T>
void MinStack<T>::Push(T element)
{
	if (!pTail)
	{
		pTail = new Node<T>(element);
	}
	else
	{
		Node<T>* pNode = new Node<T>(element);
		pNode->front = pTail;
		pTail = pNode;
	}

	if (!pMin || element < pMin->data) pMin = pTail;
}

template<typename T>
T MinStack<T>::Top()
{
	return pTail->data;
}

template<typename T>
void MinStack<T>::Pop()
{
	// 删除链表末尾元素
	Node<T>* pNode = pTail;
	pTail = pTail->front;

	// 弹出的栈顶元素若刚好就是最小节点，重新遍历出最小节点，标记此状态
	bool shouldFindMin = (pNode == pMin);

	delete pNode;
	pNode = nullptr;

	if (shouldFindMin)
	{
		pMin = pTail;
		pNode = pTail->front;
		while (pNode)
		{
			if (pNode->data < pMin->data)
			{
				pMin = pNode;
			}

			pNode = pNode->front;
		}
	}
}
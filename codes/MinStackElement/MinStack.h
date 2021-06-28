#ifndef _MIN_STACK_CLASS_DEFINE_
#define _MIN_STACK_CLASS_DEFINE_

#pragma once

/** 反向链表结构 */
template<typename T>
struct Node
{
	T  data;
	Node<T>* front;

	Node<T>(T _data)
	{
		data = _data;
		front = nullptr;
	}
};

/**
 * T 为基础的数字类数据类型，如int,float,double等
 */
template<typename T>
class MinStack
{
public:
	MinStack();
	~MinStack();

	/**
	 * @brief 获取自定义栈的最小元素
	 * @return 返回成员变量 MinElement
	 */
	T GetMin();

	/**
	 * @brief 元素入栈后按照升序排列
	 * @param element 入栈元素
	 */
	void Push(T element);

	/**
	 * @brief 返回栈顶元素，并不出栈
	 * @return 栈顶元素
	 */
	T Top();

	/**
	 * @brief 弹出栈顶元素，每次弹出后，需要重新确定最小节点
	 */
	void Pop();

private:
	/** 栈内最小元素 */
	Node<T>* pMin;
	/** 用以存储数据的链表尾指针 */
	Node<T>* pTail;
};

#endif



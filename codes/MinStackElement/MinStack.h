#ifndef _MIN_STACK_CLASS_DEFINE_
#define _MIN_STACK_CLASS_DEFINE_

#pragma once

#include <list>

/**
 * T 为基础的数字类数据类型，如int,float,double等
 */
template<typename T>
class MinStack
{
public:
	MinStack();
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
	 * @brief 弹出栈顶元素
	 * @return 栈顶元素
	 */
	T Pop();

private:
	/** 栈内最小元素 */
	T MinElement;
	/** 用以存储数据的list */
	std::list<T> DataList;

	/**
	 * @brief 设置栈的最小元素，在每次出入栈的时候需要调用
	 */
	void SetMinElement();
};

#endif


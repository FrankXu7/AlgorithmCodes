/**************************************************************************************************
 * 【题目描述】
 * 设计一个栈，要有 push、pop、top、getMin 方法，其中 getMin 获取最小元素需要在常数时间内完成。
 *
 * 【输入】
 * MinStack();
 * push(-2);
 * push(0);
 * push(-3);
 * getMin();
 * pop();
 * top();
 * getMin();
 *
 * 【输出】
 * 构造对象；
 * 入栈 -2；
 * 入栈 0；
 * 入栈 -3；
 * 返回最小元素 -3；
 * 弹出栈顶元素；
 * 返回栈顶元素 0；
 * 返回最小元素 -2；
 *
 * 【解题思路】
 *
 *
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include "MinStack.h"

int main()
{
	MinStack<int>* ob = new MinStack<int>();

	ob->Push(-2);
	ob->Push(0);
	ob->Push(-3);
	int minElement = ob->GetMin();
	ob->Pop();
	int topElement = ob->Top();
	minElement = ob->GetMin();

	delete ob;
	ob = nullptr;

	return 0;
}
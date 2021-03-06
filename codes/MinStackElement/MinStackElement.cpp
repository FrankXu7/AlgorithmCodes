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
 * 自实现一个简单的栈类，包含题中所需要的接口，同时用一个额外的节点，保存最小节点，栈的数据采用链表存储，
 * 链表节点为自定义的数据结构：MinStack.h 和 MinStack.cpp；当执行入栈时，需要比较入栈元素和当前最小节点
 * 数据的大小，确定最小值，这个处理在常数的时间复杂度内完成。而出栈时，如果出栈的节点，刚好就是最小节点，
 * 则需要对链表剩余元素进行一次遍历，找出最小节点。因为一直保存有最小节点指针，所以获取栈最小值时，可在常
 * 数时间内完成。
 * 
 * 
 * 【解题分析】
 * 时间复杂度：O(N) 最差情况，即出栈元素刚好为最小节点，需要重新遍历找到最小节点
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-28
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include "MinStack.cpp"

int main()
{
	MinStack<int>* ob = new MinStack<int>;

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
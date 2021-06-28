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
 * 考虑采用一个辅助栈来记录最小元素，dataStack保存数据，minStack在每次入栈dataStack时，比较出最小元素入栈minStack；
 * 大致过程：
 * （1）数据N入栈dataStack，比较N与minStack栈顶元素大小，若N更小，则将N也入栈minStack，若N更大，则将
 *		minStack的栈顶元素再次入栈minStack，这样就保证了每次dataStack入栈一个元素时，对应在minStack入栈的
 *		一定是当前dataStack所有数据中的最小值。
 * 特别注意：首个元素默认为最小值。
 * 
 * 【解题分析】
 * 时间复杂度：O(n)
 * 空间复杂度：O(n) 用了一个辅助栈minStack来存储最小值数据
 *
 * @author FrankX
 * @date 2021-06-28
 **************************************************************************************************/
#include <iostream>
#include <stack>
using namespace std;

void Push(int element, stack<int>& dataStack, stack<int>& minStack);
void Pop(stack<int>& dataStack, stack<int>& minStack);

void MinStackElement_HelperStack()
{
	// 存储数据
	stack<int> dataStack;
	// 存储最小值数据
	stack<int> minStack;

	Push(-2, dataStack, minStack); // 入栈 -2
	Push(0, dataStack, minStack); // 入栈 0
	Push(-3, dataStack, minStack); // 入栈 -3
	int minElement = minStack.top(); // 返回最小元素 -3
	Pop(dataStack, minStack); // 弹出栈顶元素
	int topElement = dataStack.top(); // 返回栈顶元素
	minElement = minStack.top(); // 返回最小元素 -2
}

void Push(int element, stack<int>& dataStack, stack<int>& minStack)
{
	dataStack.push(element);
	
	// 首个元素默认为最小值 
	if (minStack.empty())
	{
		minStack.push(element);
		return;
	}

	if (element < minStack.top())
		minStack.push(element);
	else 
		minStack.push(minStack.top());
}

void Pop(stack<int>& dataStack, stack<int>& minStack)
{
	dataStack.pop();
	minStack.pop();
}

int main()
{
	MinStackElement_HelperStack();
	return 0;
}
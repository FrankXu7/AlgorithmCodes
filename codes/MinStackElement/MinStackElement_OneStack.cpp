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
 * 利用辅助栈来保存最小元素，会使得空间复杂度达到O(N)，可以用记录与最小值差值的方法，来保存数据。
 * 即元素不直接入栈，而是与当前的最小值做差后再入栈，显然，出栈或获取栈顶元素时，需要还原。
 * 大致过程：
 * （1）入栈数据 element：实际的入栈元素 pushNum = element - minElement，如果 element >= minElement，
 *		显然实际入栈元素 pushNum 是一个大于零的数，反之，入栈数据 element 比当前记录的最小值 minElement
 *		更小，则更新最小值，并将这个小于零的 pushNum 入栈，栈内元素小于零，也标识入栈时发生过最小值更新。
 * （2）出栈数据：栈内元素并不是实际的数据，按照步骤（1）中的操作，栈内元素 pushNum = element - minElement，
 *		所以出栈数据实际为 element = push + minElement，这里需要特别注意，在出栈前，需要判断栈顶元素是否小于零，
 *		按步骤（1）中所述，栈内元素小于零标识发生过最小值更新，所以出栈的元素小于零时，最小元素需更新为
 *		minElement = minElement - pushNum，此等式由步骤（1）中 pushNum = element - minElement 推导而来；
 *		由 pushNum = element - minElement 可得：minElement = element - pushNum，而出栈元素小于零时，当前的最小值
 *		其实就是之前的入栈元素，且该元素入栈时代替了之前的最小值，此时的 minElement 等价于等式中的 element；
 * 因为一直记录着最小元素，所以符合题意，在常数时间内获取最小值。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-28
 **************************************************************************************************/
#include <iostream>
#include <stack>
using namespace std;

void Push(int element, stack<int> &dataStack, int &minElement);
void Pop(stack<int> &dataStack, int &minElement);
int Top(stack<int> &dataStack, int &minElement);

void MinStackElement_OneStack()
{
	stack<int> dataStack;
	int minElement = 0;

	Push(-2, dataStack, minElement);			 // 入栈 -2
	Push(0, dataStack, minElement);				 // 入栈 0
	Push(-3, dataStack, minElement);			 // 入栈 -3
	minElement;									 // 当前最小元素
	Pop(dataStack, minElement);					 // 弹出栈顶元素
	int topElement = Top(dataStack, minElement); // 返回栈顶元素
	minElement;									 // 当前最小元素
}

void Push(int element, stack<int> &dataStack, int &minElement)
{
	if (dataStack.empty())
	{
		// 首个元素即默认为最小值
		minElement = element;
		dataStack.push(0);
		return;
	}

	// 不直接入栈元素，入栈元素与当前记录最小值差值
	int pushNum = element - minElement;
	// 当前入栈元素比记录的最小值更小，更新最小值
	if (pushNum < 0)
	{
		minElement = element;
	}

	dataStack.push(pushNum);
}

void Pop(stack<int> &dataStack, int &minElement)
{
	int pushNum = dataStack.top();
	// 栈顶元素小于零，标识之前入栈时存在最小值更新，此最小值即为当时的入栈元素
	if (pushNum < 0)
	{
		minElement = minElement - pushNum;
	}

	// 此时的数据出栈元素为 pushNum + minElement
	dataStack.pop();
}

int Top(stack<int> &dataStack, int &minElement)
{
	int pushNum = dataStack.top();
	// 栈顶元素大于零，标识之前入栈的元素大于入栈时的最小值，否则存在最小值更新，当前最小值即为当时的入栈元素
	if (pushNum > 0)
		return (pushNum + minElement);
	else
		return minElement;
}

int main()
{
	MinStackElement_OneStack();

	return 0;
}
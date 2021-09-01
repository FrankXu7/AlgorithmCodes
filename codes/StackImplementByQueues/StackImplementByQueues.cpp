/**************************************************************************************************
 * 【题目描述】
 * 利用队列实现栈，需要实现以下接口：
 * void Push(int data); // 往栈内推入一个元素
 * int Pop(); // 移除并返回栈顶元素
 * int Top(); // 返回栈顶元素
 * bool Empty(); // 判断是否为空栈
 *
 * 【输入】
 * ["MyStack", "push", "push", "top", "pop", "empty"]
 * [ [],        [1],    [2],    [],    [],    []]
 * 【输出】
 * [ null,      null,   null,   2,     2,     false]
 * 
 * 【解题思路】
 * 封装双端队列容器deque，封装接口，使其使用上和栈的使用类似。
 * 
 * 【解题分析】
 * 时间复杂度：O(1) 对双端队列来说，队列首尾的操作都是常数时间复杂度
 * 空间复杂度：O(N) 
 *
 * @author FrankX
 * @date 2021-09-01
 **************************************************************************************************/
#include <iostream>
#include <deque>
using namespace std;

class MyStack 
{
public:
	MyStack() { }
	~MyStack() { deque<int>().swap(datas); }

	inline void Push(int data) { datas.emplace_back(data); }

	inline int Pop()
	{
		int tempData = datas.back();
		datas.pop_back();

		return tempData;
	}

	inline int Top() { return datas.back(); }

	inline bool Empty() { return datas.empty(); }

private:
	deque<int> datas;
};

int main(int argc, char* argv[])
{
	MyStack* ob = new MyStack();

	ob->Push(1);
	ob->Push(2);
	int topData = ob->Top();
	int popTop = ob->Pop();
	bool bEmpty = ob->Empty();

	delete ob;
	ob = nullptr;
	
	cout << endl << endl;
	return 0;
}
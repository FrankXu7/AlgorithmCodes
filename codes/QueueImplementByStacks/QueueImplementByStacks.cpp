/**************************************************************************************************
 * 【题目描述】
 * 利用栈实现队列，需要实现以下接口：
 * void Push(int data); // 入队一个元素
 * int Pop(); // 出队一个元素
 * int Peek(); // 返回队首元素
 * bool Empty(); // 判断是否为空队列
 *
 * 【输入】
 * ["MyQueue", "push", "push", "peek", "pop", "empty"]
 * [ [],        [1],    [2],    [],    [],    []]
 * 【输出】
 * [ null,      null,   null,   2,     2,     false]
 *
 * 【解题思路】
 * 封装容器配接器stack，使其使用上和队列使用类似。
 * 因为stack结构的特殊性，可知：
 * 如果将栈顶作为队首，那么入队操作需要出栈所有元素暂存，并重新入栈所有元素；
 * 如果将栈底作为队首，那么出队操作需要出栈所有元素暂存，并重新入栈所有元素；
 * 所以，如果用一个栈，会导致入队或出队操作中，一个时间复杂度为O(1)，另一个为O(2N)，在不能确定大部分操作是
 * 何种类型之前，需要均摊时间服复杂度。
 * 
 * 可以使用双栈（TopAsFront 和 BottomAsFront）实现，且双栈在同一时间只有一个栈有数据，这样不会增加空间复杂度，
 * TopAsFront 作为队列容器时，栈顶表示队列头部，BottomAsFront 作为队列容器时，栈底作为队列头部。
 * 所以会遇到以下两种情况：
 * （1）入队时，如果 BottomAsFront 作为队列容器，则队尾就在栈顶，直接入栈即相当于入队，
 *		同理，出队时，如果 TopAsFront 作为队列容器，则队首就在栈顶，直接出栈即相当于出队；
 * （2）入队时，是 TopAsFront 作为队列容器，则需要将栈内数据出栈到 BottomAsFront，并将 BottomAsFront 
 *		作为队列的容器，然后再按照步骤（1）中的操作即可。同理，出队亦然。
 *		这里需要注意的是，因为 BottomAsFront 此时是作为队列容器的，所以如果继续进行入队操作，
 *		时间复杂度会降至O(1)，直到遇到出队操作。
 * 
 * 可以认为，在执行一次入队/出队操作后，下一次大概率会执行同样的操作，即使不是，入队/出队操作完全随机，
 * 当操作次数增加时，入队/出队操作的时间复杂度也会趋于相同，使得操作的时间复杂度得到均摊。
 * 还有一点，返回队首元素，因为不涉及容器数据量的变化，可以采用一个变量单独保存。
 *
 * 【解题分析】
 * 时间复杂度：O(N) 执行一次Push或Pop操作时复杂度为O(N)，若继续进行同类西操作，时间复杂度为O(1)，实现均摊 
 * 空间复杂度：O(N)
 *
 * @author FrankX
 * @date 2021-09-06
 **************************************************************************************************/
#include <iostream>
#include <stack>
using namespace std;

class MyQueue 
{
public:
	MyQueue() { }
	~MyQueue() { }

	void Push(int num)
	{
		// 此时栈底作为队列头部，直接入队，时间复杂度O(1) 
		if (!BottomAsFront.empty())
		{
			BottomAsFront.emplace(num);
			return;
		}

		if (!TopAsFront.empty())
			// BottomAsFront为空而TopAsFront非空，取TopAsFront栈顶作为队首元素 
			PeekData = TopAsFront.top(); 
		else
			// 双栈均空，那么num显然就是队首元素了 
			PeekData = num;

		// 若是栈顶作为队列头部，则将栈元素出栈到另一个栈 
		while (!TopAsFront.empty())
		{
			BottomAsFront.emplace(TopAsFront.top());
			TopAsFront.pop();
		}

		// 此时栈底作为队列头部，均摊入队出队时，需要进行栈操作的时间复杂度 
		BottomAsFront.emplace(num);
	}

	int Pop()
	{
		int popData = 0;

		// 若此时栈顶作为队列头部，直接出队，时间复杂度O(1) 
		if (!TopAsFront.empty())
		{
			popData = TopAsFront.top();
			TopAsFront.pop();
			PeekData = TopAsFront.top();
			return popData;
		}

		// 若是栈底作为队列头部，则将栈元素出栈到另一个栈 
		while (!BottomAsFront.empty())
		{
			TopAsFront.emplace(BottomAsFront.top());
			TopAsFront.pop();
		}

		// 此时栈顶作为队列头部，均摊入队出队时，需要进行栈操作的时间复杂度 
		popData = TopAsFront.top();
		TopAsFront.pop();
		PeekData = TopAsFront.top();
		return popData;
	}

	int Peek()
	{
		return PeekData;
	}

	bool Empty()
	{
		return (TopAsFront.empty() && BottomAsFront.empty());
	}

private:
	/** 栈顶作为队列头部，队列不为空时，BottomAsFront 和 TopAsFront 同时只能有一个存在数据 */
	stack<int> TopAsFront;
	/** 栈底作为队列头部，队列不为空时，BottomAsFront 和 TopAsFront 同时只能有一个存在数据 */
	stack<int> BottomAsFront;
	/** 保存队首元素 */
	int PeekData;
};

int main(int argc, char** argv)
{
	MyQueue* que = new MyQueue();

	que->Push(1);
	que->Push(2);
	int peekData = que->Peek();
	int popData = que->Pop();
	bool bEmpty = que->Empty();

	delete que;
	que = nullptr;

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 删除链表中节点数据等于给定值的节点。
 * 
 * 【输入】
 * Link List = 6,1,2,6,3,4,6
 * 【输出】
 * Link List after remove = 1,2,3,4
 * 
 * 【解题思路】
 * 依次遍历链表节点，将节点数据等于给定值的节点从链表中独立出来，释放其内存，同时保证链表的链接正确。
 * 可申请一个临时的节点指向链表头节点，这样每次处理的就是当前遍历节点的next，一来这样可以在遇到需要删除
 * 的节点时容易找到被删除节点的前一个节点，保证链表链接，二来如果首节点需要删除，则不用做额外的特殊处理。
 * 
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-08-19
 **************************************************************************************************/
#include <iostream>
#include <array>
using namespace std;

template<typename T>
struct Node
{
	T data;
	Node* next;

	Node(T _data)
	{
		data = _data;
		next = nullptr;
	}
};

#define N(T, var) (new Node<T>(var))

template<typename T>
void RemoveListElement(Node<T>*& head, const T& targetNum)
{
	/**
	 * 用一个头指针指向链表头节点，避免删除头节点的特殊处理， 
	 * 也使得能够轻易找到被删除节点的前一个节点，便于重新建立链接 
	 */
	Node<T>* tempHead = N(T, 0);
	tempHead->next = head;
	Node<T>* p = tempHead;
	Node<T>* delNode = nullptr;

	while (p->next)
	{
		if (p->next->data == targetNum)
		{
			// 将被移除节点独立保存，释放内存 
			delNode = p->next;
			p->next = p->next->next;

			delete delNode;
			delNode = nullptr;
		}
		else
			p = p->next;
	}

	// 如果首元素就是目标值，需要重新设置头指针 
	head = tempHead->next;
}

int main()
{
	array<int, 11> datas{ 6,1,2,3,6,4,5,6,7,8,6 };
	Node<int>* head = nullptr;
	Node<int>* p = nullptr;

	// 生成链表 
	for (array<int, 11>::iterator itr = datas.begin(); itr != datas.end(); ++itr)
	{
		if (!head)
		{
			head = N(int, *itr);
			p = head;
		}
		else
		{
			p->next = N(int, *itr);
			p = p->next;
		}
	}

	int targetNum = 6;
	cout << "The target number: " << targetNum;
	cout << "\nLink list data:\n";
	p = head;
	while (p)
	{
		cout << p->data << ", ";
		p = p->next;
	}

	RemoveListElement(head, targetNum);

	cout << "\nLink list after remove target:\n";
	p = head;
	while (p)
	{
		cout << p->data << ", ";
		p = p->next;
	}

	while (head)
	{
		p = head;
		head = head->next;

		delete p;
		p = nullptr;
	}

	cout << endl;
	return 0;
}
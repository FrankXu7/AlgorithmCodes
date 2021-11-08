/**************************************************************************************************
 * 【题目描述】
 * 给定一个单链表的头节点head，反转这个链表的头节点，head指向反转后链表的表头。
 *
 * 【输入】
 * LinkList=[1,2,3,4,5]
 * 【输出】
 * ReverseLinkList=[5,4,3,2,1]
 *
 * 【解题思路】
 * 因为链表节点有指向性，所以可以用常熟个辅助节点来反转链表，大致过程：
 * （1）取出原链表首个节点，并将头节点指针指向下一个节点；
 * （2）将取出的节点作为反转链表的首个节点；
 * （3）再次取出原链表首个节点，仍然需要将头节点指针指向下一个节点；
 * （4）新取出的节点指向步骤（2）的反转链表首个节点，并将新取出的节点作为反转链表新的头节点；
 * （5）重复步骤（3）和（4）直至原链表指向空。
 * 这里有一点需要注意的是，反转链表的首个节点，其next指向一定要置空，否则就变成一个循环链表了。
 * 
 * 核心伪代码：
 * TempNode = OldHead.Next; 原链表中取出首个节点
 * OldHead = OldeHead.Next; 更新原链表头节点指向
 * TempNode.Next = NewHead; 取出的节点指向反转链表头节点
 * NewHead = TempNode; 将取出的节点作为反转链表新的头节点
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-08-27
 **************************************************************************************************/
#include <iostream>
using namespace std;

template<typename T>
struct Node 
{
	T data;
	Node<T>* next;

	Node(T _data)
	{
		data = _data;
		next = nullptr;
	}
};

#define N(val, T) (new Node<T>(val))

template<typename T>
void ReverseList(Node<T>*& head)
{
	Node<T>* pOldHead = head->next;
	Node<T>* pNewHead = nullptr;
	Node<T>* node = nullptr;

	while (pOldHead)
	{
		node = pOldHead;
		pOldHead = pOldHead->next;

		if (!pNewHead)
		{
			pNewHead = node;
			// 第一个pTail作为反转后的尾节点，next一定要置空，否则就会变成一个循环链表了 
			pNewHead->next = nullptr;
		}
		else
		{
			node->next = pNewHead;
			pNewHead = node;
		}
	}

	// 头节点指针，指向新的链表头 
	head->next = pNewHead;
}

int main(char argc, char* argv[])
{
	Node<int>* head = N(-1, int);
	Node<int>* p = head;

	for (unsigned int idx = 0; idx < 20; ++idx)
	{
		p->next = N(idx + 1, int);
		p = p->next;
	}

	cout << "Link list:\n";
	p = head->next;
	while (p)
	{
		cout << p->data << ", ";
		p = p->next;
	}

	ReverseList<int>(head);

	cout << "\n\nReverse Link List:\n";
	p = head->next;
	while (p)
	{
		cout << p->data << ", ";
		p = p->next;
	}

	// 释放内存 
	while (head)
	{
		p = head;
		head = head->next;

		delete p;
	}
	p = nullptr;


	cout << endl << endl;
	return 0;
}
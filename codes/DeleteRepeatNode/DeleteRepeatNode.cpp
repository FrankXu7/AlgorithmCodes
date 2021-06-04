/**************************************************************************************************
 * 【题目描述】
 * 删除一个升序列表中的重复元素。
 *
 * 【输入】
 * list=[1,2,3,3,3,4,5]
 *
 * 【输出】
 * newList=[1,2,3,4,5]
 *
 * 【解题思路】
 * 因为链表是升序的，所以有重复的元素必定相邻。
 * 如果当前遍历节点的数据，等于下一个节点的数据，则当前节点的next，保存为下一个节点的next；
 * 即将下一个被删除的节点移除在链表关系之外。
 *
 * 需要注意的是：
 * （1）释放删除节点的内存，原则为同函数申请和释放，传入指针引用指向删除节点组合而成的链表。
 * （2）删除节点组合而成的链表，最后一个节点一定要置空，否则可能删除结果链表中的节点。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-04-16
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

template<typename TYPE>
struct ListNode
{
	TYPE data;
	ListNode<int>* next;
};

/**
 * head 使用【指针值传递】，函数复制了head指针，改变形参head的值不影响实参。
 * delHead 展现了另一种用法，使用【指针值引用】，形参delHead为实参别名，
 * 对形参delHead的改变实际上就是在改变实参。
 */
ListNode<int>* DeleteRepeatNode(ListNode<int>* head, ListNode<int>*& delHead)
{
	ListNode<int>* p = head;
	ListNode<int>* pDel = nullptr;

	while (p)
	{
		if (p->next && p->data == p->next->data)
		{
			if (pDel)
			{
				pDel->next = p->next;
				pDel = pDel->next;
			}
			else
			{
				pDel = p->next;
				delHead = pDel;
			}

			p->next = p->next->next;
		}
		else
		{
			p = p->next;
		}
	}

	return head;
}

int main()
{
	vector<int> listData = { 1, 2, 3, 3, 3, 4, 5 };
	
	ListNode<int>* head = new ListNode<int>;
	ListNode<int>* delHead = nullptr;
	ListNode<int>* p = head;

	for (vector<int>::iterator itr = listData.begin(); itr != listData.end(); ++itr)
	{
		p->data = *itr;
		if (itr + 1 != listData.end()) // 保证最后一个节点的next不申请内存 
		{
			p->next = new ListNode<int>;
			p = p->next;
		}
		// 保证末节点的next为空指针，便于判断，不置空的话可能有野指针值 
		p->next = nullptr;
	}

	head = DeleteRepeatNode(head, delHead);

	p = head;
	cout << "New List: ";
	while (p)
	{
		cout << p->data << "  ";
		p = p->next;
	}
	cout << endl;

	p = delHead;
	cout << "Delete Nodes: ";
	while (delHead)
	{
		cout << delHead->data << "  ";
		p = delHead;
		delHead = delHead->next;

		delete p;
		p = nullptr;
	}
	cout << endl;

	return 0;
}

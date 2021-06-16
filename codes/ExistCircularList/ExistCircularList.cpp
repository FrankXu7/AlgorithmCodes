/**************************************************************************************************
 * 【题目描述】
 * 判断一个给定的链表中，是否存在环路。即最后一个节点指向链路之前的某个节点。
 *
 * 【输入】
 * LinkedList=[1,2,3,4,5,6,7,8,9]
 * 
 * 【输出】
 * 是否存在环路
 *
 * 【解题思路】
 * 方法一：
 * 首先会想到给遍历的节点加上一个遍历过的标记，所以很容易有一个方案，将遍历过的节点地址存入一个map，
 * 当遍历到后续节点时，检查后续节点是否已经在map中存在。存在标识有环路，否则无环路。
 *
 * 方法二：
 * 标记每一个被遍历过的节点，则空间复杂度不是常量。可以考虑快慢指针，慢指针每次遍历前进1位，
 * 快指针每次前进2位。如果存在环路的话，快指针迟早会追到慢指针，即快慢指针地址值相同。否则快指针
 * 会更先一步遇到下一个指向为空的节点。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 * 方法二：
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-16
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

template<typename T>
struct Node
{
	T data;
	Node<T>* next;

	Node<T>(T _data)
	{
		data = _data;
		next = nullptr;
	}
};

#define N(value) (new Node<int>(value))

bool ExistCircularList_1(Node<int>* head)
{
	map<Node<int>*, bool> tempMap = { make_pair(head, true) };

	while (head)
	{
		if (tempMap.count(head->next) > 0) return true;

		tempMap.insert(make_pair(head->next, true));
		head = head->next;
	}

	return false;
}

bool ExistCircularList_2(Node<int>* head)
{
	Node<int>* pSlow = head;
	Node<int>* pFast = head->next;

	while (pSlow != pFast)
	{
		if (!pFast || !pFast->next)
		{
			return false;
		}

		pSlow = pSlow->next;
		pFast = pFast->next->next;
	}

	return true;
}

int main()
{
	vector<Node<int>*> dataArr = { N(10),N(11),N(12),N(13),N(14),N(15),N(16),N(17),N(18),N(19), };
	unsigned int maxIdx = dataArr.size() - 1;
	for (unsigned int idx = 0; idx < maxIdx; ++idx) dataArr[idx]->next = dataArr[idx + 1];
	dataArr[maxIdx]->next = dataArr[4];
	
	cout << "[Solution 1] Is circular linked list: " << (ExistCircularList_1(dataArr[0]) ? "YES\n" : "NO\n");
	cout << "[Solution 2] Is circular linked list: " << (ExistCircularList_2(dataArr[0]) ? "YES\n" : "NO\n");

	return 0;
}
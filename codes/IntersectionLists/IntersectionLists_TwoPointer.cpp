/**************************************************************************************************
 * 【题目描述】
 * 有两个不存在环形的单链表，找出并返回这两个单链表相交的起始节点，如果没有交点则返回nullptr；
 * 这里需要注意的是，相同的节点，指的是同一块内存，如果仅仅是数据相同，不一定是同一个节点。
 *
 * 【输入】
 * A: A1 -> A2 -> A3 -> C1 -> C2
 * B: B1 -> B2 -------> C1 -> C2
 *
 * 【输出】
 * 相交节点：C1
 *
 * 【解题思路】
 * 为了能够有常数的空间复杂度，可以采用双指针（假设为pA和pB）的方式，两个指针同时从两个单链表（假设为A和B）开始遍历，
 * 且两个单链表节点长度相差 n(n>=0)，若链表A遍历完，则链表B肯定还剩 n 个节点还未遍历，
 * 此时，pA重新指向链表B的头节点进行遍历，这时，pA和pB都在链表B上，且相差 n 个节点。同理，当pB遍历完后，
 * pB重新指向链表A的头节点进行遍历，如果两个单链表有交点，则在pA和pB遍历完切换到另一个链表进行遍历时，
 * 必定会相遇于相交节点。反之，则会无限的在链表A和B之间来回切换遍历，所以一定要标记切换的行为，有交点的情况下，
 * 双指针最多各进行一次切换能同时指向相交节点（相同长度时不用切换）。
 *
 * 【解题分析】
 * 时间复杂度：O(n) 最差的情况为两个链表长度之和，此时无相交节点，或相交节点无后继节点
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-30
 **************************************************************************************************/
#include <iostream>
#include <vector>
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

#define N(Type, value) (new Node<Type>(value)) 

#define PRINT(tip, pNode) cout << tip; \
while (pNode) \
{ \
	cout << pNode->data << ", "; \
	pNode = pNode->next; \
}

template<typename T>
Node<T>* IntersectionLists_TwoPointer(Node<T>* pList1, Node<T>* pList2)
{
	Node<T>* pNode1 = pList1;
	Node<T>* pNode2 = pList2;

	// 标记是否进行过头节点切换，如果两个单链表有交点，只需要最多一次头节点切换，则双指针会同时指向相交首节点
	bool exchanged1 = false;
	bool exchanged2 = false;

	while (pNode1 && pNode2)
	{
		if (pNode1 == pNode2)
			return pNode1;

		if (pNode1->next)
		{
			pNode1 = pNode1->next;
		}
		else if (!exchanged1)
		{
			pNode1 = pList2;
			exchanged1 = true;
		}
		else
		{
			pNode1 = nullptr;
		}

		if (pNode2->next)
		{
			pNode2 = pNode2->next;
		}
		else if (!exchanged2)
		{
			pNode2 = pList1;
			exchanged2 = true;
		}
		else
		{
			pNode2 = nullptr;
		}
	}

	return nullptr;
}

/**
 * @brief 创建一个链表
 * @param dataArr 节点数据容器，右值引用
 * @return 链表头节点
 */
template<typename T>
Node<T>* CreateList(vector<T>&& dataArr)
{
	Node<T>* pList = nullptr;
	Node<T>* pNode = nullptr;

	for (typename vector<T>::iterator itr = dataArr.begin(); itr != dataArr.end(); ++itr)
	{
		if (!pNode)
		{
			pList = pNode = N(T, *itr);
		}
		else
		{
			pNode->next = N(T, *itr);
			pNode = pNode->next;
		}
	}

	return pList;
}

/**
 * @brief 在链表末尾追加一个链表，也可以是单独的一个节点
 * @param pList 链表头节点
 * @param appendList 追加的链表头指针或节点指针
 */
template<typename T>
void AppendList(Node<T>* pList, Node<T>* appendList)
{
	if (!appendList) return;
	
	while (pList)
	{
		if (!pList->next)
		{
			pList->next = appendList;
			return;
		}
		pList = pList->next;
	}
}

/**
 * @brief 释放链表内存
 * @param pList 链表头节点
 * @param stopNode 中止节点，标识从此节点起为其它链表的组合，其它链表不应由它来释放，谁申请，谁释放
 */
template<typename T>
void DeleteList(Node<T>* pList, Node<T>* stopNode = nullptr)
{
	Node<T>* pNode = nullptr;
	while (pList && pList != stopNode)
	{
		pNode = pList;
		pList = pList->next;
		delete pNode;
	}
	pList = nullptr;
	pNode = nullptr;
}

int main()
{
	Node<int>* appendList = CreateList<int>({ 11, 22, 33, 44, 55 });
	Node<int>* pNode = appendList;
	PRINT("Append List:\n", pNode);

	Node<int>* pList1 = CreateList<int>({ 1001, 1002, 1003, 1004, 1005 });
	AppendList(pList1, appendList);
	pNode = pList1;
	PRINT("\n\nList 1:\n", pNode);

	Node<int>* pList2 = CreateList <int>({ 2001, 2002, 2003 });
	AppendList(pList2, appendList);
	pNode = pList2;
	PRINT("\n\nList 2:\n", pNode);

	pNode = IntersectionLists_TwoPointer(pList1, pList2);
	if (pNode)
		cout << "\n\nThe intersection node is: " << pNode->data << '(' << pNode << ")\n";
	else
		cout << "\n\nIntersection node not exist!\n";

	DeleteList(pList1, appendList);
	DeleteList(pList2, appendList);
	DeleteList(appendList);

	return 0;
}
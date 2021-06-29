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
 * 两个相交的单链表，它们从尾部节点开始，一定存在若干个相同的节点，所以可以遍历并将两个单链表的地址
 * 存储在两个容器数组内，然后再反向遍历容器元素。如果首个末尾元素不相同，则两个单链表没有相交节点，
 * 否则，一直从后往前反向遍历，直到找到两个不相同的节点为止，即找到了两个单链表相交的起始节点。
 *
 * 【解题分析】
 * 时间复杂度：O(n) 会有两轮独立的遍历，实际时间复杂度为：链表1的长度 + 链表2的长度
 * 空间复杂度：O(n) 两个容器数组存储链表地址，实际空间复杂度为：容器1的空间 + 容器2的空间
 *
 * @author FrankX
 * @date 2021-06-29
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

	bool isd = false;
};

#define N(Type, value) (new Node<Type>(value))

template<typename T>
Node<T>* IntersectionLists(Node<T>* pList1, Node<T>* pList2)
{
	if (!pList1 || !pList2) return nullptr;

	vector<Node<T>*> pVec1;
	vector<Node<T>*> pVec2;

	while (pList1 || pList2)
	{
		if (pList1)
		{
			pVec1.push_back(pList1);
			pList1 = pList1->next;
		}

		if (pList2)
		{
			pVec2.push_back(pList2);
			pList2 = pList2->next;
		}
	}

	Node<T>* pNode = nullptr;
	typename vector<Node<T>*>::reverse_iterator itr1 = pVec1.rbegin();
	typename vector<Node<T>*>::reverse_iterator itr2 = pVec2.rbegin();
	// 存在相同节点，找出第一个相同节点
	if (*itr1 == *itr2)
	{
		pNode = *itr1;
		++itr1;
		++itr2;
		for (; itr1 != pVec1.rend() && itr2 != pVec2.rend(); ++itr1, ++itr2)
		{
			if (*itr1 == *itr2) pNode = *itr1;
		}
	}

	return pNode;
}

/**
 * @brief 创建一个链表，并返回头指针
 * @param dataArr 构造数据，容器右值引用
 * @return 链表头指针
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
 * @brief 在个链表末尾追加节点，或追加另一个链表
 * @param pList 链表头节点
 * @param appendList 追加的链表头节点，或单个节点指针
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
			break;
		}
		pList = pList->next;
	}
}

/**
 * @brief 释放链表内存空间
 * @param pList 释放的链表
 * @param stopNode 中止节点，标识此链表由其它链表组合，其它链表不应由它来释放，谁申请，神释放
 */
template<typename T>
void DeleteList(Node<T>*& pList, Node<T>* const stopNode = nullptr)
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
	Node<int>* appendList = CreateList<int>({
	11, 22, 33, 44, 55 });

	Node<int>* pList1 = CreateList<int>({
		1001, 1002, 1003, 1004, 1005 });
	AppendList(pList1, appendList);

	Node<int>* pNode = pList1;
	cout << "List 1: \n";
	while (pNode)
	{
		cout << pNode->data << ", ";
		pNode = pNode->next;
	}

	Node<int>* pList2 = CreateList<int>({
		2001, 2002, 2003 });
	AppendList(pList2, appendList);

	pNode = pList2;
	cout << "\nList 2: \n";
	while (pNode)
	{
		cout << pNode->data << ", ";
		pNode = pNode->next;
	}

	pNode = IntersectionLists(pList1, pList2);
	if (pNode)
		cout << "\n\nIntersection node: " << pNode->data << '(' << pNode << ")\n";
	else
		cout << "\n\nIntersection node not exist!\n";

	DeleteList(pList1, appendList);
	DeleteList(pList2, appendList);
	DeleteList(appendList);

	return 0;
}
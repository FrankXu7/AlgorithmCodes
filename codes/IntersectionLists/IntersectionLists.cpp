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
 * 首先，两个单链表如果至少一个为空，肯定没有相交节点。
 * 然后考虑两个存在相交的单链表，它们从尾部节点开始，一定存在若干个相同的节点。
 * 所以可以将链表1节点地址保存到map，然后遍历链表2，看遍历链表2中的节点，是否在链表1生成的map中，
 * 如果存在则返回之，否则就是没有相交节点。
 *
 * 【解题分析】
 * 时间复杂度：O(N) 实际为两个链表长度之和，需要分别遍历两个链表1次
 * 空间复杂度：O(N) 
 *
 * @author FrankX
 * @date 2021-06-29
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T> *next;

	Node<T>(T _data)
	{
		data = _data;
		next = nullptr;
	}
};

#define N(Type, value) (new Node<Type>(value))

template <typename T>
Node<T> *IntersectionLists(Node<T> *pList1, Node<T> *pList2)
{
	if (!pList1 || !pList2)
		return nullptr;

	// 以节点作为key，保存在一个map中便于遍历
	map<Node<T> *, bool> mapList1;
	while (pList1)
	{
		mapList1.insert(make_pair(pList1, true));
		pList1 = pList1->next;
	}

	typename map<Node<T> *, bool>::iterator nodeItr;
	while (pList2)
	{
		// find接口的时间复杂度为O(logN)
		nodeItr = mapList1.find(pList2);
		if (nodeItr != mapList1.end())
		{
			// 找到后返回节点指针
			return nodeItr->first;
		}
		pList2 = pList2->next;
	}

	return nullptr;
}

/**
 * @brief 创建一个链表，并返回头指针
 * @param dataArr 构造数据，容器右值引用
 * @return 链表头指针
 */
template <typename T>
Node<T> *CreateList(vector<T> &&dataArr)
{
	Node<T> *pList = nullptr;
	Node<T> *pNode = nullptr;
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
template <typename T>
void AppendList(Node<T> *pList, Node<T> *appendList)
{
	if (!appendList)
		return;

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
template <typename T>
void DeleteList(Node<T> *&pList, Node<T> *const stopNode = nullptr)
{
	Node<T> *pNode = nullptr;
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
	Node<int> *appendList = CreateList<int>({11, 22, 33, 44, 55});

	Node<int> *pList1 = CreateList<int>({1001, 1002, 1003, 1004, 1005});
	AppendList(pList1, appendList);

	Node<int> *pNode = pList1;
	cout << "List 1: \n";
	while (pNode)
	{
		cout << pNode->data << ", ";
		pNode = pNode->next;
	}

	Node<int> *pList2 = CreateList<int>({2001, 2002, 2003});
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
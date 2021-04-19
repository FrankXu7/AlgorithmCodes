/**************************************************************************************************
 *
 * 【题目描述】
 * 合并两个升序链表，返回合并后的链表的头节点
 *
 * 【输入】
 * link1={1,3,5,7,9}
 * link2={2,4,6,8,10}
 * 【输出】
 * link={1,2,3,4,5,6,7,8,9,10}
 *
 * 【解题思路】
 * 并行比较两个链表数据，将两个链表表头节点数据更小的保存起来，同时更小数据所在链表的头节点需要后移一位，
 * 这里必须对表头节点后移一位，指针也是变量，对单独保存的节点后移一位并不改变头节点指针变量的值；
 * 将保存的节点追加到结果链表，需要注意的是，结果链表初始为空指针，需要额外判断结果链表是否为空。
 *
 * @author FrankX
 * @date 2021-04-19
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct LinkOb
{
	T data;
	LinkOb<T>* next;
};

LinkOb<int>* MergeTwoSortedLists(LinkOb<int>* l1, LinkOb<int>* l2)
{
	if (!l1 || !l2)
		return l1 ? l1 : l2;

	LinkOb<int>* resultArr = nullptr;
	LinkOb<int>* ptr = nullptr;
	LinkOb<int>* minPtr = nullptr;

	while (l1 && l2)
	{
		if (l1->data < l2->data)
		{
			minPtr = l1;
			l1 = l1->next;
		}
		else
		{
			minPtr = l2;
			l2 = l2->next;
		}

		if (resultArr)
		{
			ptr->next = minPtr;
			ptr = ptr->next;
		}
		else
		{
			ptr = resultArr = minPtr;
		}

		minPtr = minPtr->next;
	}

	if (l1) ptr->next = l1;
	else if (l2) ptr->next = l2;

	return resultArr;
}

/**
 * @brief 依据vector创建链表
 * @param dataArr 原始数据，vector容器
 * @param head 赋值好的链表头指针，指针引用
 */
template<typename T>
void SetLinkListData(vector<T>&& dataArr, LinkOb<T>*& head)
{
	LinkOb<T>* p = head;

	for (typename vector<T>::iterator itr = dataArr.begin(); itr != dataArr.end(); ++itr)
	{
		if (!head)
		{
			p = new LinkOb<T>();
			head = p;
		}

		p->data = *itr;
		if (itr + 1 != dataArr.end())
		{
			p->next = new LinkOb<T>();
			p = p->next;
		}
		else 
			p->next = nullptr;
	}
}

int main()
{
	LinkOb<int> *beMergeList = nullptr;
	LinkOb<int> *mergeList = nullptr;
	
	SetLinkListData({1,3,5,7,9}, beMergeList);
	SetLinkListData({2,4,6,8,10}, mergeList);

	// 完成合并后，beMergeList包含两个链表所有节点
	beMergeList = MergeTwoSortedLists(beMergeList, mergeList);
	// 合并完成后，mergeList的结构会被破坏，直接置空
	mergeList = nullptr;

	cout << "Merge result: " << endl;
	LinkOb<int> *p = beMergeList;
	while (beMergeList)
	{
		cout << beMergeList->data << ' ';
		p = beMergeList;
		beMergeList = beMergeList->next;
		delete p;
	}
	p = nullptr;
	beMergeList = nullptr;
	cout << endl;

	return 0;
}

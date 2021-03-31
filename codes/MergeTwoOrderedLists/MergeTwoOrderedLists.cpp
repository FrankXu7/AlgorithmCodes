/**************************************************************************************************
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
 * 合并链表并不会有废弃节点产生，故可将链表2合并到链表1，并返回链表1的头节点作为最终结果：
 *（1）遍历到链表1节点数据小于等于链表2节点数据，将链表2节点插入到链表1节点之后；
 *（2）遍历到链表1节点数据大于链表2节点数据，将链表2节点插入到链表1节点之前，需要特别注意的是，
 * 此时如果链表1节点为头节点，插入完成后，链表1头节点应该指向刚刚插入的链表2节点。
 *
 * @author FrankX
 * @date 2021-03-30
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

LinkOb<int>* MergeTwoOrderedLists(LinkOb<int>* l1, LinkOb<int>* l2)
{
	LinkOb<int> *r = l1;
	LinkOb<int> *last_r = nullptr;

	while (r && l2)
	{
		if (r->data <= l2->data)
		{
			last_r = r;
			r = l2;
			l2 = l2->next;
			r->next = last_r->next;
			last_r->next = r;
		}
		else
		{
			if (!last_r)
			{
				l1 = l2;
				l2 = l2->next;
				l1->next = r;
				last_r = l1;
			}
			else
			{
				last_r->next = l2;
				last_r = l2;
				l2 = l2->next;
				last_r->next = r;
			}
		}
	}

	if (l2) r ? r->next = l2 : last_r->next = l2;

	return l2;
}

int main()
{
	LinkOb<int> *resultArr = new LinkOb<int>();
	LinkOb<int> *mergeArr = new LinkOb<int>();

	LinkOb<int> *pr = resultArr;
	LinkOb<int> *pm = mergeArr;
	
	vector<int> arr1 = { 2 };
	vector<int> arr2 = { 1, 3 };

	for (int i = 0; i < arr1.size() || i < arr2.size(); ++i)
	{
		if (i < arr1.size())
		{
			pr->data = arr1[i];
			if (i + 1 < arr1.size())
			{
				pr->next = new LinkOb<int>();
				pr = pr->next;
			}
		}

		if (i < arr2.size())
		{
			pm->data = arr2[i];
			if (i + 1 < arr2.size())
			{
				pm->next = new LinkOb<int>();
				pm = pm->next;
			}
		}
	}

	// 完成合并后，resultArr包含两个链表所有节点
	resultArr = MergeTwoOrderedLists(resultArr, mergeArr);
	// 合并完成后，mergeArr的结构会被破坏，直接置空
	mergeArr = nullptr;
	pm = nullptr;

	cout << "Merge result: " << endl;
	while (resultArr)
	{
		cout << resultArr->data << ' ';
		pr = resultArr;
		resultArr = resultArr->next;
		delete pr;
	}
	pr = nullptr;
	resultArr = nullptr;
	cout << endl;

	return 0;
}

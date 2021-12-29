/**************************************************************************************************
 * 【题目描述】
 * 给你两个非空的链表，表示两个非负的整数。它们每位数字都是按照【逆序】的方式存储的（即最高位在链表尾部），
 * 并且每个节点只能存储一位数字。 请你将两个数相加，并以相同形式返回一个表示和的链表。 你可以假设除了数字0
 * 之外，这两个数都不会以0开头。
 *
 * 【输入】
 * list1=[2,4,3]; 代表数字：342
 * list2=[5,6,4]; 代表数字：465
 * 【输出】
 * 相加得到链表：[7,0,8]; 代表数字：807
 * 
 * 【解题思路】
 * 方法一：
 * 因为两个链表代表的数字是逆序存储的，所以可以直接从表头开始进行低位的相加计算，这里需要特别注意的还要额
 * 外加上上一次计算的进位，并且还需要判断相加结果是否需要进位。两个链表长度可能不相等，故循环的终止条件为
 * 两个链表都遍历完成。最后需要注意的是，终止循环时，可能还存在进位，需要单独再处理一次。
 * 
 * 方法二：
 * 和方法一思路一样，不同之处在于使用了内置的单向链表forward_list，而方法一使用的是自定义的链表节点结构。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(max(M,N))，M和N为两个链表长度
 * 空间复杂度：1
 * 方法二：
 * 时间复杂度：O(N) 实际为O(max(M,N))，M和N为两个链表长度
 * 空间复杂度：1
 * 
 * @author FrankX
 * @date 2021-12-29
 *************************************************************************************************/
#include <iostream>
#include <forward_list>
using namespace std;

/** 自定义链表节点结构 */
struct ListNode
{
	int data;
	shared_ptr<ListNode> next;

	ListNode(int val)
	{
		data = val;
		next = nullptr;
	}
};

auto AddTwoNums_1(shared_ptr<ListNode> list1, decltype(list1) list2) -> decltype(list1)
{
	decltype(list1) ansList = nullptr, pNode = nullptr;

	// 因为题意要求每个节点都是单个数字，故进位至多是1 
	int carryOver = 0, addNum = 0;
	while (list1 || list2)
	{
		addNum = (list1 ? list1->data : 0) + (list2 ? list2->data : 0) + carryOver;
		carryOver = addNum >= 10 ? 1 : 0;
		if (carryOver) addNum %= 10;

		if (!ansList) ansList = pNode = make_shared<ListNode>(addNum);
		else
		{
			pNode->next = make_shared<ListNode>(addNum);
			pNode = pNode->next;
		}

		if (list1) list1 = list1->next;
		if (list2) list2 = list2->next;
	}

	// 最后一步有进位，不可忽略 
	if (carryOver) pNode->next = make_shared<ListNode>(carryOver);

	return ansList;
}

forward_list<int> AddTwoNums_2(forward_list<int> list1, forward_list<int> list2)
{
	forward_list<int> ansList;
	forward_list<int>::iterator end1 = list1.end(), end2 = list2.end();
	// befor_begin返回begin之前的位置，避免链表为空时begin和end相等，导致插入报错 
	forward_list<int>::iterator inPos = ansList.before_begin();

	// 因为题意要求每个节点都是单个数字，故进位至多是1 
	int carryOver = 0, addNum = 0;
	for (auto itr1 = list1.begin(), itr2 = list2.begin(); itr1 != end1 || itr2 != end2;)
	{
		addNum = (itr1 != end1 ? *itr1 : 0) + (itr2 != end2 ? *itr2 : 0) + carryOver;
		carryOver = addNum >= 10 ? 1 : 0;
		if (carryOver) addNum %= 10;

		inPos = ansList.emplace_after(inPos, addNum);

		if (itr1 != end1) ++itr1;
		if (itr2 != end2) ++itr2;
	}

	// 最后一步有进位，不可忽略 
	if (carryOver) ansList.emplace_after(inPos, carryOver);

	return ansList;
}

int main(int argc, char* argv[])
{
	shared_ptr<ListNode> list1 = nullptr, list2 = nullptr, pNode = nullptr;
	initializer_list<int> dataArr1{ 9,9,9,9,9,9,9 };
	initializer_list<int> dataArr2{ 9,9,9,9 };

	// 依据初始化列表对象设置链表数据 
	auto SetListData = [&pNode](initializer_list<int>& dataArr, shared_ptr<ListNode>& pList) {
		for (int num : dataArr)
		{
			if (!pList) pList = pNode = make_shared<ListNode>(num);
			else
			{
				pNode->next = make_shared<ListNode>(num);
				pNode = pNode->next;
			}
		}
	};

	SetListData(dataArr1, list1);
	SetListData(dataArr2, list2);

	auto PrintList = [](shared_ptr<ListNode> pList) {
		while (pList)
		{
			cout << pList->data << ", ";
			pList = pList->next;
		}
	};

	cout << "Link list 1 data:\n";
	PrintList(list1);
	cout << "\nLink list 2 data:\n";
	PrintList(list2);

	cout << "\n\n[Solution 1] Add two link list:\n";
	PrintList(AddTwoNums_1(list1, list2));

	forward_list<int> fList1, fList2;
	fList1.assign(dataArr1.begin(), dataArr1.end());
	fList2.assign(dataArr2.begin(), dataArr2.end());
	forward_list<int> ansList = AddTwoNums_2(fList1, fList2);
	cout << "\n\n[Solution 2] Add two link list:\n";
	for (auto num : ansList)
	{
		cout << num << ", ";
	}

	cout << endl << endl;
	return 0;
}
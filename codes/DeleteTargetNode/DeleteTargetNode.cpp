/**************************************************************************************************
 * 【题目描述】
 * 删除链表中的某个指定节点，该题有以下限制条件：
 * （1）算法函数只能接受节点指针作为参数，且不能有返回值；
 * （2）链表中至少有两个节点；
 * （3）不能删除最后一个节点；
 * （4）节点的数据值都是唯一的；
 *
 * 【输入】
 * List Nodes=[1,2,3,4,5]
 * Delete Node: 4
 * 【输出】
 * List Nodes=[1,2,3,5]
 *
 * 【解题思路】
 * 删除链表中节点，最先会想到的就是正儿八经的遍历一遍，找到数据与指定值相等的节点，移除之。
 * 但题中有很多限制条件，比如参数只能是被删除节点，故只能从被删除节点开始访问到下一个节点，
 * 所以，可以将下一个节点的值赋值到被删除节点，并且将被删除节点指向下一个节点的再下一个节点，
 * 这样被删除节点的数据被替换为了它的下一个节点的数据，且指向也被正确设置，就相当于是删除了指定节点。
 * 
 * 此法不能删除最后一个节点，因为传入的被删除节点无法往回访问，但题中限制了不能删除尾节点且各节点数据值唯一。
 * 
 * 【解题分析】
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 * 
 * 符合链表特性，已知节点的情况下，操作的复杂度都是O(1)
 *
 * @author FrankX
 * @date 2021-09-14
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template<typename DataType>
struct ListNode
{
	DataType data;
	shared_ptr<ListNode<DataType>> next;

	ListNode(DataType _data)
	{
		data = _data;
	}
};

#define N(val, DataType) (make_shared<ListNode<DataType>>(val))

template<typename sp_ListNode>
void DeleteTargetNode(sp_ListNode &delNode)
{
	if (delNode->next)
	{
		// 将被删节点的数据赋值为下一个节点数据 
		delNode->data = delNode->next->data;
		// 移除下一个节点，就相当于删除了指定节点 
		delNode->next = delNode->next->next;
	}
	else
		cout << "\n\nCan't delete the last node!\n\n";
}

int main(int argc, char** argv)
{
	vector<int> dataArr{ 1,2,3,4,5 };
	// 最好有个头指针指向首个节点，以防对列表首个节点有增删操作，头指针不属于链表数据节点 
	auto head = make_shared<ListNode<int>>(0);
	decltype(head) sp = head;
	decltype(head) delNode = nullptr;

	for (auto itr = dataArr.begin(); itr != dataArr.end(); ++itr)
	{
		sp->next = make_shared<ListNode<int>>(*itr);
		if (*itr == 5) delNode = sp->next;
		sp = sp->next;
	}

	cout << "List Nodes:\n";
	sp = head->next;
	while (sp)
	{
		cout << sp->data << ", ";
		sp = sp->next;
	}

	cout << "\n\nAfter delete node [" << delNode->data << "] :\n";
	DeleteTargetNode(delNode);
	
	sp = head->next;
	while (sp)
	{
		cout << sp->data << ", ";
		sp = sp->next;
	}

	cout << endl << endl;
	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 给定一个单链表，删除链表到数第 appointEnd 个节点，并返回头节点，appointEnd 从 1 开始数。
 *
 * 【输入】
 * SingleLinkedList = [ 1,2,3,4,5 ]; AppointEnd = 4;
 * 【输出】
 * SingleLinkedList = [ 1,3,4,5 ];
 * 删除到数第四个节点，移除结点 2；
 *
 * 【解题思路】
 * 方法一：
 * 因为是单向链表，不能直接从尾部开始访问，故可以先来一次遍历，统计链表的节点数量（nodeCount），然后计算出
 * 被删除节点的正序顺序：nodeCount - appointEnd + 1，最后再进行一次遍历，通过正序顺序找到被删除节点。
 * 
 * 方法二：
 * 利用栈先进后出的特性，遍历单链表，将节点依次入栈。然后出栈的顺序，即为从单链表尾部遍历的顺序，依据题中
 * 给出的到数顺序 appointEnd，找到被删除的节点。
 * 
 * 方法三：
 * 利用双指针，更确切的说是前后指针，如果前指针 first 和后指针 second 间隔的节点数量刚好为 appointEnd 时，
 * 此时同时移动前后指针，当 first 指向节点末尾时，second 指针会刚好指向到数第 appointEnd 个节点。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(2N)，统计节点数遍历一次，删除节点还需遍历一次
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N) 实际为O(2N)，节点入栈遍历一次，删除节点还需遍历一次
 * 空间复杂度：O(N) 需要要给栈来暂存节点
 * 方法三：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-01-25
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/** 单链表数据结构 */
template<typename DataType>
struct ListNode
{
	DataType data;
	shared_ptr<ListNode<DataType>> next;

	ListNode(DataType _data) { data = _data; }
};

/** 便于创建单链表节点 */
#define N(val, valType) (make_shared<ListNode<valType>>(val))

template<typename DataType>
auto DeleteNodeFromEnd_1(shared_ptr<ListNode<DataType>> root, unsigned int appointEnd)
{
	// 顺序不可能为负，按题意到数顺序从1开始
	if (!root || appointEnd == 0) return root;

	unsigned int nodeCount = 0;
	decltype(root) node = root;
	// 统计单链表节点个数 
	while (node)
	{
		++nodeCount;
		node = node->next;
	}

	// 依据删除到数第 appointEnd，计算正序删除时需要遍历的节点数量 
	nodeCount = nodeCount - appointEnd + 1;

	decltype(root) lastNode;
	node = root;
	while (node)
	{
		if (--nodeCount == 0)
		{
			if (node == root) root = root->next; // 删除头节点
			else if (node->next) lastNode->next = node->next; // 删中间节点 
			else lastNode->next = nullptr; // 删尾部节点 

			break;
		}

		lastNode = node;
		node = node->next;
	}

	return root;
}

template<typename DataType>
auto DeleteNodeFromEnd_2(shared_ptr<ListNode<DataType>> root, unsigned int appointEnd)
{
	// 顺序不可能为负，按题意到数顺序从1开始
	if (!root || appointEnd == 0) return root;

	stack<decltype(root)> stk;
	decltype(root) node = root;
	while (node)
	{
		stk.emplace(node);
		node = node->next;
	}

	unsigned int nodeCount = 0;
	node = root;
	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();
		++nodeCount;

		if (nodeCount == appointEnd)
		{
			if (stk.empty()) root = root->next; // 删除头节点
			else if (node->next) stk.top()->next = node->next; // 删中间节点 
			else stk.top()->next = nullptr; // 删尾部节点 
		}
	}

	return root;
}

template<typename DataType>
auto DeleteNodeFromEnd_3(shared_ptr<ListNode<DataType>> root, unsigned int appointEnd)
{
	decltype(root) first = root, second = root, lastNode;
	unsigned int nodeCount = 0;

	while (first)
	{
		if (nodeCount < appointEnd)
		{
			// 先移动 first 指针，使得前后指针相距 appointEnd 个节点 
			++nodeCount;
		}
		else
		{
			/**
			 * 当前后指针相距 appointEnd 个节点时，同时移动前后指针，而后 first 指向链表尾部时，second
			 * 指向的就是到数第 appointEnd 个节点了
			 */
			lastNode = second;
			second = second->next;
		}

		first = first->next;
	}

	if (second != root)
		lastNode->next = second->next;
	else
		root = root->next;

	return root;
}

/**
 * 构造一个单链表
 * @param listData 数据引用
 */
template<typename DataType>
shared_ptr<ListNode<DataType>> CreateLinkedList(vector<DataType>& listData)
{
	shared_ptr<ListNode<DataType>> root;
	decltype(root) node;
	for (int num : listData)
	{
		if (!root) root = node = N(num, DataType);
		else
		{
			node->next = N(num, DataType);
			node = node->next;
		}
	}
	return root;
}

/**
 * 打印链表数据
 * @param root 链表头节点，值传递
 */
template<typename DataType>
void PrintLinkedList(shared_ptr<ListNode<DataType>> root)
{
	while (root)
	{
		cout << root->data << ", ";
		root = root->next;
	}
}


int main(int argc, char* argv[])
{
	shared_ptr<ListNode<int>> root;
	unsigned int appointEnd = 1;
	vector<int> listData = { 1,2,3,4,5 };

	root = CreateLinkedList(listData);
	cout << "The given single linked list:\n";
	PrintLinkedList(root);
	cout << "\nDelete the No." << appointEnd << " node from the end.";

	root = DeleteNodeFromEnd_1(root, appointEnd);
	cout << "\n\n[Solution 1] The single linked list fter delete:\n";
	PrintLinkedList(root);

	root = CreateLinkedList(listData);
	root = DeleteNodeFromEnd_2(root, appointEnd);
	cout << "\n\n[Solution 2] The single linked list fter delete:\n";
	PrintLinkedList(root);

	root = CreateLinkedList(listData);
	root = DeleteNodeFromEnd_3(root, appointEnd);
	cout << "\n\n[Solution 3] The single linked list fter delete:\n";
	PrintLinkedList(root);

	cout << endl << endl;
	return 0;
}
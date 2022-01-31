/**************************************************************************************************
 * 【题目描述】
 * 给定一个单链表，两两交换其中相邻的节点，并返回交换后新链表的头节点。要求不能修改节点的数据，只能进行节
 * 点的交换。
 *
 * 【输入】
 * LinkedList = [1,2,3,4,5,6];
 * 【输出】
 * SwapNodesInPairs = [2,1,4,3,6,5];
 *
 * 【解题思路】
 * 方法一：
 * 递归法，对于局部进行两两交换的节点链，头节点会变成新的局部节点链的第二个节点，原先的第二个节点会变成新
 * 的局部节点链的头节点。在递归的调用中，先暂存局部节点链的第二个节点 curNode->next，暂存的其实就是新的头
 * 节点，使 curNode 指向 curNode->next->next，这一步其实就是换头，然后将之前暂存在新头指向 curNode 即可。
 *
 * 方法二：
 * 迭代法，相较于递归法，拥有常数级别的空间复杂度，且逻辑上更好理解。首先，定义一个空节点 superRoot 用以
 * 指向链表头节点，在后续的遍历中，实际交换的就是 superRoot 后面两个相邻的节点，一轮交换完成后，superRoot
 * 需要指向 superRoot->next->next。需要注意的是，交换的左右节点中，如果左节点等于 root，那么在本轮交换后，
 * 需要将 root 执行右节点，最后返回的就是 root。
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-01-31
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

template<typename DataType>
struct ListNode
{
	DataType data;
	shared_ptr<ListNode<DataType>> next;

	ListNode(DataType _data) { data = _data; }
};

#define N(val, DataType) (make_shared<ListNode<DataType>>(val))

template<typename DataType>
shared_ptr<ListNode<DataType>> SwapNodesInPairs_1(shared_ptr<ListNode<DataType>> root)
{
	if (!root || !root->next) return root;

	decltype(root) newRoot = root->next;
	// 交换 root 后面的两个节点，root 最终指向 root->next->next 
	root->next = SwapNodesInPairs_1(root->next->next);
	newRoot->next = root;

	return newRoot;
}

template<typename DataType>
shared_ptr<ListNode<DataType>> SwapNodesInPairs_2(shared_ptr<ListNode<DataType>> root)
{
	decltype(root) leftNode, rightNode, node = root, superRoot = N(0, DataType);
	superRoot->next = root;

	while (superRoot && superRoot->next && superRoot->next->next)
	{
		leftNode = superRoot->next;
		rightNode = superRoot->next->next;

		// 交换 superRoot 后面两个相邻的左右节点 
		superRoot->next = rightNode;
		leftNode->next = rightNode->next;
		rightNode->next = leftNode;

		superRoot = leftNode;
		if (leftNode == root) root = rightNode;
	}

	return root;
}

/**
 * @brief 辅助函数，用以生成链表
 * @param listData 链表节点数据数组
 * @return 返回链表头节点
 */
template<typename DataType>
shared_ptr<ListNode<DataType>> CreateList(vector<DataType> listData)
{
	shared_ptr<ListNode<DataType>> root, node;

	for (DataType num : listData)
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
 * @brief 辅助函数，用以打印链表节点
 * @param root 链表头节点
 */
template<typename DataType>
void PrintList(shared_ptr<ListNode<DataType>> root)
{
	while (root)
	{
		cout << root->data << ", ";
		root = root->next;
	}
}


int main(int argc, char** argv)
{
	vector<int> listData = { 1,2,3,4,5,6 };
	shared_ptr<ListNode<int>> root;

	root = CreateList(listData);
	cout << "The given linked list data:\n";
	PrintList(root);

	root = SwapNodesInPairs_1(root);
	cout << "\n\n[Solution 1] Swap the linked list nodes in pairs:\n";
	PrintList(root);

	root = CreateList(listData);
	root = SwapNodesInPairs_2(root);
	cout << "\n\n[Colution 2] Swap the linked list nodes in pairs:\n";
	PrintList(root);


	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 给定一个目标整数，在一颗二叉树中，判断是否存在一条路径上所有节点值之和等于该目标整数的路径。二叉树一条
 * 路径定义为从根节点到叶节点的一条分支。
 * 
 * 【输入】
 * 一颗二叉树 treeRoot
 * 目标整数 targetNum
 *
 * 【输出】
 * 是否存在题中所要求的路径
 *
 * 【解题思路】
 * 可以发现规律：在二叉树中，从树根结点到某节点的路径一定是唯一的。采用自顶向下的策略，将当前结点及传入的
 * 路径上祖先结点之和，分别传入左右子树；直到叶节点位置，判断和是否等于给定的目标整数，符合中序遍历，大致
 * 步骤：
 * （1）传入树根结点，以及到达当前节点的祖先路径上节点之和，目标整数引用；
 * （2）将当前节点的值与祖先节点之和相加，并传入到左右子节点中；
 * （3）递归（1）（2）步骤直至叶节点，判断此时的和是否与目标整数相等。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(H)，H为数的高度，此处空间复杂度主要取决于树的高度，最差的情况为单链表，空间复杂度为O(N)，
 *            平均情况下树的高度与结点数的对数正相关，空间复杂度为O(logN)。
 * 
 * @author FrankX
 * @date 2021-05-25
 **************************************************************************************************/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T> *dad;
	TreeNode<T> *left;
	TreeNode<T> *right;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define NODE(value) (new TreeNode<int>(value))

bool BinaryTreePathSum_DFS(const TreeNode<int> *treeRoot, int curSum, const int &targetNum)
{
	if (!treeRoot)
		return false;

	curSum += treeRoot->data;
	if (!treeRoot->left && !treeRoot->right)
		return (curSum == targetNum);

	return BinaryTreePathSum_DFS(treeRoot->left, curSum, targetNum) || BinaryTreePathSum_DFS(treeRoot->right, curSum, targetNum);
}

/**
 * @brief 创建一颗二叉树，并非BST树或AVL树
 * @param treeData 二叉树数据源，右值引用
 * @param treeRoot 二叉树根节点，指针引用
 */
void CreateTree(vector<TreeNode<int> *> &&treeData, TreeNode<int> *&treeRoot)
{
	// 首元素为空当空树处理
	if (treeData.empty() || !treeData[0])
	{
		// 释放容器中的堆内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		return;
	}

	treeRoot = treeData[0];
	TreeNode<int> *node = nullptr;
	unsigned int dataSize = treeData.size();

	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];

		if (++n < dataSize && node)
		{
			node->left = treeData[n];
			if (node->left)
				node->left->dad = node;
		}
		if (++n < dataSize && node)
		{
			node->right = treeData[n];
			if (node->right)
				node->right->dad = node;
		}
	}
}

/**
 * @brief 释放一颗二叉树内存
 * @param treeRoot 树根节点，指针引用
 */
void DeleteTree(TreeNode<int> *&treeRoot)
{
	if (!treeRoot)
		return;

	queue<TreeNode<int> *> delQue({treeRoot});

	while (!delQue.empty())
	{
		treeRoot = delQue.front();
		delQue.pop();

		if (treeRoot->left)
			delQue.push(treeRoot->left);

		if (treeRoot->right)
			delQue.push(treeRoot->right);

		delete treeRoot;
	}

	treeRoot = nullptr;
}

/**
 * @brief 打印一颗二叉树
 * @param treeRoot 树根节点
 */
void PrintTree(const TreeNode<int> *treeRoot)
{
	if (!treeRoot)
	{
		cout << "Empty Tree!\n\n";
		return;
	}

	queue<const TreeNode<int> *> printQue({treeRoot});
	queue<const TreeNode<int> *> tempQue;
	int layerCount = 0;

	while (!printQue.empty())
	{
		cout << '[' << ++layerCount << "]  ";
		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();

			if (treeRoot)
			{
				cout << treeRoot->data;
				if (treeRoot->dad)
					cout << '(' << treeRoot->dad->data << "),";
				else
					cout << "(null),";
			}

			if (treeRoot && treeRoot->left)
				tempQue.push(treeRoot->left);
			if (treeRoot && treeRoot->right)
				tempQue.push(treeRoot->right);
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	TreeNode<int> *root = nullptr;

	CreateTree({
				   NODE(5),
				   NODE(4),
				   NODE(8),
				   NODE(11),
				   nullptr,
				   NODE(13),
				   NODE(99),
				   NODE(7),
				   NODE(2),
				   nullptr,
				   nullptr,
				   nullptr,
				   nullptr,
				   nullptr,
				   NODE(1),
			   },
			   root);

	PrintTree(root);

	int targetNum = 0;
	cout << "Input target number:\n";
	cin >> targetNum;
	cout << "\nHas any path node value sum equal the target number?\n";
	cout << (BinaryTreePathSum_DFS(root, 0, targetNum) ? "true" : "false") << endl
		 << endl;

	DeleteTree(root);

	return 0;
}

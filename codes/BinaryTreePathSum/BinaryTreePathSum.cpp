/**************************************************************************************************
 * 【题目描述】
 * 
 *
 * 【输入】
 * 
 *
 * 【输出】
 * 
 *
 * 【解题思路】
 * 
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* dad;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define NODE(value) (new TreeNode<int>(value))

int BinaryTreePathSum(const TreeNode<int>* treeRoot, int curSum, const int& targetNum)
{
	int leftSum = curSum;
	int rightSum = curSum;

	if (treeRoot && treeRoot->left)
	{
		leftSum = BinaryTreePathSum(treeRoot->left, curSum + treeRoot->left->data, targetNum);
	}

	if (treeRoot && treeRoot->right)
	{
		rightSum = BinaryTreePathSum(treeRoot->right, curSum + treeRoot->right->data, targetNum);
	}

	return (leftSum + rightSum);
}

/**
 * @brief 创建一颗二叉树，并非BST树或AVL树
 * @param treeData 二叉树数据源，右值引用
 * @param treeRoot 二叉树根节点，指针引用
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = nullptr;
	TreeNode<int>* node = nullptr;
	unsigned int dataSize = treeData.size();

	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];
		if (!node)
		{
			if (idx + 1 > n) ++n;
		}
		else if (!treeRoot)
			treeRoot = node;

		if (node && ++n < dataSize)
		{
			node->left = treeData[n];
			if (node->left) node->left->dad = node;
		}

		if (node && ++n < dataSize)
		{
			node->right = treeData[n];
			if (node->right) node->right->dad = node;
		}
	
	}
}

/**
 * @brief 释放一颗二叉树内存
 * @param treeRoot 树根节点，指针引用
 */
void DeleteTree(TreeNode<int>*& treeRoot)
{
	queue<TreeNode<int>*> delQue({ treeRoot });

	while (!delQue.empty()) 
	{
		treeRoot = delQue.front();
		delQue.pop();

		if (treeRoot && treeRoot->left)
		{
			delQue.push(treeRoot->left);
		}

		if (treeRoot && treeRoot->right)
		{
			delQue.push(treeRoot->right);
		}

		delete treeRoot;
	}

	treeRoot = nullptr;
}

/**
 * @brief 打印一颗二叉树
 * @param treeRoot 树根节点
 */
void PrintTree(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
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
	TreeNode<int>* root = nullptr;

	CreateTree({
		NODE(5), 
		NODE(4), NODE(8), 
		NODE(11), nullptr, NODE(13), NODE(4), 
		NODE(7), NODE(2), nullptr, nullptr, nullptr, nullptr, nullptr, NODE(1),
	}, root);

	PrintTree(root);

	DeleteTree(root);

	return 0;
}


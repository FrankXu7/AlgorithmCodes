/**************************************************************************************************
 * 【题目描述】
 * 
 *
 * 【输入】
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
#include <utility>
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

unsigned int BinaryTreeMinDepth_BFS(const TreeNode<int>* treeRoot)
{
	if (!treeRoot) return 0;

	queue<pair<TreeNode<int>*, int>> que;
	pair<TreeNode<int>*, int>(treeRoot, treeRoot->data)

	return 0;
}

/**
 * @brief 创建一颗二叉树
 * @param treeData 二叉树结点数据容器，右值引用
 * @param treeRoot 树根结点，指针引用
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	// 空容器或首节点为空，当作空树处理
	if (treeData.empty() || !treeRoot)
	{
		// 释放容器内的堆内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		return;
	}

	TreeNode<int>* node = nullptr;
	unsigned int idx = 0, n = 0, dataSize = treeData.size();
	for (; n < dataSize; ++idx)
	{
		node = treeData[idx];

		if (++n < dataSize && node)
		{
			node->left = treeData[n];
			if (node->left) node->left->dad = node;
		}
		if (++n < dataSize && node)
		{
			node->right = treeData[n];
			if (node->right) node->right->dad = node;
		}
	}
}

/**
 * @brief 释放二叉树内存
 * @param treeRoot 树根节点，指针引用，释放后置nullptr
 */
void DeleteTree(TreeNode<int>*& treeRoot)
{
	if (!treeRoot) return;

	queue<TreeNode<int>*> delQue({ treeRoot });
	while (!delQue.empty())
	{
		treeRoot = delQue.front();
		delQue.pop();

		if (treeRoot->left) delQue.push(treeRoot->left);
		if (treeRoot->right) delQue.push(treeRoot->right);

		delete treeRoot;
	}
	treeRoot = nullptr;
}

/**
 * @brief 按BFS遍历打印一颗二叉树
 * @param treeRoot 树根节点，常量指针，不可更改指向的数据
 */
void PrintTree(const TreeNode<int>* treeRoot)
{
	if (!treeRoot)
	{
		cout << "Empty tree!\n";
		return;
	}

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
				if (treeRoot->dad) cout << '(' << treeRoot->dad->data << "), ";
				else cout << "(null), ";
			}

			if (treeRoot->left) tempQue.push(treeRoot->left);
			if (treeRoot->right) tempQue.push(treeRoot->right);
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	TreeNode<int>* root = nullptr;
	CreateTree({
		NODE(1),
		NODE(2), NODE(3),
		NODE(4), NODE(5), NODE(6), NODE(7),
		NODE(8), NODE(9), NODE(10), NODE(11), NODE(12), nullptr, nullptr, nullptr,
		NODE(13), NODE(14), NODE(15), nullptr, nullptr, NODE(16)
		}, root);

	PrintTree(root);

	cout << "\nThe Mininum binary tree depth: " << BinaryTreeMinDepth_BFS(root) << endl;

	DeleteTree(root);

	cout << endl;
	return 0;
}

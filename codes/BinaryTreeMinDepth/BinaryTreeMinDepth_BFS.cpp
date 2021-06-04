/**************************************************************************************************
 * 【题目描述】
 * 找出一颗二叉树的最小深度。
 *
 * 【输入】
 * 一颗二叉树，不一定是AVL或BST树
 * 【输出】
 * 该二叉树的最小深度
 * 
 * 【解题思路】
 * 小深度即为根节点到最近的叶子节点的最小路径。
 * 因为遇到的第一个叶子结点的深度即为当前二叉树的最小深度，
 * 考虑自顶向下的方式逐层计算深度，遍历符合层次遍历，大致过程：
 * （1）构建一个pair为元素的队列，值分别为树结点和其所在深度，显然树根结点为第一层；
 * （2）BFS遍历树，当前结点的左右子节点深度+1，并构建pair入队；
 * （3）当遍历到叶子结点时，返回其当前深度即为二叉树的最小深度；
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 
 * @author FrankX
 * @date 2021-05-28
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

unsigned int BinaryTreeMinDepth_BFS(TreeNode<int>* treeRoot)
{
	if (!treeRoot) return 0;
	
	queue<pair<TreeNode<int>*, int>> que({ make_pair(treeRoot, 1) });
	int curLayer = 0;

	while (!que.empty())
	{
		treeRoot = que.front().first;
		curLayer = que.front().second;
		que.pop();

		if (!treeRoot->left && !treeRoot->right) 
			return curLayer;

		if (treeRoot->left)
			que.push(make_pair(treeRoot->left, curLayer + 1));
		if (treeRoot->right)
			que.push(make_pair(treeRoot->right, curLayer + 1));
	}

	return 0;
}

/**
 * @brief 创建一颗二叉树
 * @param treeData 二叉树结点数据容器，右值引用
 * @param treeRoot 树根结点，指针引用
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	
	// 空容器或首节点为空，当作空树处理
	if (treeData.empty() || !treeData[0])
	{
		// 释放容器内的堆内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		return;
	}
		
	treeRoot = treeData[0];
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

				if (treeRoot->left) tempQue.push(treeRoot->left);
				if (treeRoot->right) tempQue.push(treeRoot->right);
			}
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

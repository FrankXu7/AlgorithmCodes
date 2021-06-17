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
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	/** 父节点主要用于打印的时候标名关系，算法本身并不需要 */
	TreeNode<T>* dad;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define N(value) (new TreeNode<int>(value))

void TraverseBinaryTree_DLR_Recursion(TreeNode<int>* treeRoot, vector<TreeNode<int>*>& resultArr)
{
	if (!treeRoot) return;

	// 根
	resultArr.push_back(treeRoot);
	// 左
	if (treeRoot->left)
		TraverseBinaryTree_DLR_Recursion(treeRoot->left, resultArr);
	// 右
	if (treeRoot->right)
		TraverseBinaryTree_DLR_Recursion(treeRoot->right, resultArr);
}

void TraverseBinaryTree_DLR_Stack(TreeNode<int>* treeRoot, vector<TreeNode<int>*>& resultArr)
{
	stack<TreeNode<int>*> tempStack({ treeRoot });
	TreeNode<int>* node = nullptr;
	while (!tempStack.empty())
	{
		node = tempStack.top();
		tempStack.pop();

		resultArr.push_back(node);

		// 先入栈右孩子，再入栈左孩子，出栈时就是前序遍历的根左右了
		if (node && node->right)
			tempStack.push(node->right);
		if (node && node->left)
			tempStack.push(node->left);
	}
}

/**
 * @brief 依据数组创建一颗二叉树
 * @param treeData 数据容器，右值引用
 */
TreeNode<int>* CreateTree(vector<TreeNode<int>*>&& treeData)
{
	unsigned int dataSize = treeData.size();

	// 空容器或容器首节点为空指针，都当作空树处理
	if (dataSize == 0 || !treeData[0])
	{
		// 释放右值引用的内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		return nullptr;
	}

	TreeNode<int>* head = treeData[0];

	TreeNode<int>* node = nullptr;
	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];

		if (++n < dataSize && treeData[n] && node)
		{
			node->left = treeData[n];
			node->left->dad = node;
		}

		if (++n < dataSize && treeData[n] && node)
		{
			node->right = treeData[n];
			node->right->dad = node;
		}
	}

	return head;
}

/**
 * @brief 释放一颗二叉树内存
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
 * @brief 打印一颗二叉树，BFS遍历
 * @param treeRoot 树根节点，常量指针
 */
void PrintTree(const TreeNode<int>* treeRoot)
{
	if (!treeRoot)
	{
		cout << "It's an empty tree!\n";
		return;
	}

	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	unsigned int layerCount = 0;

	while (!printQue.empty())
	{
		cout << '[' << ++layerCount << "]  ";

		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();

			if (treeRoot)
			{
				(treeRoot->dad) ? cout << treeRoot->data << '(' << treeRoot->dad->data << "), " :
					cout << treeRoot->data << "(null), ";
			}
			else
				cout << "null, ";

			if (treeRoot && (treeRoot->left || treeRoot->right))
			{
				tempQue.push(treeRoot->left);
				tempQue.push(treeRoot->right);
			}
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	TreeNode<int>* treeRoot = CreateTree({
		N(4),
		N(2), N(6),
		N(1), N(3), N(5), N(7) });

	cout << "The tree: \n";
	PrintTree(treeRoot);

	vector<TreeNode<int>*> resultArr;
	TraverseBinaryTree_DLR_Recursion(treeRoot, resultArr);
	cout << "\n[Recursion] DLR Traverse array: \n";
	for (vector<TreeNode<int>*>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";
	cout << endl;

	resultArr.clear();
	TraverseBinaryTree_DLR_Stack(treeRoot, resultArr);
	cout << "\n[Stack] DLR Traverse array: \n";
	for (vector<TreeNode<int>*>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";
	cout << endl;

	DeleteTree(treeRoot);

	return 0;
}
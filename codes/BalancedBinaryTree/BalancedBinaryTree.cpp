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
#include <chrono>
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

#define NODE(Value) (new TreeNode<int>(Value))

bool BalancedBinaryTree_UpDown()
{
	return true;
}

bool BalancedBinaryTree_DownUp()
{
	return true;
}

/**
 * @brief 创建一颗二叉树，非BST或AVL树
 * @param treeData 二叉树构建数据，右值引用
 * @param treeRoot 作为最终生成的树的根节点
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	TreeNode<int>* node = nullptr;
	unsigned int dataSize = treeData.size();
	
	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];
		if (++n < dataSize)
		{
			node->left = treeData[n];
			node->left->dad = node;
		}
		if (++n < dataSize)
		{
			node->right = treeData[n];
			node->right->dad = node;
		}
	}
}

/**
 * @brief 计算给定二叉树的最大深度
 * @param treeRoot 树根节点，常量指针，不可改变指向内容
 * @return 返回深度
 */
int GetTreeDepth(const TreeNode<int>* treeRoot) {
	queue<const TreeNode<int>*> tempQue({ treeRoot });
	int depth = 1;
	// BFS遍历，每一层的元素统计，默认根节点为第一层，且只有一个节点 
	unsigned int nodeCount = tempQue.size();

	const TreeNode<int>* node = nullptr;
	while (!tempQue.empty())
	{
		node = tempQue.front();
		tempQue.pop();
		--nodeCount;
		
		if (node->left) tempQue.push(node->left);
		if (node->right) tempQue.push(node->right);

		if (nodeCount == 0)
		{
			++depth;
			nodeCount = tempQue.size();
		}
	}

	return depth;
}

/**
 * @brief 删除一颗二叉树
 * @param treeRoot 树根节点，指针引用，删除后会置nullptr
 */
void DeleteTree(TreeNode<int>*& treeRoot)
{
	queue<TreeNode<int>*> delQue({ treeRoot });

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
 * @brief 打印一棵二叉树
 * @param treeRoot 树根节点，常量指针，不可更改指向内容
 */
void PrintTree(const TreeNode<int>* treeRoot) 
{
	queue<const TreeNode<int>*>	printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	
	while (!printQue.empty())
	{
		cout << "Layer: ";
		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();

			if (treeRoot)
			{
				cout << treeRoot->data;
				if (treeRoot->dad)
					cout << '(' << treeRoot->dad->data << "), ";
				else 
					cout << "(null), ";

				if (treeRoot->left)
					tempQue.push(treeRoot->left);
				if (treeRoot->right)
					tempQue.push(treeRoot->right);
			}
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	chrono::system_clock::time_point start = chrono::system_clock::now();

	TreeNode<int>* root = nullptr;
	CreateTree({
		NODE(1), NODE(2), NODE(3), NODE(4), NODE(5),
		NODE(6), NODE(7), NODE(8), NODE(9), NODE(10),
		}, root);
	PrintTree(root);

	cout << (BalancedBinaryTree_UpDown() ? "\nIt's a AVL tree!\n" : "\nNot AVL Tree!\n");
	cout << (BalancedBinaryTree_DownUp() ? "\nIt's a AVL tree!\n" : "\nNot AVL Tree!\n");

	DeleteTree(root);
	
	cout << "\nExecute Time(milliseconds): " 
		<< chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count()
		<< endl;

	return 0;
}

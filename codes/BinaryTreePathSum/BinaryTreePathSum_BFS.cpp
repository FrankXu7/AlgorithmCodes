/**************************************************************************************************
 * 【题目描述】
 * 给定一个目标整数，在一颗二叉树中，判断是否存在一条路径上所有节点值之和等于该目标整数的路径。
 * 二叉树一条路径定义为从根节点到叶节点的一条分支。
 *
 * 【输入】
 * 一颗二叉树 treeRoot
 * 目标整数 targetNum
 *
 * 【输出】
 * 是否存在题中所要求的路径
 *
 * 【解题思路】
 * 可以发现规律：在二叉树中，从树根结点到某节点的路径一定是唯一的。
 * 考虑用两个队列，一个存结点，一个存路径上结点之和，大致过程如下：
 * （1）出队一个结点，同时出队一个值，这个值就是从树根结点到出队的结点的路径上结点之和，
 *		如果这个出队结点是叶节点，且对应的值等于目标值，即得出最终结果，可直接截断返回；
 * （2）否则，将出队结点的左右子结点入队，将结点的值入队时，需要加上出队结点的值之后，再入队，
 *		这样就相当于逐层计算了每层的每个结点，从树根结点到当前结点路径上节点之和；
 *
 * @author FrankX
 * @date 2021-05-25
 **************************************************************************************************/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode<int>* dad;
	TreeNode<int>* left;
	TreeNode<int>* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define NODE(value) (new TreeNode<int>(value))

bool BinaryTreePathSum_BFS(const TreeNode<int>* treeRoot, int& targetNum)
{
	if (!treeRoot) return false;

	queue<const TreeNode<int>*> nodeQue({ treeRoot });
	queue<int> valueQue({ treeRoot->data });
	int curValue = 0;

	while (!nodeQue.empty())
	{
		treeRoot = nodeQue.front();
		nodeQue.pop();
		curValue = valueQue.front();
		valueQue.pop();

		// 当前结点为叶节点，且计算的值等于目标值，即找到了一条路径符合要求 
		if (!treeRoot->left && !treeRoot->right && curValue == targetNum)
		{
			return true;
		} 
		else if (treeRoot->left)
		{
			nodeQue.push(treeRoot->left);
			valueQue.push(treeRoot->left->data + curValue);
		} 
		else if (treeRoot->right)
		{
			nodeQue.push(treeRoot->right);
			valueQue.push(treeRoot->right->data + curValue);
		}
	}

	return false;
}

/**
 * @brief 依据数组构建一颗二叉树，不一定是BST树或AVL树
 * @param treeData 树结点数组，右值引用
 * @param treeRoot 树根结点，指针引用
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	// 空容器或首元素为空，认为是空树
	if (treeData.empty() || !treeData[0])
	{
		// 释放容器剩余堆内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[0];
		return;
	}

	treeRoot = treeData[0];
	TreeNode<int>* node = nullptr;
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
 * @brief 释放一颗二叉树的堆内存
 * @param treeRoot 树根结点，指针引用，释放后会置nullptr
 */
void DeleteTree(TreeNode<int>*& treeRoot)
{
	if (!treeRoot) return;

	queue<TreeNode<int>*> que({ treeRoot });
	TreeNode<int>* node = nullptr;

	while (!que.empty()) 
	{
		node = que.front();
		que.pop();

		if (node->left)
			que.push(node->left);
		if (node->right)
			que.push(node->right);

		delete node;
	}

	treeRoot = nullptr;
}

/**
 * @brief 按照BFS遍历打印一颗二叉树结点
 * @param treeRoot 树根节点，常量指针
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
		NODE(11), nullptr, NODE(13), NODE(99),
		NODE(7), NODE(2), nullptr,  nullptr, nullptr, nullptr, nullptr, NODE(1),
	}, root);

	PrintTree(root);
	
	int targetNum = 0;
	cout << "Input target number:\n";
	cin >> targetNum;
	cout << "\nHas any path node value sum equal the target number?\n";
	cout << (BinaryTreePathSum_BFS(root, targetNum) ? "true" : "false") << endl << endl;

	DeleteTree(root);

	return 0;
}


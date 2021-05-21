/**************************************************************************************************
 * 【题目描述】
 * 判断一颗给定的二叉树是否为平衡二叉树。
 * 这里需要特别注意的是，平常大家说的平衡二叉树，即为AVL树，其必定为BST树；
 * 但【本题中】的平衡二叉树的定义并不包含BST树。
 * 
 * 本题应该意在二叉树的平衡判断上，不考虑是否为BST树，也算是简化了算法。
 *
 * 【输入】
 * 一颗AVL树，不一定是BST树；
 *
 * 【输出】
 * 是否为平衡二叉树；
 *
 * 【解题思路】
 * 方法一：
 * 自顶向下法，即从树根节点开始，计算其左右子树最大高度差，递归计算到叶节点。
 * 使用BFS遍历树的结点并使用队列结构，依次计算出队结点左右子树高度差，
 * 在这之前，还需要实现给定一个树结点，返回该树最大深度的接口。
 * 
 * 方法二：
 * 在方法一中，时间复杂度是 O(n^2)，且节点深度越大，节点深度重复计算的次数越多。
 * 考虑自底向上的方法，判断结点左右子树深度高度差，其遍历的顺序符合二叉树的【后序遍历】。大致过程为：
 * （1）从叶子结点开始，计算左右子树的深度差；
 * （2）深度差绝对值大于1，则返回-1标识当前节点不平衡；
 * （3）反之节点平衡，则比较左右子树深度，取更大值，即为当前节点子树最大深度，
 *		此时注意，需要将得到的最大深度+1后返回，即为当前节点父节点子树的最大深度，
 *		这样每个节点只计算了一次，时间复杂度将得到很大优化。
 *
 * @author FrankX 
 * @date 2021-05-21
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

int GetTreeDepth(const TreeNode<int>* treeRoot);
bool BalancedBinaryTree_1(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> que({ treeRoot });
	int leftDepth = 0;
	int rightDepth = 0;

	while (!que.empty())
	{
		treeRoot = que.front();
		que.pop();

		if (treeRoot->left)
		{
			leftDepth = GetTreeDepth(treeRoot->left);
			que.push(treeRoot->left);
		}
		else leftDepth = 0;

		if (treeRoot->right)
		{
			rightDepth = GetTreeDepth(treeRoot->right);
			que.push(treeRoot->right);
		}
		else rightDepth = 0;
		
		if (abs(leftDepth - rightDepth) > 1) return false;
	}

	return true;
}

int BalancedBinaryTree_2(const TreeNode<int>* treeRoot)
{
	if (!treeRoot) return 0;

	int leftDepth = BalancedBinaryTree_2(treeRoot->left);
	int rightDepth = BalancedBinaryTree_2(treeRoot->right);

	if (leftDepth == -1 || rightDepth == -1 || abs(leftDepth - rightDepth) > 1)
	{
		return -1;
	}
	else
	{
		// 返回当前节点的子树最大深度，+1是当前节点的父节点的子树最大深度
		return (max(leftDepth, rightDepth) + 1);
	}
}

/**
 * @brief 创建一颗二叉树，非BST或AVL树
 * @param treeData 二叉树构建数据，右值引用
 * @param treeRoot 作为最终生成的树的根节点
 */
void CreateTree(vector<TreeNode<int>*>& treeData, TreeNode<int>*& treeRoot)
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
			if (node->left)
				node->left->dad = node;
		}
		if (++n < dataSize)
		{
			node->right = treeData[n];
			if (node->right)
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
	if (!treeRoot) return 0;

	queue<const TreeNode<int>*> tempQue({ treeRoot });
	int depth = 0;
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
	TreeNode<int>* root = nullptr;

	chrono::system_clock::time_point start = chrono::system_clock::now();
	vector<TreeNode<int>*> treeData;
	for (int idx = 0; idx < 10000; ++idx) treeData.push_back(NODE(idx + 1));
	CreateTree(treeData, root);
	chrono::system_clock::time_point end = chrono::system_clock::now();
	cout << "[Create milliseconds]  "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl << endl;

	//PrintTree(root);

	start = end;
	cout << (BalancedBinaryTree_1(root) ? "\nIt's a AVL tree!\n" : "\nNot AVL Tree!\n");
	end = chrono::system_clock::now();
	cout << "[Solution_1 exec milliseconds]  " 
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	start = end;
	cout << (BalancedBinaryTree_2(root) >= 0 ? "\nIt's a AVL tree!\n" : "\nNot AVL Tree!\n");
	cout << "[Solution_2 exec milliseconds]  " 
		<< chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() << endl;

	DeleteTree(root);
	
	cout << endl;
	return 0;
}

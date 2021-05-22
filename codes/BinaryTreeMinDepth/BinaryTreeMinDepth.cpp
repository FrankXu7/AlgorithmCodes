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
 * 最小深度即为根节点到最近的叶子节点的最小路径。
 * 考虑采用自底向上的方式计算深度，遍历为后续遍历，大致过程为：
 * （1）后续遍历，从叶子节点往上遍历到根节点，叶子节点返回深度为0；
 * （2）当前节点左右子树的最小深度，在+1后，即为当前节点父节点的子树最小深度；
 * （3）每层递归返回的都是子树的最小深度，到根节点时，即为二叉树的最小深度；
 * 
 * @author FrankX
 * @date 2021-05-22
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

#define NODE(Value) (new TreeNode<int>(Value))

unsigned int BinaryTreeMinDepth(const TreeNode<int>* treeRoot)
{
	if (!treeRoot) return 0;

	unsigned int leftDepth = BinaryTreeMinDepth(treeRoot->left);
	unsigned int rightDepth = BinaryTreeMinDepth(treeRoot->right);

	// 当前节点的子树最小深度，+1后即为当前节点父节点的子树最小深度 
	return (min(leftDepth, rightDepth) + 1);
}

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
			// 容器前X个元素为nullptr, n跟随idx增加 
			++n;
			continue;
		}

		// 防止treeData首元素为nullptr，你永远不知道用户会对你的程序干什么...
		if (!treeRoot) treeRoot = node;

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

void DeleteTree(TreeNode<int>*& treeRoot)
{
	if (!treeRoot) return;
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

void PrintTree(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	int layer = 0;

	while (!printQue.empty())
	{
		cout << '[' << ++layer << "]  ";
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
		nullptr,
		NODE(1), NODE (2), NODE(3),NODE(4), NODE(5), 
		NODE(6), NODE(7), NODE(8), NODE(9), NODE(10),
		NODE(11), NODE(12), nullptr, nullptr, nullptr,
		NODE(13), NODE(14), NODE(15), nullptr, nullptr,
		NODE(16)
	}, root);

	PrintTree(root);

	cout << "\nThe Mininum binary tree depth: " << BinaryTreeMinDepth(root) << endl;

	DeleteTree(root);

	cout << endl;
	return 0;
}

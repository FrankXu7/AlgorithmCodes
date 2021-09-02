/**************************************************************************************************
 * 【题目描述】
 * 反转一颗二叉树节点
 *
 * 【输入】
 * Before Invert:
 *       1,
 *   2,       3
 * 4, null, 5, 6
 * 
 * 【输出】
 * After Invert:
 *       1,
 *   3,       2
 * 6, 5, null, 4
 *
 *
 * 【解题思路】
 * BST搜索法：
 * 反转一颗二叉树，实际上相当于交换每个二叉树节点的左右孩子节点，通过简单的BST搜索，将遍历的节点推入到
 * 一个队列中，然后依次将节点出队，并交换节点的左右孩子节点。
 * 
 * 递归法：
 * 同样是交换节点的左右孩子节点，交换完当前节点的左右孩子节点后，
 * 继续将当前节点的不为空的左右孩子作为根节点，继续进行递归交换。
 * 
 * 【解题分析】
 * BST搜索法：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N) 最多存储某一层的叶子节点，完全二叉树最后一层叶子节点数量为 2N+1
 * 
 * 递归搜索法：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N) 递归调用的层数，也即二叉树的层数 logN，最差的情况下，二叉树退化为链表，层数为 N
 *
 * @author FrankX
 * @date 2021-09-02
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

/** 二叉树节点数据结构 */
template<typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* dad; // 用于打印时表现树的结构，不参与算法逻辑 
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define N(val, T) (new TreeNode<T>(val))

/** BST搜索法 */
template<typename T>
void InvertBinaryTree_BST(TreeNode<T>* root)
{
	deque<TreeNode<T>*> que{ root };

	while (!que.empty())
	{
		root = que.front();
		que.pop_front();

		if (root->left && !root->right)
		{
			root->right = root->left;
			root->left = nullptr;

			que.emplace_back(root->right);
		}
		else if (!root->left && root->right)
		{
			root->left = root->right;
			root->right = nullptr;

			que.emplace_back(root->left);
		}
		else if (root->left && root->right)
		{
			TreeNode<T>* node = root->left;
			root->left = root->right;
			root->right = node;

			que.emplace_back(root->left);
			que.emplace_back(root->right);
		}
	}
}

/** 递归搜索法 */
template<typename T>
void InvertBinaryTree_Recursion(TreeNode<T>*& root)
{
	if (!root) return;

	if (root->left && !root->right)
	{
		root->right = root->left;
		root->left = nullptr;

		InvertBinaryTree_Recursion(root->right);
	}
	else if (!root->left && !root->right)
	{
		root->left = root->right;
		root->right = root->left;

		InvertBinaryTree_Recursion(root->left);
	}
	else if (root->left && root->right)
	{
		TreeNode<T>* node = root->left;
		root->left = root->right;
		root->right = node;

		InvertBinaryTree_Recursion(root->left);
		InvertBinaryTree_Recursion(root->right);
	}
}

/**
 * @brief 依据一个数组构建一个二叉树，未必是平衡树和排序树
 * @param treeData 二叉树节点数组，右值引用
 * @param root 二叉树根节点，指针引用
 */
template<typename T_Node, typename T_Data>
void CreateTree(vector<T_Node>&& treeData, TreeNode<T_Data>*& root)
{
	// 数组首节点为空，认为是空树 
	if (!treeData[0]) return;
	root = treeData[0];

	unsigned int dataSize = treeData.size();
	unsigned int n = 0, idx = 0;
	TreeNode<T_Data>* node = nullptr;

	// n 肯定比 idx 增加更快，所以只判断 n 就行 
	while (n < dataSize)
	{
		node = treeData[idx++];
		if (!node) continue;

		if (++n < dataSize && treeData[n])
		{
			node->left = treeData[n];
			treeData[n]->dad = node;
		}
		if (++n < dataSize && treeData[n])
		{
			node->right = treeData[n];
			treeData[n]->dad = node;
		}
	}
}

/**
 * @brief 释放二叉树内存
 * @param 二叉树根节点，指针引用，释放后置空
 */
template<typename T>
void DeleteTree(TreeNode<T>*& root)
{
	deque<TreeNode<T>*> treeData{ root };

	while (!treeData.empty())
	{
		root = treeData.front();
		treeData.pop_front();

		if (root->left) treeData.emplace_back(root->left);
		if (root->right) treeData.emplace_back(root->right);

		delete root;
	}

	root = nullptr;
}

/**
 * @brief 打印一颗二叉树，按BST顺序分行打印
 * @param root 二叉树根节点，常量指针
 */
template<typename T>
void PrintTree(const TreeNode<T>* root)
{
	deque<const TreeNode<T>*> printQue{ root };
	deque<const TreeNode<T>*> tempQue;

	const TreeNode<T>* node = nullptr;

	do
	{
		while (!printQue.empty())
		{
			node = printQue.front();
			printQue.pop_front();

			if (node)
			{
				cout << node->data;
				if (node->dad)
				{
					// 因为算法是需要反转二叉树，所以要表示节点是左或右孩子节点 
					(node->dad->left == node) ?
						cout << '(' << node->dad->data << " L), " :
						cout << '(' << node->dad->data << " R), ";
				}
				else
					cout << "(null), "; // 只有根节点会走到此分支 

				if (node->left)
					tempQue.emplace_back(node->left);
				if (node->right)
					tempQue.emplace_back(node->right);
			}
		}

		cout << endl;
		printQue.swap(tempQue);

	} while (!printQue.empty());
}

int main(int argc, char* argv[])
{
	TreeNode<int>* root = nullptr;

	CreateTree<TreeNode<int>*, int>({
		N(1, int),
		N(2, int), N(3, int),
		N(4, int), nullptr,   N(5, int), N(6, int),
		N(7, int), N(8, int), N(9, int), nullptr,   N(10, int), N(11, int)
		}, root);

	cout << "Tree Before Invert:\n";
	PrintTree<int>(root);

	// BST搜索法 
	InvertBinaryTree_BST(root);
	// 递归法 
	// InvertBinaryTree_Recursion(root);

	cout << "\nTree After Invert:\n";
	PrintTree<int>(root);

	DeleteTree(root);

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 判断一颗给定的二叉树是否对称，即分支结构相同，对应节点的值相等
 *
 * 【输入】
 * 一颗二叉树
 * 【输出】
 * 返回判断结果
 *
 * 【解题思路】
 * 首先，需要特别注意，给定的二叉树并没有说是平衡二叉树
 * 考虑一颗对称的树，根节点的左右子树肯定是相同的，所以采用两个栈，前序遍历树节点
 * （1）若两颗子树为空树，当成是对称的；
 * （2）若两颗子树仅有一颗是空树，肯定不对称；
 * （3）两颗子树对应位置的节点非空，但值不同，也是不对称的；
 *
 * @author FrankX
 * @date 2021-05-08
 **************************************************************************************************/
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		left = right = nullptr;
	}
};

#define NODE(data) (new TreeNode<int>(data))

bool TheSymmetricBinaryTree(TreeNode<int>* tree)
{
	if (tree == nullptr) return true;

	TreeNode<int>* treeL = tree->left;
	TreeNode<int>* treeR = tree->right;

	stack<TreeNode<int>*> stackL({ treeL });
	stack<TreeNode<int>*> stackR({ treeR });

	while (!stackL.empty() || !stackR.empty())
	{
		if (!stackL.empty()) stackL.pop();
		if (!stackR.empty()) stackR.pop();

		if (treeL == nullptr && treeR == nullptr);
		else if ((treeL == nullptr || treeR == nullptr) ||
				 treeL->data != treeR->data)
		{
			return false;
		}

		/**
		 * 这里需要注意，只有左右子节点都不为空，才需要入栈；
		 * 因为左右子节点都为空，表示遍历到叶子节点了，不需要继续遍历了；
		 */
		if (treeL != nullptr && 
			(treeL->right != nullptr || treeL->left != nullptr))
		{
			stackL.push(treeL->right);
			stackL.push(treeL->left);
		}
		if (treeR != nullptr && 
			(treeR->right != nullptr || treeR->left != nullptr))
		{
			stackR.push(treeR->right);
			stackR.push(treeR->left);
		}

		treeL = stackL.empty() ? nullptr : stackL.top();
		treeR = stackR.empty() ? nullptr : stackR.top();
	}

	return true;
}

/**
 * @brief 利用传入的vector数据生成一颗二叉树，非搜索树，非平衡树
 * @param treeData 树的原始数据
 * @param treeRoot 完成后的树根节点
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	unsigned int dataSize = treeData.size();

	// n 的增加必定快于 idx，故边界判断用 n 即可 
	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		if (treeData[idx] == nullptr) continue;

		if (++n < dataSize)
			treeData[idx]->left = treeData[n];
		if (++n < dataSize)
			treeData[idx]->right = treeData[n];
	}
}

/**
* @brief 释放一颗二叉树内存
* @param treeRoot 树的根节点
*/
void DeleteTree(TreeNode<int>*& treeRoot)
{
	queue<TreeNode<int>*> delQue({ treeRoot });
	TreeNode<int>* node = nullptr;
	while (!delQue.empty())
	{
		node = delQue.front();
		delQue.pop();
		if (node && (node->left || node->right))
		{
			delQue.push(node->left);
			delQue.push(node->right);
		}
		delete node;
	}
	treeRoot = nullptr;
}

/**
* @brief 打印一颗二叉树
* @brief treeRoot 树的根节点
*/
void PrintTree(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	const TreeNode<int>* node = nullptr;
	while (!printQue.empty())
	{
		while (!printQue.empty())
		{
			node = printQue.front();
			printQue.pop();
			if (node) cout << node->data << ", ";
			else cout << "null, ";

			if (node && (node->left || node->right))
			{
				tempQue.push(node->left);
				tempQue.push(node->right);
			}
		}
		printQue.swap(tempQue);
		cout << endl;
	}
}

int main()
{
	TreeNode<int>* tree = nullptr;
	CreateTree({NODE(4),
		NODE(1), NODE(1),
		NODE(3), NODE(6), NODE(3), NODE(0),
		}, tree);

	cout << "Tree:\n";
	PrintTree(tree);

	cout << "\nThe Symmetric Binary Tree?\n" << (TheSymmetricBinaryTree(tree) ? "YES" : "NO") << endl;

	DeleteTree(tree);

	return 0;
}
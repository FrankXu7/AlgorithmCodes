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

int main()
{
	// 应该依据数据构造平衡二叉树，这里直接手写两棵树 
	TreeNode<int>* tree1 = new TreeNode<int>(4);
	tree1->left = new TreeNode<int>(2);
	tree1->left->left = new TreeNode<int>(1);
	tree1->left->right = new TreeNode<int>(3);
	tree1->right = new TreeNode<int>(2);
	tree1->right->left = new TreeNode<int>(1);
	tree1->right->right = new TreeNode<int>(3);
	tree1->right->right->left = new TreeNode<int>(9);

	cout << (TheSymmetricBinaryTree(tree1) ? "Symmetric" : "NOT Symmetric") << endl;

	return 0;
}
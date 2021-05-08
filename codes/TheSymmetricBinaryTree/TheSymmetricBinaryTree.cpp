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

	while (treeL && treeR)
	{

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
	tree1->right = new TreeNode<int>(6);
	tree1->right->left = new TreeNode<int>(5);
	tree1->right->right = new TreeNode<int>(7);

	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 判断两颗给定的二叉树是否相同，即结构相同，对应节点的值也相同。
 *
 * 【输入】
 * 两颗二叉树
 * 【输出】
 * 判断两颗二叉树结构与节点对应值是否相同
 *
 * 【解题思路】
 * 使用深度优先算法，考虑到树的高度对递归的性能会有较大影响，故使用栈来实现非递归的DFS：
 *
 * @author FrankX
 * @date 2021-04-30
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode* left;
	TreeNode* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		left = right = nullptr;
	}
};

bool TheSameBinaryTree_DFS_Stack(TreeNode<int>* tree1, TreeNode<int>* tree2)
{
	return false;
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
	TreeNode<int>* tree2 = new TreeNode<int>(4);
	tree2->left = new TreeNode<int>(2);
	tree2->left->left = new TreeNode<int>(1);
	tree2->left->right = new TreeNode<int>(3);
	tree2->right = new TreeNode<int>(6);
	tree2->right->left = new TreeNode<int>(5);
	tree2->right->right = new TreeNode<int>(7);

	cout << (TheSameBinaryTree_DFS_Stack(tree1, tree2) ? "TRUE" : "FALSE") << endl;

	return 0;
}

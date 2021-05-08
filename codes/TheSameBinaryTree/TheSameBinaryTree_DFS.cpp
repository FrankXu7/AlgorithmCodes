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
 * 首先需要特别注意的是，给定的二叉树不一定是平衡二叉树；
 * 使用深度优先算法，采用递归来实现：
 * （1）两棵树是空二叉树，自然是相同的；
 * （2）若其中一颗为空二叉树，另一颗非空，则二叉树不相同；
 * （3）都是非空二叉树但节点的值不同，则二叉树不相同；
 * （4）递归重复（1）（2）（3）步骤，直到叶子节点为止；
 * 注意点：左右分支没有值时，指针需要设置为nullptr，否则判断为非空，指针不初始化的话可能为任意值。
 *
 * @author FrankX
 * @date 2021-04-30
 **************************************************************************************************/
#include <iostream>
#include <vector>

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

bool TheSameBinaryTree_DFS(TreeNode<int>* tree1, TreeNode<int>* tree2)
{
	if (tree1 == nullptr && tree2 == nullptr)
	{
		return true;
	}
	else if ((tree1 == nullptr || tree2 == nullptr) || 
			 tree1->data != tree2->data)
	{
		return false;
	}
	else
	{
		return (TheSameBinaryTree_DFS(tree1->left, tree2->left) && 
				TheSameBinaryTree_DFS(tree1->right, tree2->right));
	}
}

int main()
{
	// 应该依据数据构造二叉树，这里直接手写两棵树 
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

	cout << (TheSameBinaryTree_DFS(tree1, tree2) ? "TRUE" : "FALSE") << endl;

	return 0;
}

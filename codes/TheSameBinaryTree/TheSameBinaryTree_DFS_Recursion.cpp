#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode* left;
	TreeNode* right;

};

bool TheSameBinaryTree_DFS_Recursion(TreeNode<int>* tree1, TreeNode<int>* tree2)
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
		return (TheSameBinaryTree_DFS_Recursion(tree1->left, tree2->left) && 
			TheSameBinaryTree_DFS_Recursion(tree1->right, tree2->right));
	}
}

int main()
{
	// 应该依据数据构造平衡二叉树，这里直接手写两棵树
	TreeNode<int>* tree1 = new TreeNode<int>;
	tree1->data = 2;
	tree1->left = new TreeNode<int>;
	tree1->left->data = 1;
	tree1->left->left = nullptr;
	tree1->right = new TreeNode<int>;
	TreeNode<int>* tree2 = new TreeNode<int>;
	tree2

	return 0;
}

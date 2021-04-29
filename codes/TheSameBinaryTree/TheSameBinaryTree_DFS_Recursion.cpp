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

	cout << (TheSameBinaryTree_DFS_Recursion(tree1, tree2) ? "TRUE" : "FALSE") << endl;

	return 0;
}

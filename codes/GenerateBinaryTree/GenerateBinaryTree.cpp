#include <iostream>
#include <stack>
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

TreeNode<int>* GenerateBinaryTree(vector<TreeNode<int>*>& treeData, int leftIdx, int rightIdx)
{

}

void DeleteTree(TreeNode<int>*& treeRoot)
{
	if (treeRoot == nullptr) return;

	queue<TreeNode<int>*> delQue({ treeRoot });
	
	while (!delQue.empty())
	{
		treeRoot = delQue.front();
		delQue.pop();
		if (treeRoot->left) delQue.push(treeRoot->left);
		if (treeRoot->right) delQue.push(treeRoot->right);

		delete treeRoot;
	}

	treeRoot = nullptr;
}

void PrintTree(const TreeNode<int>* treeRoot)
{

}

int main()
{

	return 0;
}

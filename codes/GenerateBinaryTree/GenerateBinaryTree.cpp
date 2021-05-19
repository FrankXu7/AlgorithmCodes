#include <iostream>
#include <stack>
#include <queue>
#include <vector>

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

#define NODE(Value) (new TreeNode<int>(Value))

TreeNode<int>* GenerateBinaryTree(vector<TreeNode<int>*>& treeData, int leftIdx, int rightIdx)
{
	if (leftIdx > rightIdx) return nullptr;

	int midIdx = (leftIdx + rightIdx) / 2;
	TreeNode<int>* root = treeData[midIdx];
	root->left = GenerateBinaryTree(treeData, leftIdx, midIdx - 1);
	root->right = GenerateBinaryTree(treeData, midIdx + 1, rightIdx);

	return root;
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
	vector<TreeNode<int>*> treeData = {
		NODE(1), NODE(2), NODE(3), NODE(4), NODE(5), 
		NODE(6), NODE(7), NODE(8), NODE(9), NODE(10), 
		NODE(11), NODE(12),
	};

	TreeNode<int>* root = GenerateBinaryTree(treeData, 0, treeData.size() - 1);

	DeleteTree(root);

	return 0;
}

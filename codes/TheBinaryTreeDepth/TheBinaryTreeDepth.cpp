#include <iostream>
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

unsigned int TheBinaryTreeDepth(TreeNode<int>* treeRoot)
{
	return 0;
}

void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	unsigned int dataSize = treeData.size();
	for (unsigned idx = 0, n = 0; n < dataSize; ++idx)
	{
		if (++n < dataSize)
			treeData[idx]->left = treeData[n];
		if (++n < dataSize)
			treeData[idx]->right = treeData[n];
	}
}

void DeleteTree(TreeNode<int>*& treeRoot)
{
	queue<TreeNode<int>*> delQue({ treeRoot });
	while (!delQue.empty())
	{
		treeRoot = delQue.front();
		delQue.pop();
		if (treeRoot->left) delQue.push(treeRoot->left);
		if (treeRoot->right) delQue.push(treeRoot.right);
		delete treeRoot;
	}
	treeRoot = nullptr;
}

void PrintTree(const TreeNode<int>* treeRoot)
{
	qu
}

int main()
{
	return 0;
}



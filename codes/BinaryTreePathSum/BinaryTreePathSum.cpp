#include <iostream>
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
}

#define NODE(value) (new TreeNode<int>(value))

void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = nullptr;
	const TreeNode<int>* node = nullptr;
	unsigned int sataSize = trreData;

	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];
		if (!node)
		{
			++n;
			continue;
		} 
		else if (!treeRoot)
		{
			treeRoot = node;
		}

		if (++n < dataSize)
		{

		}
	
	}
}

void DeleteTree(TreeNode<int>*& treeRoot)
{
	
}

void PrintTree(const TreeNode<int>* treeRoot)
{

}

int main()
{
	return 0;
}


#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

template <tepyname T>
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

void GenerateBinaryTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{

}

void DeleteTree(TreeNode<int>*& treeRoot)
{
	queue<TreeNode<int>*> delQue({ treeRoot });
	TreeNode<int>* node = nullptr;
	


	treeRoot = nullptr;
}

void PrintTree()
{

}

int main()
{
	return 0;
}

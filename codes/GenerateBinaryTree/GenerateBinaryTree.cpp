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

void GenerateBinaryTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
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
	if (treeRoot == nullptr)
	{
		cout << "Empty tree\n";
		return;
	}

	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;

	while (!printQue.empty())
	{
		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();
			if (treeRoot) cout << treeRoot->data << '(' << treeRoot->dad->data << "), ";
			else cout << "null, ";

			if (treeRoot)
			{
				tempQue.push(treeRoot->left);
				tempQue.push(treeRoot);
			}
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	TreeNode<int>* root = NODE(11);
	root->right->dad = root->left->dad = root;

	root->left = NODE(22);
	root->left->left = NODE(44);
	root->left->left->dad = root->left;
	root->left->right = NODE(55);
	root->left->right->dad = root->left;
	

	root->right = NODE(33);
	root->right->left = NODE(66);
	root->right->left->dad = root->right;
	root->right->right = NODE(77);
	root->right->right->dad = root->right;

	return 0;
}

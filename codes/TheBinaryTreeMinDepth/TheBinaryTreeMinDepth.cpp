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
};

#define NODE(Value) (new TreeNode<int>(Value))

unsigned int TheBinaryTreeMinDepth(const TreeNode<int>* treeRoot)
{
	if (!treeRoot) return 0;

	unsigned int leftDepth = TheBinaryTreeMinDepth(treeRoot->left);
	unsigned int rightDepth = TheBinaryTreeMaxDepth(treeRoot->right);

	return (min(leftDepth, rightDepth) + 1);
}

void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	TreeNode<int>* node = nullptr;
	unsigned int dataSize = treeData.size();

	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];
		if (node && ++n < dataSize)
		{
			node->left = treeData[n];
			node->left->dad = node;
		}
		if (node && ++n < dataSize)
		{
			node->right = treeData[n];
			node->right->dad = node;
		}
	}
}

void DeleteTree(TreeNode<int>*& treeRoot)
{
	if (!treeRoot) return;
	queue<TreeNode<int>*> delQue({ treeRoot });

	while (!delQue.empty())
	{
		treeRoot = delQue.front();
		delQue.pop();

		if (treeRoot->left)
			delQue.push(treeRoot->left);
		if (treeRoot->right)
			delQue.push(treeRoot->right);

		delete treeRoot;
	}

	treeRoot = nullptr;
}

void PrintTree(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	int layer = 0;

	while (!printQue.empty())
	{
		cout << '[' << ++layer << "]  ";
		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();

			if (treeRoot)
			{
				cout << treeRoot->data;
				if (treeRoot->dad)
					cout << '(' << treeRoot->dad->data << "), ";
				else
					cout << "(null), ";
			}

			if (treeRoot && treeRoot->left)
				tempQue.push(treeRoot->left);
			if (treeRoot && treeRoot->right)
				tempQue.push(treeRoot->right);
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	TreeNode<int>* root = nullptr;
	CreateTree({
		NODE(1), NODE (2), NODE(3),NODE(4), NODE(5), 
		NODE(6), NODE(7), NODE(8), NODE(9), NODE(10),
		NODE(11), NODE(12), NODE(13), NODE(14), NODE(15),
	}, root);

	PrintTree(root);

	DeleteTree(root);

	return 0;
}

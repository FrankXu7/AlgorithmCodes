/**************************************************************************************************
 * 【题目描述】
 * 刷出一句英文中最后一个单词的长度，单词以空格分割。
 *
 * 【输入】
 * string="Hello world"
 * 【输出】
 * lastWorldLen=5
 *
 * 【解题思路】
 * 反序遍历字符串，遇到空格或tab即停止，需要特别注意的是，最后一个单词后，可能还会有空格和tab，需要排除。
 *
 * @author FrankX
 * @date 2021-04-09
 **************************************************************************************************/
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
	unsigned int rightDepth = TheBinaryTreeMinDepth(treeRoot->right);

	return (min(leftDepth, rightDepth) + 1);
}

void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = nullptr;
	TreeNode<int>* node = nullptr;
	unsigned int dataSize = treeData.size();

	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];
		if (!node)
		{
			// 容器前X个元素为nullptr, n跟随idx增加 
			++n;
			continue;
		}

		// 防止treeData首元素为nullptr，你永远不知道用户会对你的程序干什么...
		if (!treeRoot) treeRoot = node;

		if (++n < dataSize)
		{
			node->left = treeData[n];
			if (node->left)
				node->left->dad = node;
		}
		if (++n < dataSize)
		{
			node->right = treeData[n];
			if (node->right)
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
		nullptr,
		NODE(1), NODE (2), NODE(3),NODE(4), NODE(5), 
		NODE(6), NODE(7), NODE(8), NODE(9), NODE(10),
		NODE(11), NODE(12), nullptr, nullptr, nullptr,
		NODE(13), NODE(14), NODE(15), nullptr, nullptr,
		NODE(16)
	}, root);

	PrintTree(root);

	cout << "\nThe Mininum binary tree depth: " << TheBinaryTreeMinDepth(root) << endl;

	DeleteTree(root);

	cout << endl;
	return 0;
}

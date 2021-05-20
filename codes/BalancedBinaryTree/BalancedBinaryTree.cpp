/**************************************************************************************************
 * 【题目描述】
 * 
 *
 * 【输入】
 * 
 *
 * 【输出】
 * 
 *
 * 【解题思路】
 *
 *
 * @author FrankX
 * @date 2021-
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

void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{

}

void DeleteTree(TreeNode<int>*& treeRoot)
{
	
}

void PrintTree(const TreeNode<int>* treeRoot) 
{
	queue<const TreeNode<int>*>	printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	
	while (!printQue.empty())
	{
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

			if (treeRoot->left)
				tempQue.push(treeRoot->left);
			if (treeRoot->right)
				tempQue.push(treeRoot->right);
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	return 0;
}
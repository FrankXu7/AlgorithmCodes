/**************************************************************************************************
 * 【题目描述】
 * 将一个有序数组，转化为一颗平衡二叉树
 *
 * 【输入】
 * sortedArray 一个有序的数组
 * 【输出】
 * 一颗平衡二叉树
 *
 * 【解题思路】
 * 一颗二叉搜索树（BST）的中序遍历即为一个有序数组；因为数组有序，需要高度平衡的话，那根节点肯定是数组中
 * 间的元素，分解步骤：
 * （1）给定有序数组的左右下标，当前树的根节点即为中间下标对应的节点；
 * （2）以中间下标为界，按（1）的方式递归左右的子有序数组；
 * （3）重复上述（1）（2）步骤，直到左下标大于右下标，返回nullptr；
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(logN)，空间复杂度和递归的层级正相关，而树的深度决定了递归的层级，由满二叉树的节点数量N =
 *             (2^H) - 1，可知空间复杂度为O(logN)。
 * 
 * @author FrankX
 * @date 2021-05-20
 **************************************************************************************************/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	// 父节点的作用是为了方便打印的时候看树结构，算法本身并不需要记录父节点指针
	TreeNode<T> *dad;
	TreeNode<T> *left;
	TreeNode<T> *right;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define NODE(Value) (new TreeNode<int>(Value))

TreeNode<int> *GenerateBinaryTree(vector<TreeNode<int> *> &treeData, int leftIdx, int rightIdx)
{
	if (leftIdx > rightIdx)
		return nullptr;

	int midIdx = (leftIdx + rightIdx) / 2;
	TreeNode<int> *root = treeData[midIdx];
	root->left = GenerateBinaryTree(treeData, leftIdx, midIdx - 1);
	root->right = GenerateBinaryTree(treeData, midIdx + 1, rightIdx);

	if (root->left)
		root->left->dad = root;
	if (root->right)
		root->right->dad = root;

	return root;
}

/**
 * @breif 释放树节点内存
 * @param treeRoot 树的根节点，指针引用，释放指向内存后会置nullptr
 */
void DeleteTree(TreeNode<int> *&treeRoot)
{
	if (treeRoot == nullptr)
		return;

	queue<TreeNode<int> *> delQue({treeRoot});

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

/**
 * @brief 打印树，打印的每个值都会显示其父节点值以便观察树结构，根节点的父节点打印为null
 * @param treeRoot 树的根节点常量指针，其指向的内容不允许改变 
 */
void PrintTree(const TreeNode<int> *treeRoot)
{
	queue<const TreeNode<int> *> printQue({treeRoot});
	queue<const TreeNode<int> *> tempQue;

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

				if (treeRoot->left)
					tempQue.push(treeRoot->left);
				if (treeRoot->right)
					tempQue.push(treeRoot->right);
			}
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	vector<TreeNode<int> *> treeData = {
		NODE(1),
		NODE(2),
		NODE(3),
		NODE(4),
		NODE(5),
		NODE(6),
		NODE(7),
		NODE(8),
		NODE(9),
		NODE(10),
		NODE(11),
		NODE(12),
	};

	TreeNode<int> *root = GenerateBinaryTree(treeData, 0, treeData.size() - 1);

	PrintTree(root);

	DeleteTree(root);

	return 0;
}

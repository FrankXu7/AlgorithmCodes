/**************************************************************************************************
 * 【题目描述】
 * 找出一颗二叉树的最小深度。
 *
 * 【输入】
 * 一颗二叉树，不一定是AVL或BST树
 * 【输出】
 * 该二叉树的最小深度
 *
 * 【解题思路】
 * 最小深度即为根节点到最近的叶子节点的最小路径。
 * 考虑采用自底向上的方式计算深度，遍历为后续遍历，大致过程为：
 * （1）后续遍历，从叶子节点往上遍历到根节点，叶子节点返回深度为0；
 * （2）当前节点左右子树的最小深度，在+1后，即为当前节点父节点的子树最小深度；
 * （3）每层递归返回的都是子树的最小深度，到根节点时，即为二叉树的最小深度；
 *
 * @author FrankX
 * @date 2021-05-22
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

#define NODE(value) (new TreeNode<int>(value))

/**
 * @brief 创建一颗二叉树
 * @param treeData 二叉树结点数据容器，右值引用
 * @param treeRoot 树根结点，指针引用
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	// 空容器或首节点为空，当作空树处理，
	if (treeData.empty() || !treeRoot)
	{
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		return;
	}

	queue<TreeNode<int>*> que({ treeData[0] });
	TreeNode<int>* node = nullptr;
	while (!que.empty())
	{
		node = que.front();
		que.pop();



	}

}

/**
 * @brief 释放二叉树内存
 * @param treeRoot 树根节点，指针引用，释放后置nullptr
 */
void DeleteTree(TreeNode<int>*& treeRoot)
{

}

/**
 * @brief 按BFS遍历打印一颗二叉树
 * @param treeRoot 树根节点，常量指针，不可更改指向的数据
 */
void PrintTree(const TreeNode<int>* treeRoot)
{

}

int main()
{
	TreeNode<int>* root = nullptr;
	CreateTree({ nullptr, nullptr, NODE(1), NODE(2), NODE(4) }, root);
	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 判断两颗给定的二叉树是否相同，即结构相同，对应节点的值也相同。
 *
 * 【输入】
 * 两颗二叉树
 * 【输出】
 * 判断两颗二叉树结构与节点对应值是否相同
 *
 * 【解题思路】
 * 首先需要特别注意的是，给定的二叉树不一定是平衡二叉树；
 * 使用深度优先算法，采用递归来实现：
 * （1）两棵树是空二叉树，自然是相同的；
 * （2）若其中一颗为空二叉树，另一颗非空，则二叉树不相同；
 * （3）都是非空二叉树但节点的值不同，则二叉树不相同；
 * （4）递归重复（1）（2）（3）步骤，直到叶子节点为止；
 * 注意点：左右分支没有值时，指针需要设置为nullptr，否则判断为非空，指针不初始化的话可能为任意值。
 *
 * @author FrankX
 * @date 2021-04-30
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode* left;
	TreeNode* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		left = right = nullptr;
	}
};

#define NODE(data) (new TreeNode<int>(data))

bool TheSameBinaryTree_DFS(TreeNode<int>* tree1, TreeNode<int>* tree2)
{
	if (tree1 == nullptr && tree2 == nullptr)
	{
		return true;
	}
	else if ((tree1 == nullptr || tree2 == nullptr) || 
			 tree1->data != tree2->data)
	{
		return false;
	}
	else
	{
		return (TheSameBinaryTree_DFS(tree1->left, tree2->left) && 
				TheSameBinaryTree_DFS(tree1->right, tree2->right));
	}
}

/**
 * @brief 利用传入的vector数据生成一颗二叉树，非搜索树，非平衡树
 * @param treeData 树的原始数据
 * @param treeRoot 完成后的树根节点
 */
void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	unsigned int dataSize = treeData.size();

	// n 的增加必定快于 idx，故边界判断用 n 即可 
	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		if (treeData[idx] == nullptr) continue;

		if (++n < dataSize)
			treeData[idx]->left = treeData[n];
		if (++n < dataSize)
			treeData[idx]->right = treeData[n];
	}
}

/**
* @brief 释放一颗二叉树内存
* @param treeRoot 树的根节点
*/
void DeleteTree(TreeNode<int>*& treeRoot)
{
	queue<TreeNode<int>*> delQue({ treeRoot });
	TreeNode<int>* node = nullptr;
	while (!delQue.empty())
	{
		node = delQue.front();
		delQue.pop();
		if (node && (node->left || node->right))
		{
			delQue.push(node->left);
			delQue.push(node->right);
		}
		delete node;
	}
	treeRoot = nullptr;
}

/**
* @brief 打印一颗二叉树
* @brief treeRoot 树的根节点
*/
void PrintTree(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	const TreeNode<int>* node = nullptr;
	while (!printQue.empty())
	{
		while (!printQue.empty())
		{
			node = printQue.front();
			printQue.pop();
			if (node) cout << node->data << ", ";
			else cout << "null, ";

			if (node && (node->left || node->right))
			{
				tempQue.push(node->left);
				tempQue.push(node->right);
			}
		}
		printQue.swap(tempQue);
		cout << endl;
	}
}

int main()
{
	TreeNode<int>* tree1 = nullptr;
	CreateTree({ NODE(4),
		NODE(2), NODE(6),
		NODE(1), NODE(7), NODE(5), NODE(7),
		NODE(9356), NODE(99),
		}, tree1);
	TreeNode<int>* tree2 = nullptr;
	CreateTree({ NODE(4),
		NODE(2), NODE(6),
		NODE(1), NODE(7), NODE(5), NODE(7),
		NODE(9356), NODE(99), NODE(77)
		}, tree2);

	cout << "Tree 1: \n";
	PrintTree(tree1);
	cout << "\nTree 2: \n";
	PrintTree(tree2);

	cout << "\nThe Same Binary Tree?\n" << (TheSameBinaryTree_DFS(tree1, tree2) ? "YES" : "NO") << endl;

	DeleteTree(tree1);
	DeleteTree(tree2);

	return 0;
}

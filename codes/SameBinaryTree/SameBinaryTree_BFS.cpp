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
 * 使用队列FIFO特性，对两颗树进行层次遍历，比较元素的值：
 * （1）两棵树是空二叉树，自然是相同的；
 * （2）若其中一颗为空二叉树，另一颗非空，则二叉树不相同；
 * （3）不是以上两种情况，就按左右顺序依次比较节点的值，发现有不同，则两棵树不同；
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-05-07
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

bool SameBinaryTree_BFS(TreeNode<int>* tree1, TreeNode<int>* tree2)
{
	queue<TreeNode<int>*> que1({ tree1 });
	queue<TreeNode<int>*> que2({ tree2 });

	while (!que1.empty() || !que2.empty())
	{
		if (!que1.empty()) que1.pop();
		if (!que2.empty()) que2.pop();

		if (tree1 == nullptr && tree2 == nullptr);
		else if ((tree1 == nullptr || tree2 == nullptr) ||
				 tree1->data != tree2->data)
		{
			return false;
		}

		/**
		 * 这里需要注意，只有左右子节点都不为空时，才需要将子节点入队；
		 * 子节点都为空，表示已经遍历到该分支的叶子节点，不需要继续遍历了；
		 */
		if (tree1 != nullptr &&
			(tree1->left != nullptr || tree1->right != nullptr))
		{
			que1.push(tree1->left);
			que1.push(tree1->right);
		}
		if (tree2 != nullptr &&
			(tree2->left != nullptr || tree2->right != nullptr))
		{
			que2.push(tree2->left);
			que2.push(tree2->right);
		}

		tree1 = que1.empty() ? nullptr : que1.front();
		tree2 = que2.empty() ? nullptr : que2.front();
	}

	return true;
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

	unsigned int n = 0;
	// n 的增加必定快于 idx，故边界判断用 n 即可 
	for (unsigned int idx = 0; n < dataSize; ++idx)
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
void PrintTree(const TreeNode<int>* const treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	const TreeNode<int>* p = nullptr;

	while (!printQue.empty())
	{
		while (!printQue.empty())
		{
			p = printQue.front();
			printQue.pop();
			if (p) cout << p->data << ", ";
			else cout << "null, ";

			if (p && (p->left || p->right))
			{
				tempQue.push(p->left);
				tempQue.push(p->right);
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
		NODE(9356), nullptr, NODE(99)
		}, tree1);
	TreeNode<int>* tree2 = nullptr;
	CreateTree({ NODE(4),
		NODE(2), NODE(6),
		NODE(1), NODE(7), NODE(5), NODE(7),
		NODE(9356), NODE(99)
		}, tree2);

	cout << "Tree 1: \n";
	PrintTree(tree1);
	cout << "\nTree 2: \n";
	PrintTree(tree2);

	cout << "\nThe Same Binary Tree?\n" << (SameBinaryTree_BFS(tree1, tree2) ? "YES" : "NO") << endl;

	DeleteTree(tree1);
	DeleteTree(tree2);

	return 0;
}

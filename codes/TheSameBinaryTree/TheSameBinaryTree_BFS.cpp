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

bool TheSameBinaryTree_BFS(TreeNode<int>* tree1, TreeNode<int>* tree2)
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

int main()
{
	// 应该依据数据构造二叉树，这里直接手写两棵树 
	TreeNode<int>* tree1 = new TreeNode<int>(4);
	tree1->left = new TreeNode<int>(2);
	tree1->left->left = new TreeNode<int>(1);
	tree1->left->right = new TreeNode<int>(7);
	tree1->right = new TreeNode<int>(6);
	tree1->right->left = new TreeNode<int>(5);
	tree1->right->right = new TreeNode<int>(7);
	tree1->right->right->left = new TreeNode<int>(9356);
	TreeNode<int>* tree2 = new TreeNode<int>(4);
	tree2->left = new TreeNode<int>(2);
	tree2->left->left = new TreeNode<int>(1);
	tree2->left->right = new TreeNode<int>(7);
	tree2->right = new TreeNode<int>(6);
	tree2->right->left = new TreeNode<int>(5);
	tree2->right->right = new TreeNode<int>(7);
	tree2->right->right->right = new TreeNode<int>(9356);

	cout << (TheSameBinaryTree_BFS(tree1, tree2) ? "TRUE" : "FALSE") << endl;

	return 0;
}

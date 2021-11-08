/**************************************************************************************************
 * 【题目描述】
 * 给定一颗二叉树，返回其前序遍历
 *
 * 【输入】
 * 二叉树：
 *    4
 *  2   6
 * 1 3 5 7
 *
 * 【输出】
 * 前序遍历序列：4 2 1 3 6 5 7
 *
 * 【解题思路】
 * 方法一：
 * 前序遍历顺序为“根左右”，考虑采用递归，传入子树根节点，先将根节点推入数组，然后依次将根节点的左右子树节
 * 点作为参数进行递归调用，遇到传入的根节点为空时返回。
 *
 * 方法二：
 * 递归有时候不是那么好理解，而且递归层级多的话，会占用较多资源。也可以考虑用栈的方式，大致步骤：
 * （1）先将根节点入栈，然后进行循环遍历，中止条件为空栈；
 * （2）弹出栈顶节点，并作为结果推入数组；
 * （3）依次入栈弹出节点的右子节点和左子节点（这样出栈的时候就符合“根左右”的顺序了）；
 * （4）子节点为空不如栈，重复（2）（3）直到栈空是跳出循环。
 * 
 * 方法三：
 * 采用Morris遍历算法，可以将空间复杂度降为O(1)，Morris是一种遍历二叉树的算法，利用叶子节点的左右空指针。
 * 在二叉树的叶子节点中，其左右子节点指向为空，虽然是空指针，但指针本身已经占用空间了，Morris算法的核心思
 * 想就是临时利用这些，已经声明但没有定义的空指针变量，相当于把原本对空间的需求转移到了已经存在的但指向为
 * 空的指针上，是一种对无指向的内存的充分利用。大致步骤：
 * （1）CurNode.left 不为空，找到以 CurNode.left 为根节点的最右侧节点 MostRightNode：
 *      I.  MostRightNode.right 为空，则将 MostRightNode.right = CurNode，这里保证了后续的当前遍历节点
 *          右移的时候，能够回到根节点，本质为借用叶子节点 MostRightNode 的右指针，该指针必为空值。然后 
 *          CurNode = CurNode.left，因为题目要求为前序遍历，所以此步骤遍历的 CurNode 为首次访问，将其推
 *          入数组，满足前序遍历“根左右”的特性。
 *      II. MostRightNode.right 不为空，且刚好等于 CurNode，此时遍历的 CurNode 其实不是首次访问，而是由
 *          CurNode.left 右移而来，因为之前优先左移，所以此时回到之前标记的根节点，就需要右移。这里需要
 *          注意将 MostRightNode.right = nullptr，本质上只是借用了 MostRightNode 叶子节点的右侧空指针，
 *          用完后需要重置。
 * （2）CurNode.left 为空，直接推入 CurNode 节点，这一步符合前序遍历“根左右”和中序遍历“左根右”的特性，也
 *      保证了步骤（1）的第 II 种情况中，不会出现 MostRightNode.right 不为空且不等于 CurNode 的情况。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 方法三：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-21
 **************************************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T> *left;
	TreeNode<T> *right;
	/** 父节点主要用于打印的时候标名关系，算法本身并不需要 */
	TreeNode<T> *dad;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define N(value) (new TreeNode<int>(value))

/** 递归遍历 */
void TraverseBinaryTree_DLR_Recursion(TreeNode<int> *treeRoot, vector<TreeNode<int> *> &resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	// 根
	resultArr.push_back(treeRoot);
	// 左
	if (treeRoot->left)
		TraverseBinaryTree_DLR_Recursion(treeRoot->left, resultArr);
	// 右
	if (treeRoot->right)
		TraverseBinaryTree_DLR_Recursion(treeRoot->right, resultArr);
}

/** 利用栈迭代遍历 */
void TraverseBinaryTree_DLR_Stack(TreeNode<int> *treeRoot, vector<TreeNode<int> *> &resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	stack<TreeNode<int> *> tempStack({treeRoot});
	TreeNode<int> *node = nullptr;

	while (!tempStack.empty())
	{
		node = tempStack.top();
		tempStack.pop();

		resultArr.push_back(node);

		// 先入栈右孩子，再入栈左孩子，出栈时就是前序遍历的根左右了
		if (node && node->right)
			tempStack.push(node->right);
		if (node && node->left)
			tempStack.push(node->left);
	}
}

/** Morris（莫里斯）遍历 */
void TraverseBinaryTree_DLR_Morris(TreeNode<int> *treeRoot, vector<TreeNode<int> *> &resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	TreeNode<int> *pCur = treeRoot;
	// 左子树最右侧节点
	TreeNode<int> *pMostRight = nullptr;

	while (pCur)
	{
		if (pCur->left)
		{
			pMostRight = pCur->left;

			while (pMostRight && pMostRight->right && pMostRight->right != pCur)
			{
				pMostRight = pMostRight->right;
			}

			if (!pMostRight->right)
			{
				// 根，第一次访问就输出，满足前序遍历“根左右”特性
				resultArr.push_back(pCur);

				pMostRight->right = pCur;
				pCur = pCur->left;
				continue;
			}
			else
			{
				/**
				 * resultArr.push_back(pCur);
				 * 
				 * 如果在这里输出，节点被再次访问，满足中序遍历“左根右”的特性
				 */

				pMostRight->right = nullptr;
				pCur = pCur->right;
			}
		}
		else
		{
			// 左右
			resultArr.push_back(pCur);
			pCur = pCur->right;
		}
	}
}

/**
 * @brief 依据数组创建一颗二叉树
 * @param treeData 数据容器，右值引用
 */
TreeNode<int> *CreateTree(vector<TreeNode<int> *> &&treeData)
{
	unsigned int dataSize = treeData.size();

	// 空容器或容器首节点为空指针，都当作空树处理
	if (dataSize == 0 || !treeData[0])
	{
		// 释放右值引用的内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		return nullptr;
	}

	TreeNode<int> *head = treeData[0];

	TreeNode<int> *node = nullptr;
	for (unsigned int idx = 0, n = 0; n < dataSize; ++idx)
	{
		node = treeData[idx];

		if (++n < dataSize && treeData[n] && node)
		{
			node->left = treeData[n];
			node->left->dad = node;
		}

		if (++n < dataSize && treeData[n] && node)
		{
			node->right = treeData[n];
			node->right->dad = node;
		}
	}

	return head;
}

/**
 * @brief 释放一颗二叉树内存
 * @param treeRoot 树根节点，指针引用，释放后置nullptr
 */
void DeleteTree(TreeNode<int> *&treeRoot)
{
	if (!treeRoot)
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
 * @brief 打印一颗二叉树，BFS遍历
 * @param treeRoot 树根节点，常量指针
 */
void PrintTree(const TreeNode<int> *treeRoot)
{
	if (!treeRoot)
	{
		cout << "It's an empty tree!\n";
		return;
	}

	queue<const TreeNode<int> *> printQue({treeRoot});
	queue<const TreeNode<int> *> tempQue;
	unsigned int layerCount = 0;

	while (!printQue.empty())
	{
		cout << '[' << ++layerCount << "]  ";

		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();

			if (treeRoot)
			{
				(treeRoot->dad) ? cout << treeRoot->data << '(' << treeRoot->dad->data << "), " : cout << treeRoot->data << "(null), ";
			}
			else
				cout << "null, ";

			if (treeRoot && (treeRoot->left || treeRoot->right))
			{
				tempQue.push(treeRoot->left);
				tempQue.push(treeRoot->right);
			}
		}
		cout << endl;
		printQue.swap(tempQue);
	}
}

int main()
{
	TreeNode<int> *treeRoot = CreateTree({
		N(4),
		N(2),
		N(6),
		N(1),
		N(3),
		N(5),
		N(7),
		N(11),
		N(22),
		N(33),
		N(44),
		N(55),
		N(66),
		N(77),
		N(88),
	});

	cout << "The tree: \n";
	PrintTree(treeRoot);

	vector<TreeNode<int> *> resultArr;
	TraverseBinaryTree_DLR_Recursion(treeRoot, resultArr);
	cout << "\n[Recursion] DLR Traverse array: \n";
	for (vector<TreeNode<int> *>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";
	cout << endl;

	resultArr.clear();
	TraverseBinaryTree_DLR_Stack(treeRoot, resultArr);
	cout << "\n[Stack] DLR Traverse array: \n";
	for (vector<TreeNode<int> *>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";
	cout << endl;

	resultArr.clear();
	TraverseBinaryTree_DLR_Morris(treeRoot, resultArr);
	cout << "\n[Morris] DLR Traverse array: \n";
	for (vector<TreeNode<int> *>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";
	cout << endl;

	DeleteTree(treeRoot);

	return 0;
}
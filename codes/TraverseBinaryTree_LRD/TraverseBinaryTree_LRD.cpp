/**************************************************************************************************
 * 【题目描述】
 * 给定一颗二叉树，返回它的后续遍历。
 *
 * 【输入】
 * 二叉树：
 *    4
 *  2   6
 * 1 3 5 7
 *
 * 【输出】
 * 后续遍历序列: 1 3 2 5 7 6 4
 *
 * 【解题思路】
 * 方法一：
 * 依据后续遍历“左右根”的特性，考虑采用递归遍历，传入树根节点，
 * 若左节点或右节点存在，优先传入子节点进行递归，
 * 当左右节点都不存在时，即将当前节点值推入数组。
 *
 * 方法二：
 *
 * 方法三：
 * 有时候递归并不是特别好理解，而且递归层级过多的话会占用较多资源，考虑用栈的方式，
 * 后续遍历需要准备两个栈：inputStack 和额外的 tempStack.
 * 额外的栈 tempStack 是因为栈有先进后出的特性，用栈来后续遍历会得到后续遍历的倒序列，所以用栈来翻转一下。
 * 大致过程：
 * （1）节点入栈 inputStack，然后出栈并紧接着入栈 tempStack，出栈时，将左右子节点依次入栈 inputStack；
 * （2）重复步骤（1）直到 inputStack 栈空，此时将 tempStack 栈中的元素依次出栈，并推入一个序列容器，
 *		即为最终后续遍历结果。
 * 这里需要注意的是，也可以不用 tempStack，而是采用从后往前的方式构建序列，减少逻辑处理，不过构建序列需要
 * 注意容器是否有较优的头部插入效率，比如STL中 list 比 vector 更适合作为最终容器，因为 list 头部插入的效率
 * 要高于 vector.
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 * 方法二：
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 * 方法三：
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 * 方法四：
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode<T>* dad; // 仅用于打印显示层次结构，不参与算法逻辑 

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define N(value) (new TreeNode<int>(value))

/** 递归遍历 */
void TraverseBinaryTree_LRD_Recursion(TreeNode<int>* treeRoot, vector<TreeNode<int>*>& resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	if (treeRoot->left)
		TraverseBinaryTree_LRD_Recursion(treeRoot->left, resultArr);
	if (treeRoot->right)
		TraverseBinaryTree_LRD_Recursion(treeRoot->right, resultArr);

	resultArr.push_back(treeRoot);
}

/** 利用单栈迭代遍历 */
void TraverseBinaryTree_LRD_OneStack(TreeNode<int>* treeRoot, vector<TreeNode<int>*>& resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	stack <TreeNode<int>*> inputStack;
	TreeNode<int>* lastNode = nullptr;

	while (!inputStack.empty() || treeRoot)
	{
		while (treeRoot)
		{
			inputStack.push(treeRoot);
			treeRoot = treeRoot->left;
		}

		treeRoot = inputStack.top();
		/**
		 * treeRoot->right == lastNode 相当于标记了 treeRoot 虽然存在右侧节点，但已经输出了，
		 * 此时左右节点均以输出，就可以输出根节点，这样就保证了后续遍历“左右根”的特性
		 */
		if (!treeRoot->right || treeRoot->right == lastNode)
		{
			lastNode = treeRoot;
			resultArr.push_back(treeRoot);
			inputStack.pop();
			treeRoot = nullptr;
		}
		else
		{
			treeRoot = treeRoot->right;
		}
	}
}

/** 利用双栈迭代遍历 */
void TraverseBinaryTree_LRD_TwoStack(TreeNode<int>* treeRoot, vector<TreeNode<int>*>& resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	stack<TreeNode<int>*> inputStack({ treeRoot });
	stack<TreeNode<int>*> tempStack;

	while (!inputStack.empty())
	{
		treeRoot = inputStack.top();
		inputStack.pop();

		if (treeRoot)
		{
			tempStack.push(treeRoot);
			// 也可以如下所示直接从后往前构建序列，这样就不需要再遍历一遍tempStack了 
			//resultArr.insert(resultArr.begin(), treeRoot);

			if (treeRoot->left) inputStack.push(treeRoot->left);
			if (treeRoot->right) inputStack.push(treeRoot->right);
		}
	}

	while (!tempStack.empty())
	{
		resultArr.push_back(tempStack.top());
		tempStack.pop();
	}
}

/** Morris（莫里斯）遍历 */
void TraverseBinaryTree_LRD_Morris(TreeNode<int>* treeRoot, vector<TreeNode<int>*>& resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	TreeNode<int>* pCur = treeRoot;
	/** 左子树最右侧节点 */
	TreeNode<int>* pMostRight = nullptr;

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
				pMostRight->right = pCur;
				pCur = pCur->left;
				continue;
			}
			else
			{
				pMostRight->right = nullptr;
				pCur = pCur->right;
			}
		}
		else
		{
			pCur = pCur->right;
		}
	}
}

/**
 * @brief 创建一颗二叉树
 * @param treeData 树节点容器，右值引用
 * @return 返回树根节点指针，指针指向内存并非在此函数内申请
 */
TreeNode<int>* CreateTree(vector<TreeNode<int>*>&& treeData)
{
	// 空容器，或首节点为空的容器，都当作空树处理
	if (treeData.empty() || !treeData[0])
	{
		// 释放容器内存
		for (unsigned int idx = 0; idx < treeData.size(); ++idx)
			delete treeData[idx];
		treeData.clear();
		return nullptr;
	}

	TreeNode<int>* head = treeData[0];
	unsigned int dataSize = treeData.size();

	TreeNode<int>* node = nullptr;
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
 * @param treeRoot 二叉树根节点，指针引用，释放后置nullptr
 */
void DeleteTree(TreeNode<int>*& treeRoot)
{
	if (!treeRoot) return;

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

/**
 * @brief 打印一颗二叉树
 * @param treeRoot 树根节点，常量指针
 */
void PrintTree(const TreeNode<int>* treeRoot)
{
	if (!treeRoot)
	{
		cout << "It's an empty tree!\n";
		return;
	}

	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;

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
				(treeRoot->dad) ? cout << treeRoot->data << '(' << treeRoot->dad->data << "), " :
					cout << treeRoot->data << "(null), ";
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
	TreeNode<int>* treeRoot = CreateTree({
								 N(4),
				   N(2),                       N(6),
			N(1),         N(3),         N(5),         N(7),
		N(11), N(22), N(33), N(44), N(55), N(66), N(77), N(88),
		});

	cout << "The tree:\n";
	PrintTree(treeRoot);

	vector<TreeNode<int>*> resultArr;
	TraverseBinaryTree_LRD_Recursion(treeRoot, resultArr);
	cout << "\n[Recursion] LRD traverse array:\n";
	for (vector<TreeNode<int>*>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	resultArr.clear();
	TraverseBinaryTree_LRD_OneStack(treeRoot, resultArr);
	cout << "\n[One Stack] LRD traverse array:\n";
	for (vector<TreeNode<int>*>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	resultArr.clear();
	TraverseBinaryTree_LRD_TwoStack(treeRoot, resultArr);
	cout << "\n[Two Stack] LRD traverse array:\n";
	for (vector<TreeNode<int>*>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	resultArr.clear();
	TraverseBinaryTree_LRD_Morris(treeRoot, resultArr);
	cout << "\n[Morris] LRD traverse array:\n";
	for (vector<TreeNode<int>*>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	DeleteTree(treeRoot);

	return 0;
}

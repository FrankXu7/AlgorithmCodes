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
 * 依据后续遍历“左右根”的特性，考虑采用递归遍历，传入树根节点，若左节点或右节点存在，优先传入子节点进行递
 * 归，当左右节点都不存在时，即将当前节点值推入数组。
 *
 * 方法二：
 * 有时候递归并不是特别好理解，而且递归层级过多的话会占用较多资源，考虑用栈的方式，后续遍历需要准备两个栈：
 * inputStack 和额外的 tempStack。额外的栈 tempStack 是因为栈有先进后出的特性，用栈来后续遍历会得到后续
 * 遍历的倒序列，所以用栈来翻转一下。大致过程：
 * （1）节点入栈 inputStack，然后出栈并紧接着入栈 tempStack，出栈时，将左右子节点依次入栈 inputStack；
 * （2）重复步骤（1）直到 inputStack 栈空，此时将 tempStack 栈中的元素依次出栈，并推入一个序列容器，即为
 *      最终后续遍历结果。
 * 这里需要注意的是，也可以不用 tempStack，而是采用从后往前的方式构建序列，减少逻辑处理，不过构建序列需要
 * 注意容器是否有较优的头部插入效率，比如STL中 list 比 vector 更适合作为最终容器，因为 list 头部插入的效
 * 率要高于 vector.
 * 
 * 方法三：
 * 双栈法的逻辑相对简单，但是用到了两个栈，而且因为得到的是后续遍历的反序序列，还需要将序列倒置一下。参考
 * 中序遍历的做法，中序遍历只用一个栈，在弹出栈顶元素的时候，如果有右节点，则从右节点开始，依次压入左节点
 * 到叶子节点为止，这样序列就符合中序遍历“左根右”的特性。这里可以得出，如果栈顶元素在弹出前，提前判断到存
 * 在右节点，先不弹出栈顶元素，而直接从右节点开始，依次压入左节点到叶子节点为止。这样构建的序列就符合后续
 * 遍历“左右根”的特性。大致过程：
 * （1）从根节点开始，依次压入左节点到叶子节点为止；
 * （2）不出栈的情况下，判断栈顶元素是否有右节点，没有则出栈，并推入输出序列；
 * （3）栈顶元素有右节点的情况下，直接从其右节点开始，依次压入左节点到叶子节点为止；
 * （4）重复（1）（2）（3）直到栈空。
 * 
 * 方法四：
 * 采用Morris遍历，二叉树的Morris后续遍历比前序和中序更复杂一点，假如某个节点A的左侧分支的最右节点的右指
 * 针指向A，当遍历到这个最右侧节点时，此时已经无法直接回到这个最右侧节点的父节点了，也就失去了“左右根”中
 * “根”的指向。仔细想想，当遍历一圈回到A节点时，之前那个找不到的最右侧节点的父节点，其实就在A节点左侧分支
 * 的最右侧的路径上，显然第一个这种路径就是二叉树最左侧的节点。而二叉树的后续遍历，符合这么一个规律：从树
 * 的最左侧节点所在的最右侧路径开始，逐层网上，逆序遍历，就是二叉树的后续遍历了，比如题目中输入的二叉树，
 * 路径从左往右，节点从上到下，第一条路径是：1，第二条路径是：2、3，第三条路径是：5，第四条路径是：4、6、
 * 7；依据路径顺序逆序输出，刚好就是二叉树的后续遍历。算法大致步骤：
 * （1）CurNode.left 不为空，找到以 CurNode.left 为根节点的最右侧节点 MostRightNode：
 *      I.  MostRightNode.right 为空，借用其指针变量，指向当前遍历节点，MostRightNode.right = CurNode，
 *          这样保证后面遍历的节点在左右移动的时候还能够回到根节点。然后将当前遍历节点左移，即执行表达式
 *          CurNode = CurNode.left；
 *      II. MostRightNode.right 不为空，且刚好等于 CurNode，此时遍历的 CurNode 其实不是首次访问，相当于
 *          回到了第 I 种情况中的 CurNode，以 CurNode.left 所在的最右侧路径为分界线，其左侧所有节点均已
 *          输出，该路径需要【逆序】输出以保证“左右根”的特性，因为 MostRightNode.right 记录了第 I 种情
 *          况中的 CurNode，所以遍历中止条件就是回到了 CurNode，然后需要特别注意要将 MostRightNode 设置
 *          为 nullptr，因为算法只是借用了空指针变量，不能改变树的结构。
 * （2）CurNode.left 直接右移，在步骤（1）的第 II 种情况中，来处理 CurNode.left 所在最右侧路径的遍历输
 *      出问题。值得注意的是，这个步骤也保证了步骤（1）的第 II 种情况中，不会出现 MostRightNode.right 
 *      不为空且不等于 CurNode 的情况。
 * 
 * 需要特别注意的是，针对二叉树最后一条路径（即最右侧路径）在遍历结束后这条路径还未输出，需要以根节点为起
 * 始节点，逆序输出该路径节点。
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
 * 空间复杂度：O(N)
 * 方法四：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-24
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T> *left;
	TreeNode<T> *right;
	TreeNode<T> *dad; // 仅用于打印显示层次结构，不参与算法逻辑

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

#define N(value) (new TreeNode<int>(value))

/** 递归遍历 */
void TraverseBinaryTree_LRD_Recursion(TreeNode<int> *treeRoot, vector<TreeNode<int> *> &resultArr)
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

/** 利用双栈迭代遍历 */
void TraverseBinaryTree_LRD_TwoStack(TreeNode<int> *treeRoot, vector<TreeNode<int> *> &resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	stack<TreeNode<int> *> inputStack({treeRoot});
	stack<TreeNode<int> *> tempStack;

	while (!inputStack.empty())
	{
		treeRoot = inputStack.top();
		inputStack.pop();

		if (treeRoot)
		{
			tempStack.push(treeRoot);
			// 也可以如下所示直接从后往前构建序列，这样就不需要再遍历一遍tempStack了
			//resultArr.insert(resultArr.begin(), treeRoot);

			if (treeRoot->left)
				inputStack.push(treeRoot->left);
			if (treeRoot->right)
				inputStack.push(treeRoot->right);
		}
	}

	while (!tempStack.empty())
	{
		resultArr.push_back(tempStack.top());
		tempStack.pop();
	}
}

/** 利用单栈迭代遍历 */
void TraverseBinaryTree_LRD_OneStack(TreeNode<int> *treeRoot, vector<TreeNode<int> *> &resultArr)
{
	if (!treeRoot)
	{
		resultArr.clear();
		return;
	}

	stack<TreeNode<int> *> inputStack;
	// 输出序列中的最后一个元素
	TreeNode<int> *lastNode = nullptr;

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

/** Morris（莫里斯）遍历，因为有逆序遍历的步骤，用list效率更高 */
void TraverseBinaryTree_LRD_Morris(TreeNode<int> *treeRoot, list<TreeNode<int> *> &resultList)
{
	if (!treeRoot)
	{
		resultList.clear();
		return;
	}

	TreeNode<int> *pCur = treeRoot;
	/** 左子树最右侧节点 */
	TreeNode<int> *pMostRight = nullptr;

	list<TreeNode<int> *>::iterator inPos;
	TreeNode<int> *node = nullptr;

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
				/**
				 * 此时回到了之前遍历到某个节点A时，以A为根节点的最右侧节点的指向，即指向A本身，
				 * 逆序遍历A节点的左侧分支最右侧路径并输出，这样就保证了先输出右节点，再输出根节点；
				 */
				if (pCur && pCur->left)
				{
					inPos = resultList.end();
					node = pCur->left;
					while (node != pCur)
					{
						inPos = resultList.insert(inPos, node);
						node = node->right;
					}
				}

				pMostRight->right = nullptr;
				pCur = pCur->right;
			}
		}
		else
		{
			pCur = pCur->right;
		}
	}

	// 逆序输出整个二叉树最右侧的分支
	inPos = resultList.end();
	while (treeRoot)
	{
		inPos = resultList.insert(inPos, treeRoot);
		treeRoot = treeRoot->right;
	}
}

/**
 * @brief 创建一颗二叉树
 * @param treeData 树节点容器，右值引用
 * @return 返回树根节点指针，指针指向内存并非在此函数内申请
 */
TreeNode<int> *CreateTree(vector<TreeNode<int> *> &&treeData)
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

	TreeNode<int> *head = treeData[0];
	unsigned int dataSize = treeData.size();

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
 * @param treeRoot 二叉树根节点，指针引用，释放后置nullptr
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
 * @brief 打印一颗二叉树
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

	cout << "The tree:\n";
	PrintTree(treeRoot);

	vector<TreeNode<int> *> resultArr;
	TraverseBinaryTree_LRD_Recursion(treeRoot, resultArr);
	cout << "\n\n[Recursion] LRD traverse array:\n";
	for (vector<TreeNode<int> *>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	resultArr.clear();
	TraverseBinaryTree_LRD_TwoStack(treeRoot, resultArr);
	cout << "\n\n[Two Stack] LRD traverse array:\n";
	for (vector<TreeNode<int> *>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	resultArr.clear();
	TraverseBinaryTree_LRD_OneStack(treeRoot, resultArr);
	cout << "\n\n[One Stack] LRD traverse array:\n";
	for (vector<TreeNode<int> *>::iterator itr = resultArr.begin(); itr != resultArr.end(); ++itr)
		cout << (*itr)->data << ", ";

	list<TreeNode<int> *> resultList;
	TraverseBinaryTree_LRD_Morris(treeRoot, resultList);
	cout << "\n\n[Morris] LRD traverse array:\n";
	for (list<TreeNode<int> *>::iterator itr = resultList.begin(); itr != resultList.end(); ++itr)
		cout << (*itr)->data << ", ";

	cout << endl;

	DeleteTree(treeRoot);
	resultArr.clear();
	resultList.clear();

	return 0;
}

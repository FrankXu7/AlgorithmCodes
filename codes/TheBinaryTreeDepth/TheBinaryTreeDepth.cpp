/**************************************************************************************************
 * 【题目描述】
 * 判断给定的二叉树的最大深度。
 *
 * 【输入】
 * 一颗二叉树，不一定是搜索树或平衡树。
 * 【输出】
 * 二叉树的最大深度。
 *
 * 【解题思路】
 * 方法一：
 * 采用BFS遍历，利用两个队列交替存储彼此队列中存储节点的子节点，直到两个队列为空，
 * 每次遍历前，判断队列中有元素，则表示该层非空，深度+1，具体步骤：
 * （1）BFS一层节点入Queue1；
 * （2）遍历Queue1中节点，若有子节点，则入队Queue2；
 * （3）再遍历Queue2中节点，若有子节点，则入队Queue1；
 * （4）重复上述过程直到两个队列都为空；
 * 
 * 方法二：
 * 依然采用BFS遍历，只利用一个队列，记录每一层的节点数量，出队时节点数量依次减一，
 * 并将该节点的非空的子节点入队，节点数量减为0时，深度+1，并且节点数量更新为下一层的数量，
 * 具体步骤：
 * （1）将一层节点入队，并统计该层的节点数量；
 * （2）依次出队节点，每出队一个节点，节点数量减一，并将该节点的非空的子节点入队；
 * （3）节点数量减为0时表示该层出队完毕，深度+1，节点数量重置为当前队列的siez；
 * 
 * @author FrankX
 * @date 2021-05-12
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
struct TreeNode 
{
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		left = right = nullptr;
	}
};

#define NODE(data) (new TreeNode<int>(data))

unsigned int TheBinaryTreeDepth_1(const TreeNode<int>* treeRoot)
{
	unsigned int treeDepth = 0;
	queue<const TreeNode<int>*> que1({ treeRoot });
	queue<const TreeNode<int>*> que2;

	while (!que1.empty() || !que2.empty())
	{
		if (!que1.empty()) ++treeDepth;
		while (!que1.empty())
		{
			treeRoot = que1.front();
			if (treeRoot->left) que2.push(treeRoot->left);
			if (treeRoot->right) que2.push(treeRoot->right);
			que1.pop();
		}

		if (!que2.empty()) ++treeDepth;
		while (!que2.empty())
		{
			treeRoot = que2.front();
			if (treeRoot->left) que1.push(treeRoot->left);
			if (treeRoot->right) que1.push(treeRoot->right);
			que2.pop();
		}
	}

	return treeDepth;
}

unsigned int TheBinaryTreeDepth_2(const TreeNode<int>* treeRoot)
{
	unsigned int treeDepth = 0;
	queue<const TreeNode<int>*> que({ treeRoot });
	unsigned int nodeCount = 1;
	
	while (!que.empty())
	{
		--nodeCount;
		treeRoot = que.front();
		que.pop();
		if (treeRoot)
		{
			if (treeRoot->left) que.push(treeRoot->left);
			if (treeRoot->right) que.push(treeRoot->right);
		}

		if (nodeCount == 0)
		{
			++treeDepth;
			nodeCount = que.size();
		}
	}

	return treeDepth;
}

void CreateTree(vector<TreeNode<int>*>&& treeData, TreeNode<int>*& treeRoot)
{
	treeRoot = treeData[0];
	unsigned int dataSize = treeData.size();
	for (unsigned idx = 0, n = 0; n < dataSize; ++idx)
	{
		if (treeData[idx] && ++n < dataSize)
			treeData[idx]->left = treeData[n];
		if (treeData[idx] && ++n < dataSize)
			treeData[idx]->right = treeData[n];
	}
}

void DeleteTree(TreeNode<int>*& treeRoot)
{
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

void PrintTree(const TreeNode<int>* treeRoot)
{
	queue<const TreeNode<int>*> printQue({ treeRoot });
	queue<const TreeNode<int>*> tempQue;
	while (!printQue.empty())
	{
		while (!printQue.empty())
		{
			treeRoot = printQue.front();
			printQue.pop();
			if (treeRoot) cout << treeRoot->data << ", ";
			else cout << "null, ";
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
	TreeNode<int>* treeRoot = nullptr;
	CreateTree({NODE(4),
		NODE(5), NODE(6), 
		nullptr, NODE(88), nullptr, nullptr,
		NODE(67), NODE(54), nullptr, NODE(88),
		}, treeRoot);

	cout << "Tree: \n";
	PrintTree(treeRoot);

	cout << "\n[Solution 1] The Binary Tree Depth: " << TheBinaryTreeDepth_1(treeRoot) << endl;
	cout << "[Solution 2] The Binary Tree Depth: " << TheBinaryTreeDepth_2(treeRoot) << endl;

	DeleteTree(treeRoot);

	return 0;
}



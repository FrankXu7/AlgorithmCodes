/**************************************************************************************************
 * 【题目描述】
 * 给定一颗二叉树的根节点root，返回所有根节点到叶子节点的路径。
 *
 * 【输入】
 * Tree Data Array=[1,2,3,4,5,6,7,null,null,8,9,null,null,null,10]
 * 【输出】
 * Paths=[
 * "1 -> 2 -> 4",
 * "1 -> 2 -> 5 -> 8",
 * "1 -> 2 -> 5 -> 9",
 * "1 -> 3 -> 6",
 * "1 -> 3 -> 7 -> 10" ]
 * 
 * 【解题思路】
 * DFS遍历法：
 * 使用递归实现深度遍历二叉树，记录从根节点到当前节点的路径字符串，并作为参数传到下一次递归中去，
 * 当递归到叶子节点时，将当前节点追加到路径字符串中，并推入作为参数传入的容器中，容器必须是左值引用。
 * 
 * BFS遍历法：
 * 使用迭代实现广度遍历二叉树，用两个双端队列，一个记录节点，另一个记录从根节点到该节点的路径字符串，
 * 正常情况下两个队列元素数量是相等的。在一次遍历中，同时出队两个队列的首元素，如果出队的节点不是
 * 叶子节点，则将其左右孩子节点入队到节点队列，并依据左右孩子的数据值和当前节点的路径字符串，组合新的
 * 左右孩子路径字符串，入队到路径字符串队列；若本次遍历出队的节点是叶子节点，则将对应出队的路径字符串
 * 推入最终需要返回的路径容器。
 * 
 * 【解题分析】
 * DFS遍历：
 * 时间复杂度：O(N^2) 访问节点最差情况是链表O(N)，每次递归都需要拷贝路径字符串O(N)，所以最差情况为O(N*N)
 * 空间复杂度：O(N^2) 递归调用最差情况是链表O(N)，递归时复制字符串最差为O(N)，所以需要空间O(N^2)
 * BFS遍历：
 * 时间复杂度：O(N^2) 情况和DFS遍历类型
 * 空间复杂度：O(N^2) 情况和DFS遍历类似
 * 
 * @author FrankX
 * @date 2021-09-16
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <deque>
using namespace std;

template<typename DataType>
struct TreeNode 
{
	DataType data;
	shared_ptr<TreeNode<DataType>> left;
	decltype(left) right;
	decltype(left) dad; // 算法逻辑本身不需要，用于打印显示树的结构 

	TreeNode(DataType _data) { data = _data; }
};

#define N(val, DataType) (make_shared<TreeNode<DataType>>(val))

template<typename spNodeType>
void RecursionCall(spNodeType& root, string pathStr, vector<string>& paths)
{
	pathStr += to_string(root->data);

	// 组装到叶子节点时推入容器 
	if (!root->left && !root->right)
	{
		paths.emplace_back(pathStr);
		return;
	}
	pathStr += " -> ";

	if (root->left)
		RecursionCall(root->left, pathStr, paths);
	if (root->right)
		RecursionCall(root->right, pathStr, paths);
}

template<typename spNodeType>
vector<string> BinaryTreePaths_DFS(spNodeType root)
{
	vector<string> paths;
	
	RecursionCall(root, "", paths);

	return paths;
}

template<typename spNodeType>
vector<string> BinaryTreePaths_BFS(spNodeType root)
{
	vector<string> paths;
	string curPath = "";
	
	deque<spNodeType> nodesQue{ root };
	deque<string> pathsQue{ to_string(root->data) };

	// 正常情况下，两个队列元素数量相同 
	while (!nodesQue.empty() && !pathsQue.empty())
	{
		root = nodesQue.front();
		nodesQue.pop_front();

		curPath = pathsQue.front();
		pathsQue.pop_front();

		if (!root->left && !root->right)
		{
			paths.emplace_back(curPath);
			continue;
		}
		curPath += " -> ";

		if (root->left)
		{
			nodesQue.emplace_back(root->left);
			pathsQue.emplace_back(curPath + to_string(root->left->data));
		}
		if (root->right)
		{
			nodesQue.emplace_back(root->right);
			pathsQue.emplace_back(curPath + to_string(root->right->data));
		}
	}

	return paths;
}

/**
 * @brief 辅助函数，使用容器数组的节点数据生成一颗二叉树
 * @param dataArr 二叉树节点容器，右值引用
 * @return 返回二叉树的根节点
 */
template<typename spNodeType>
spNodeType CreateTree(vector<spNodeType>&& dataArr)
{
	if (dataArr.empty()) return nullptr;
	unsigned int dataSize = dataArr.size(), dadIdx = 0, leftIdx = 0, rightIdx = 0;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		// 找爹 
		if (idx > 0 && dataArr[idx])
		{
			dadIdx = (idx - 1) / 2;
			dataArr[idx]->dad = dataArr[dadIdx];
		}

		// 找俩儿子 
		leftIdx = 2 * idx + 1;
		rightIdx = leftIdx + 1;

		if (leftIdx < dataSize && dataArr[idx])
			dataArr[idx]->left = dataArr[leftIdx];
		
		if (rightIdx < dataSize && dataArr[idx])
			dataArr[idx]->right = dataArr[rightIdx];
	}

	return dataArr[0];
}

/**
 * @brief 辅助函数，打印一颗二叉树
 * @param root 树根节点，常量左值引用
 */
template<typename spNodeType>
void PrintTree(spNodeType root)
{
	deque<decltype(root)> printQue{ root };
	int lvNodeNum = 0;

	cout << "\nBinary Tree:\n";
	while (!printQue.empty())
	{
		lvNodeNum = printQue.size();

		while (--lvNodeNum >= 0)
		{
			root = printQue.front();
			printQue.pop_front();

			cout << root->data;
			if (root->dad)
				cout << '(' << root->dad->data << (root->dad->left == root ? " L" : " R") << "), ";

			if (root->left)
				printQue.emplace_back(root->left);
			if (root->right)
				printQue.emplace_back(root->right);
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	auto root = CreateTree<shared_ptr<TreeNode<int>>>({
		N(1, int), // 1
		N(2, int),N(3, int), // 2
		N(4, int),N(5, int),N(6, int),N(7, int), // 4
		nullptr,nullptr,N(8, int),N(9, int),nullptr,nullptr,nullptr,N(10, int), // 8
		});
	PrintTree(root);

	auto paths = BinaryTreePaths_DFS(root);
	cout << "\n\n[Solution DFS] Binary Tree Paths:\n";
	for (auto itr = paths.begin(); itr != paths.end(); ++itr)
	{
		cout << *itr << endl;
	}

	vector<string>().swap(paths);
	paths = BinaryTreePaths_BFS(root);
	cout << "\n\n[Solution BFS] Binary Tree Paths:\n";
	for (auto itr = paths.begin(); itr != paths.end(); ++itr)
	{
		cout << *itr << endl;
	}

	cout << endl << endl;
	return 0;
}
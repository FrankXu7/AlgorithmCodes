/**************************************************************************************************
 * 【题目描述】
 * 给定一颗二叉树，计算所有左【叶子】节点之和。
 * 
 * 【输入】
 * 二叉树数据源：[3,9,20,null,null,15,7]
 * 【输出】
 * 所有左叶子之和：24
 * 
 * 【解题思路】
 * 
 * 二叉树的BFS和DFS详解，参考之前的笔记：https://zhuanlan.zhihu.com/p/386595111
 * 
 * 方法一：
 * BFS遍历，访问每个节点时，若存在左子节点，且为叶子节点，则加入到总和中，遍历完成后返回总和。
 * 
 * 方法二：
 * DFS遍历之前序遍历（DLR），利用一个栈遍历所有元素，入栈时为“右左”顺序这样保证出栈的时候是“左右”顺序，符
 * 合前序遍历根左右的特性。访问到每个节点时，若存在左子节点，且为叶子节点，则加入到总和中，遍历完成后返回
 * 总和。
 * 
 * 方法三：
 * DFS遍历之中序遍历（LDR），利用一个栈来遍历所有节点，初始先将从根节点开始顺着最左侧的路径入栈所有左子节
 * 点，然后再出栈节点，当出栈的节点存在右节点时，从右节点开始顺着其最左侧的路径入栈所有左子节点。对每个出
 * 栈节点，若存在左子节点，且为叶子节点，则加入到总和中，遍历完成后返回总和。
 * 
 * 方法四：
 * DFS遍历只后续遍历（LRD），和中序遍历过程基本一致，唯一不同的就是，在出栈节点时，如果即将要出栈的节点存
 * 在右节点，则先不出栈，而是把当前节点从其右节点开始顺着右节点最左侧的路径入栈所有左子节点。为了不让再次
 * 出栈当前节点时重复操作，需要一个 lastPopNode 来保存上一次被出栈的节点，如果当前遍历的节点存在右子节点，
 * 但其右子节点又等于 lastPopNode，标识当前节点的右子节点的最左侧的路径已经处理过了。同理，对每个出栈节点，
 * 若存在左子节点，且为叶子节点，则加入到总和中，遍历完成后返回总和。
 * 
 * 
 * 【解题分析】
 * 
 * 复杂度分析总结：每个节点访问一次，故时间复杂度均为O(N)，特别注意的是因为后续遍历中存在右节点的节点
 * 会被二次访问，但不需要额外存储两次。而空间复杂度最差的情况为单链表，需要O(N)的复杂度。
 * 
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
 * 空间复杂度：O(N)
 * 
 * @author FrankX
 * @date 2021-10-29
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
using namespace std;

template<typename DataType>
struct TreeNode
{
	DataType data;
	shared_ptr<TreeNode<DataType>> dad; // 算法本身不需要父节点，仅用于打印树结构 
	decltype(dad) left;
	decltype(dad) right;

	TreeNode(DataType _data) { data = _data; }
};

// 方便声明一个节点 
#define N(val, DataType) (make_shared<TreeNode<DataType>>(val))
// 方便中序和后续遍历时，一直入栈最左侧节点直到叶子节点 
#define PUSH_LEFT(node, stk) \
while (node) \
{ \
	stk.emplace(node); \
	node = node->left; \
}

/**
 * @brief 辅助函数，依据数组序列生成一颗二叉树
 * @param dataArr 二叉树节点数据源，右值引用
 * @return 返回生成的二叉树头节点
 */
template<typename NodeType>
NodeType CreateTree(vector<NodeType>&& dataArr)
{
	unsigned int dataSize = dataArr.size(),
		dadIdx = 0, leftIdx = 0, rightIdx = 0;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		// 找爹 
		if (idx > 0 && dataArr[idx])
		{
			dadIdx = (idx - 1) / 2;
			dataArr[idx]->dad = dataArr[(idx - 1) / 2];
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
 * @param root 二叉树根节点
 */
template<typename NodeType>
void PrintTree(NodeType root)
{
	deque<NodeType> printQue;
	deque<NodeType> cacheQue{ root };
	NodeType node = nullptr;

	while (!cacheQue.empty())
	{
		printQue.swap(cacheQue);
		while (!printQue.empty())
		{
			node = printQue.front();
			printQue.pop_front();

			cout << node->data;
			if (node->dad)
				cout << "(" << node->dad->data
				<< (node->dad->left == node ? " L" : " R") << "), ";

			if (node->left)
				cacheQue.emplace_back(node->left);
			if (node->right)
				cacheQue.emplace_back(node->right);
		}
		cout << endl;
	}
}


template<typename NodeType>
int SumOfLeftLeaves_BFS(NodeType root)
{
	deque<NodeType> que{ root };
	NodeType node = nullptr;
	int leftLeavesSum = 0;

	while (!que.empty())
	{
		node = que.front();
		que.pop_front();

		if (node->left)
		{
			// 确认是否为叶子节点 
			if (!node->left->left)
				leftLeavesSum += node->left->data;
			que.emplace_back(node->left);
		}
		if (node->right)
			que.emplace_back(node->right);
	}

	return leftLeavesSum;
}

template<typename NodeType>
int SumOfLeftLeaves_DLR(NodeType root)
{
	stack<NodeType> stk;
	int leftLeavesSum = 0;

	stk.emplace(root);
	NodeType node = nullptr;

	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();

		// 按“右左”入栈，出栈顺序就是“左右”，符合前序遍历“左右根”的特性 
		if (node->right)
			stk.emplace(node->right);
		if (node->left)
		{
			// 确认是否为叶子节点 
			if (!node->left->left)
				leftLeavesSum += node->left->data;
			stk.emplace(node->left);
		}
	}

	return leftLeavesSum;
}

template<typename NodeType>
int SumOfLeftLeaves_LDR(NodeType root)
{
	stack<NodeType> stk;
	int leftLeavesSum = 0;

	// 先将初始的从根节点开始的最左侧节点入栈 
	PUSH_LEFT(root, stk);

	NodeType node = nullptr;
	while (!stk.empty())
	{
		node = stk.top();
		stk.pop();

		if (node->left && !node->left->left)
			leftLeavesSum += node->left->data;

		// 出栈节点存在右节点，将右节点和其最左侧分支入栈 
		if (node->right)
		{
			// 赋值到一个变量，避免直接传递node->right导致树结构改变 
			node = node->right;
			PUSH_LEFT(node, stk);
		}
	}

	return leftLeavesSum;
}

template<typename NodeType>
int SumOfLeftLeaves_LRD(NodeType root)
{
	stack<NodeType> stk;
	int leftLeavesSum = 0;

	// 先将初始的从根节点开始的最左侧节点入栈 
	PUSH_LEFT(root, stk);

	NodeType node = nullptr;
	NodeType lastPopNode = nullptr;
	while (!stk.empty())
	{
		node = stk.top();

		/**
		 * 出栈节点存在右节点，且右节点不等于上一个出栈节点，标识遇到新节点，
		 * 从该节点开始的最左侧节点入栈，这也是和中序遍历算法中不同之处；
		 */
		if (node->right && node->right != lastPopNode)
		{
			// 赋值到一个变量，避免直接传递node->right导致树结构改变 
			node = node->right;
			PUSH_LEFT(node, stk);
			continue;
		}

		lastPopNode = node;

		if (node->left && !node->left->left)
			leftLeavesSum += node->left->data;

		stk.pop();
	}

	return leftLeavesSum;
}

int main(int argc, char* argv[])
{
	auto root = CreateTree<shared_ptr<TreeNode<int>>>({
		N(3, int),
		N(9, int),N(20, int),
		N(10, int),nullptr,N(15, int),N(7, int),
		});

	cout << "Binary tree struct: \n";
	PrintTree(root);

	cout << "\n\n[Solution BFS] The sum of all left leaves: " << SumOfLeftLeaves_BFS(root);

	cout << "\n\n[Solution DLR] The sum of all left leaves: " << SumOfLeftLeaves_DLR(root);

	cout << "\n\n[Solution LDR] The sum of all left leaves: " << SumOfLeftLeaves_LDR(root);

	cout << "\n\n[Solution LRD] The sum of all left leaves: " << SumOfLeftLeaves_LRD(root);

	cout << "\n\n\nCheck Binary tree struct whether to change: \n";
	PrintTree(root);

	cout << endl << endl;
	return 0;
}
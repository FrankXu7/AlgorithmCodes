/**************************************************************************************************
 * 【题目描述】
 * 给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素），可能存在多个。
 *
 * 【输入】
 * BST=[5, 3, 9, 2, null, null, 9]
 * 结构为：
 *       5
 *   3       9
 * 2  3  null   9
 * 【输出】
 * 众数：[3, 9]
 *
 * 【解题思路】
 * 方法一：
 * 统计后遍历，用一个无序map统计各个元素出现的个数，并记录最高出现次数，然后遍历这个统计的无序map，找到
 * 统计次数和记录的最高出现次数相同的元素，即为众数之一。
 * 
 * 方法二：
 * 因为BST的节点之间是有大小关系的，如果将BST节点按中序遍历输出，得到的是一个有序的序列，所以相同的节点在
 * 该序列中必然是相邻元素。中序遍历一般可以用递归或栈迭代遍历来实现，但它们和方法一类似，都需要线性的空间
 * 复杂度，为了达到常数级别的空间复杂度，可以使用Morris遍历，Morris遍历的本质在于利用了BST中已经申请了内
 * 存，但并没有数据的叶子节点和单分支的空节点，等价于将空间的需求转移到必须存在的空节点中。
 * 
 * Morris遍历笔记：https://zhuanlan.zhihu.com/p/389024066
 * 按照Morris遍历的特性，对于局部三节点组成的子树来说，遍历到左右节点时，都需要执行统计比较，而对于根节点，
 * 则需要在第二次被访问时执行统计比较，保证中序遍历“根左右”的特性。
 * 
 * 对于统计比较，如果上一个节点和当前节点的值相等，则统计自加，否则就是遇见不同的节点了，将上一个节点赋值
 * 为当前节点。而后比较上一个节点（有可能赋值的是当前节点）和记录的众数节点的统计情况，会出现三种情况：
 * （1）上一个节点的次数小于记录的众数节点次数，自然忽略，继续执行；
 * （2）上一个节点和记录的众数节点次数相同，表示上一个节点有可能也是众数，推入返回数组；
 * （3）上一个节点次数大于记录的众数节点次数，即众数有更新，清空之前的返回数组，推入新的众数节点；
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-12-23
 *************************************************************************************************/
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;

template<typename T>
struct TreeNode
{
	T data;
	shared_ptr<TreeNode<T>> left;
	shared_ptr<TreeNode<T>> right;
	shared_ptr<TreeNode<T>> dad; // 算法本身不需要，只是用于打印树结构 

	TreeNode(T val)
	{
		data = val;
		left = right = dad = nullptr;
	}
};

#define N(T, val) (make_shared<TreeNode<T>>(val))

vector<int> FindModeInBST_1(shared_ptr<TreeNode<int>> root)
{
	vector<int> modeArr;
	if (!root) return modeArr;

	// 统计各个节点元素的数量 
	unordered_map<int, int> modeCount;
	// 使用BFS遍历树节点 
	deque<decltype(root)> que{ root };
	// 标记数据最大值 
	int maxNum = 0;

	decltype(root) node = nullptr;
	while (!que.empty())
	{
		root = que.front();
		que.pop_front();

		if (root->left) que.emplace_back(root->left);
		if (root->right) que.emplace_back(root->right);

		if (++modeCount[root->data] > maxNum)
			maxNum = modeCount[root->data];
	}

	for (auto& pair : modeCount)
	{
		if (pair.second == maxNum)
			modeArr.emplace_back(pair.first);
	}

	return modeArr;
}

vector<int> FindModeInBST_2(shared_ptr<TreeNode<int>> root)
{
	vector<int> modeArr;

	int lastCount = 0, maxCount = 0;
	decltype(root) lastNode = nullptr, maxNode = nullptr;

	decltype(root) pCur = root;
	decltype(root) pMostRight = nullptr;

	auto callback = [&lastNode, &lastCount, &maxNode, &maxCount, &modeArr](decltype(root) curNode) {
		if (lastNode && curNode->data == lastNode->data)
		{
			++lastCount;
		}
		else
		{
			lastCount = 1;
			lastNode = curNode;
		}

		if (!maxNode || lastCount >= maxCount)
		{
			/**
			 * 满足条件 lastCount > maxCount 时，表示 modeArr 记录的都不是众数节点了，因为发现了出现次
			 * 数更多的节点，故需要清空 modeArr，至于判断 maxNode 是因为首次执行时，maxNode为空，此时的
			 * modeArr 必然为空，减少一次数组操作。
			 * 
			 * 这里不使用 vector<int>().swap(modeArr) 是考虑到可能二叉树中所有节点元素值相同，
			 * 也避免了频繁的内存操作。
			 */
			if (maxNode && lastCount > maxCount) modeArr.clear();

			maxCount = lastCount;
			maxNode = lastNode;

			modeArr.emplace_back(maxNode->data);
		}
	};

	// Morris 中序遍历 
	while (pCur)
	{
		if (!pCur->left)
		{
			callback(pCur);

			pCur = pCur->right;
			continue;
		}

		pMostRight = pCur->left;
		// pMostRight->right != pCur 避免右移到回溯节点，造成死循环 
		while (pMostRight && pMostRight->right && pMostRight->right != pCur)
		{
			pMostRight = pMostRight->right;
		}

		if (!pMostRight->right)
		{
			pMostRight->right = pCur;
			pCur = pCur->left;
		}
		else
		{
			// pCur第二次访问时执行统计比较，保证中序遍历“根左右”的特性 
			callback(pCur);

			pMostRight->right = nullptr;
			pCur = pCur->right;
		}
	}

	return modeArr;
}

/**
 * @brief 辅助函数，生成一颗二叉树
 * @param dataArr 二叉树节点顺序，BST结构
 * @return 返回二叉树的根节点
 */
template<typename DataType>
shared_ptr<TreeNode<DataType>> BuildTree(vector<shared_ptr<TreeNode<DataType>>>&& dataArr)
{
	if (dataArr.empty() || !dataArr[0]) return nullptr;
	shared_ptr<TreeNode<DataType>> root = dataArr[0];

	unsigned int leftIdx = 0, rightIdx = 0;
	for (unsigned int idx = 0; idx < dataArr.size(); ++idx)
	{
		if (!dataArr[idx]) continue;

		// 找爹 
		if (idx > 0)
			dataArr[idx]->dad = dataArr[static_cast<unsigned int>((idx - 1) / 2)];

		// 找俩儿子 
		leftIdx = idx * 2 + 1;
		rightIdx = leftIdx + 1;

		if (leftIdx < dataArr.size() && dataArr[leftIdx])
			dataArr[idx]->left = dataArr[leftIdx];
		if (rightIdx < dataArr.size() && dataArr[rightIdx])
			dataArr[idx]->right = dataArr[rightIdx];
	}

	return root;
}

/**
 * @brief 辅助函数，打印一颗二叉树
 * @param root 数根节点
 */
template<typename DataType>
void PrintTree(shared_ptr<TreeNode<DataType>> root)
{
	if (!root) return;

	shared_ptr<TreeNode<DataType>> node = nullptr;
	deque<decltype(node)> printQue;
	decltype(printQue) tempQue{ root };

	while (!tempQue.empty())
	{
		printQue.swap(tempQue);
		while (!printQue.empty())
		{
			node = printQue.front();
			printQue.pop_front();

			cout << node->data;
			if (node->dad)
				cout << '(' << node->dad->data << (node->dad->left == node ? " L), " : " R), ");

			if (node->left) tempQue.emplace_back(node->left);
			if (node->right) tempQue.emplace_back(node->right);
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	shared_ptr<TreeNode<int>> root = BuildTree<int>({
	N(int, 5),
	N(int, 3),N(int, 9),
	N(int, 2),N(int, 3),nullptr,N(int, 9),
	});
	/**

	N(int, 2),N(int, 4),N(int, 7),N(int, 9),
	N(int, 1),nullptr,nullptr,nullptr,nullptr,N(int, 7),nullptr,nullptr
	 */
	cout << "The given BST:\n";
	PrintTree<int>(root);

	vector<int> modeArr1 = FindModeInBST_1(root);
	cout << "\n\n[Solution 1] The mode number array:\n";
	for (auto& num : modeArr1) cout << num << ", ";

	vector<int> modeArr2 = FindModeInBST_2(root);
	cout << "\n\n[Solution 2] The mode number array:\n";
	for (auto& num : modeArr2) cout << num << ", ";

	cout << endl << endl;
	return 0;
}
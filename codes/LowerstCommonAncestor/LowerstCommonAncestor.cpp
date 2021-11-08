/**************************************************************************************************
 * 【题目描述】
 * 给定一颗二叉搜索树，找出给定的两个节点的最近公共祖先节点。规定所有节点的数值都是唯一的，两个节点为不同
 * 节点。
 * 
 * 二叉树根节点到任意节点路径都是唯一的，所以任意两个在二叉树的不同节点，在它们的路径上必定有相同的节点，
 * 找出这些重合节点中深度最大的，即为所求最近公共节点。
 *
 * 【输入】
 * Tree Nodes Array = [6,2,8,0,4,7,9,null,null,3,5,null,null,null,10]
 * 【输出】
 * 最近公共祖先节点：8
 *
 * 【解题思路】
 * 方法一：
 * 两个节点到根节点的路径是唯一的，所以可以从上到下BFS遍历，先找出两个节点路径上的所有节点，暂存于队列。
 * 然后依次出队两个队列节点，如果出队节点相同，则是给定节点的公共祖先，因为是按BFS遍历的，所以深度越大的
 * 越晚入队和出队，当遇到两个出队节点不同时，上一次出队的相同节点即为它们的最近公共祖先。在找节点路径的遍
 * 历中，因为是BST树，所以查找节点小于当前遍历节点时，则向左遍历，否则向右遍历。
 * 
 * 方法二：
 * 因为两个节点的路径都是从根节点出发，所以可以从根节点开始，就通过BFS遍历一层一层比较，这样只需要一次循
 * 环，且不需要额外的辅助空间，当遍历到某个节点时，会遇到以下情况：
 * （1）如果给定的俩节点都小于当前遍历节点，那它们的公共祖先肯定在左侧分支上，继续往左侧查找；
 * （2）反之，如果俩节点都大于当前遍历节点，那它们的公共祖先必然在右侧分支上，则向右侧查找；
 * （3）不是上面两种情况，那意味着给的俩节点以当前遍历节点为界，分散在了两侧分支（也包含其中某个节点就是
 *      当前遍历的节点这种情况），这就表示了当前遍历的节点就是他俩的最近公共祖先了。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际上要经历三次循环，查找两条路径各需循环一次，比较路径需要循环一次，它们的平均复杂
 *             度都是O(logN)，故平均复杂度之和为log(3*logN)，最差情况为单链表O(3N)
 * 空间复杂度：O(N) 存储两条路径节点的复杂度都是O(logN)，复杂度之和为O(2*logN)，最差情况为单链表O(2N)
 * 方法二：
 * 时间复杂度：O(N) 平均复杂度为O(logN)，最差情况是单链表O(N）
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-10
 **************************************************************************************************/
#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <unordered_set>
using namespace std;

template<typename DataType>
struct TreeNode
{
	DataType data;
	shared_ptr<TreeNode<DataType>> left;
	decltype(left) right;
	decltype(left) dad; // 算法逻辑不需要，仅用于打印树的结构 

	TreeNode(DataType _data)
	{
		data = _data;
	}
};
#define N(val, DataType) (make_shared<TreeNode<DataType>>(val))

template<typename sp_NodeType, typename DataType>
sp_NodeType LowerstCommonAncestor_1(sp_NodeType& root, DataType node1, DataType node2)
{
	// 二叉树中根节点必定是所有节点的祖先节点
	sp_NodeType spAncestor = root;

	// 从根节点到节点1的路径 
	deque<sp_NodeType> route1;
	while (spAncestor)
	{
		route1.emplace_back(spAncestor);

		if (node1 < spAncestor->data)
			spAncestor = spAncestor->left;
		else if (node1 > spAncestor->data)
			spAncestor = spAncestor->right;
		else
			spAncestor.reset();
	}

	// 从根节点到节点2的路径 
	deque<sp_NodeType> route2;
	spAncestor = root;
	while (spAncestor)
	{
		route2.emplace_back(spAncestor);

		if (node2 < spAncestor->data)
			spAncestor = spAncestor->left;
		else if (node2 > spAncestor->data)
			spAncestor = spAncestor->right;
		else
			spAncestor.reset();
	}

	// 找到公共祖先，即最后一对相同路径节点 
	sp_NodeType spNode1;
	sp_NodeType spNode2;
	while (!route1.empty() && !route2.empty())
	{
		spNode1 = route1.front();
		route1.pop_front();
		spNode2 = route2.front();
		route2.pop_front();

		// 题意要求不存在数值相同的节点，所以spNode1和spNode2数值相同必为同一个节点 
		if (spNode1->data == spNode2->data)
			spAncestor = spNode1;
		else
			break; // 跳出时，在上一次循环已经保存了相同节点，即为最近公共祖先节点 
	}

	return spAncestor;
}

template<typename sp_NodeType, typename DataType>
sp_NodeType LowerstCommonAncestor_2(sp_NodeType& root, DataType node1, DataType node2)
{
	// 二叉树中根节点必定是所有节点的祖先节点
	sp_NodeType spAncestor = root;

	while (spAncestor)
	{
		if (node1 < spAncestor->data && node2 < spAncestor->data)
			spAncestor = spAncestor->left; // 俩节点都小于当前节点，left指向必不为空 
		else if (node1 > spAncestor->data && node2 > spAncestor->data)
			spAncestor = spAncestor->right; // 俩节点都大于当前节点，right指向必不为空 
		else
			break;
	}

	return spAncestor;
}

/**
 * @brief 依据数组数据生成一颗二叉树，数组内节点数据按照BFS排序，空节点也占用一个元素位置，
 * 则二叉树的节点有如下性质：
 *	父节点下标：(idx - 1) / 2
 *	左孩子下标：idx * 2 + 1
 *	有孩子下标：idx * 2 + 2（左孩子下标+1）
 * @param arr 右值引用，节点数据数组
 * @param head 左值引用，为二叉树根节点，因为按照BFS放置，所以数组首元素就是二叉树根节点
 */
template<typename sp_NodeType>
void CreateTree(vector<sp_NodeType>& arr, sp_NodeType& root)
{
	if (arr.empty())
		return;
	else
		root = arr[0];

	auto dataSize = arr.size();

	unsigned int dadIdx = 0;
	unsigned int leftIdx = 0;
	unsigned int rightIdx = 0;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		if (!arr[idx]) continue;

		// 非根节点才会有父节点 
		if (idx > 0)
		{
			dadIdx = static_cast<unsigned int>((idx - 1) / 2);
			// dadIdx肯定比当前的idx小，所以肯定不会越过上界，所以判断下界即可 
			if (dadIdx >= 0) arr[idx]->dad = arr[dadIdx];
		}

		leftIdx = idx * 2 + 1;
		if (leftIdx < dataSize) arr[idx]->left = arr[leftIdx];

		rightIdx = leftIdx + 1;
		if (rightIdx < dataSize) arr[idx]->right = arr[rightIdx];
	}
}

/**
 * @brief 打印一颗二叉树
 * @param root 二叉树根节点
 */
template<typename sp_NodeType>
void PrintTree(sp_NodeType& root)
{
	if (!root) return;

	deque<sp_NodeType> printQue{ root };
	decltype(printQue) tempQue;
	sp_NodeType sp;

	cout << "Binary Tree Struct:\n";
	do
	{
		while (!printQue.empty())
		{
			sp = printQue.front();
			printQue.pop_front();

			cout << sp->data;
			if (sp->dad)
			{
				if (sp->dad->left == sp)
					cout << "(" << sp->dad->data << " L), ";
				else
					cout << "(" << sp->dad->data << " R), ";
			}

			if (sp->left)
				tempQue.emplace_back(sp->left);
			if (sp->right)
				tempQue.emplace_back(sp->right);
		}

		cout << endl;
		printQue.swap(tempQue);

	} while (!printQue.empty());
}

int main(int argc, char* argv[])
{
	shared_ptr<TreeNode<int>> root;
	vector<decltype(root)> arr{
		N(6,int),
		N(2,int), N(8,int),
		N(0,int), N(4,int), N(7,int), N(9,int),
		nullptr,  nullptr,  N(3,int), N(5,int), nullptr, nullptr, nullptr, N(10,int),
	};

	CreateTree(arr, root);
	PrintTree(root);

	decltype(root) node1 = arr[5];
	decltype(root) node2 = arr[14];
	cout << "\n\nThe given two nodes: " << node1->data << ", " << node2->data;

	cout << "\n\n[Solution 1]: The lowerst common ancestor of BST: "
		<< LowerstCommonAncestor_1(root, node1->data, node2->data)->data;

	cout << "\n\n[Solution 2]: The lowerst common ancestor of BST: "
		<< LowerstCommonAncestor_2(root, node1->data, node2->data)->data;

	cout << endl << endl;
	return 0;
}
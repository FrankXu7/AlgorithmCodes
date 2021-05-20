/**************************************************************************************************
 * 【题目描述】
 * 删除一个升序列表中的重复元素。
 *
 * 【输入】
 * list=[1,2,3,3,3,4,5]
 *
 * 【输出】
 * newList=[1,2,3,4,5]
 *
 * 【解题思路】
 * 因为链表是升序的，所以有重复的元素必定相邻。
 * 如果当前遍历节点的数据，等于下一个节点的数据，则当前节点的next，保存为下一个节点的next；
 * 即将下一个被删除的节点移除在链表关系之外。
 *
 * 需要注意的是：
 * （1）释放删除节点的内存，原则为同函数申请和释放，传入指针引用指向删除节点组合而成的链表。
 * （2）删除节点组合而成的链表，最后一个节点一定要置空，否则可能删除结果链表中的节点。
 *
 *
 * @author FrankX
 * @date 2021-04-16
 **************************************************************************************************/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode<T>* dad;
	TreeNode<T>* left;
	TreeNode<T>* right;

	TreeNode<T>(T _data)
	{
		data = _data;
		dad = left = right = nullptr;
	}
};

void DeleteTree(TreeNode<int>*& treeRoot)
{

}

void PrintTree() {

}

int main()
{
	return 0;
}

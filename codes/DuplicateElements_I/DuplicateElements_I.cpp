/**************************************************************************************************
 * 【题目描述】
 * 判断一个整数数组是否存在相同元素，存在返回true，不存在则返回false; 特别注意，数组并未说是有序的！
 * 
 * 
 * 【输入】
 * array = 1,2,3,1
 * 【输出】
 * 返回true
 * 
 * 【解题思路】
 * 利用 unordered_set 容器，判断当前遍历的元素是否已经存在于容器，若存在，表示已经存在相同的元素，若不存
 * 在于容器，则将当前元素放入容器。
 * 
 * 题意的数组并非有序数组，也可以将其先行排序，然后利用快慢指针来判断，可参考：DeleteRepeatNumber.cpp
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 *
 * @author FrankX
 * @date 2021-08-30
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool DuplicateElements_I(const vector<int>& arr)
{
	unordered_set<int> tempGather;

	for (vector<int>::const_iterator itr = arr.begin(); itr != arr.end(); ++itr)
	{
		if (tempGather.find(*itr) != tempGather.end())
			return true;
		else	
			tempGather.insert(*itr);
	}

	return false;
}

int main(int argc, char** argv)
{
	vector<int> arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 8};
	cout << "Array data:\n";
	for (vector<int>::iterator itr = arr.begin(); itr != arr.end(); ++itr)
		cout << *itr << ", ";

	cout << "\n\n[Solution 1] Exist duplicate elements? " << (DuplicateElements_I(arr) ? "YES\n" : "NO\n");

	cout << endl << endl;
	return 0;
}
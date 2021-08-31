/**************************************************************************************************
 * 【题目描述】
 * 判断一个整数数组是否存在相同元素，同时给定一个整数 idxDifference，如果这几个相同元素的下标的差值，
 * 存在不超过给定的整数 idxDifference，则返回true，反之返回false；
 * 
 * 【输入】
 * Array=[1,2,3,1]    idxDifference=3
 * 【输出】
 * 返回true
 * 
 * 【解题思路】
 * 方法一：
 * 最先最直观想到的就是线性搜索（暴力解法），遍历数组中的每个元素，并且遍历的下标上限为当前下标加上给定的
 * 最大下标差值，如果在限定范围的遍历过程中出现元素数值相等，则返回ture；
 * 
 * 方法二：
 * 因为给定了一个最大下标差值，可以利用“窗口滑动”思想，使用无序的set集合，如果将不重复的数组元素放入无序set集合，
 * 依据题意要求，可以得出无序set集合内的元素数量，必然不会超过给定的最大下标差值，所以，当放入一个元素导致
 * 无序set集合容量超过给定的最大下标差值时，需要将首元素移除，大致过程：
 * （1）判断当前遍历的元素如果存在于无序set集合，表示集合中已经存在与当前遍历元素数值相同的元素，且下标差值
 *		在给定范围内，直接返回true，结束算法；
 * （2）如果当前遍历元素在无序set集合不存在，则将元素放入集合，放入后需要进一步判断容器元素数量是否超过
 *		最大下标差值，若超过，需要将首元素移除。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N*min(N,K)) N为数组长度，K为给定的最大下标差值，对每个元素的判断遍历上限就是 min(N,K)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(min(N,k)) N为数组长度，K为给定的最大下标差值，无序set集合元素最大值即为 min(N,k)
 * 
 * @author FrankX
 * @date 2021-08-31
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool DuplicateElements_II_1(const vector<int>& arr, const unsigned int& idxDifference)
{
	unsigned int dataSize = arr.size();
	unsigned int cycleBoundary = 0;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		// 限定下标上限不超过给定的最大下标差值 idxDifference 
		cycleBoundary = idx + idxDifference;
		if (cycleBoundary >= dataSize) cycleBoundary = dataSize - 1;

		for (unsigned int n = idx + 1; n <= cycleBoundary; ++n)
		{
			if (arr[idx] == arr[n])
			{
				return true;
			}
		}
	}

	return false;
}

bool DuplicateElements_II_2(const vector<int>& arr, const unsigned int& idxDifference)
{
	unordered_set<unsigned int> gather;

	for (vector<int>::const_iterator itr = arr.begin(); itr != arr.end(); ++itr)
	{
		if (gather.find(*itr) == gather.end())
		{
			gather.insert(*itr);

			// 这一步保证了重复元素的下标差值不会超过给定的最大下标差值 
			if (gather.size() > idxDifference)
			{
				gather.erase(gather.begin());
			}
		}
		else
		{
			// 如果在集合中找到了重复元素，则它们之间的下标差值必然小于等于给定的最大下标差值 
			return true;
		}
	}

	return false;
}

int main(int artc, char** argv)
{
	vector<int> arr = { 1,2,3,1 };
	unsigned int idxDifference = 3;

	cout << "Array data: \n";
	for (vector<int>::iterator itr = arr.begin(); itr != arr.end(); ++itr)
	{
		cout << *itr << ", ";
	}
	cout << "\nMaximum index difference: " << idxDifference;

	cout << "\n\n[Solution 1] Exist the duplicate elements? " << (DuplicateElements_II_1(arr, idxDifference) ? "YES\n" : "NO\n");

	cout << "\n\n[Solution 2] Exist the duplicate elements? " << (DuplicateElements_II_2(arr, idxDifference) ? "YES\n" : "NO\n");

	cout << endl << endl;
	return 0;
}
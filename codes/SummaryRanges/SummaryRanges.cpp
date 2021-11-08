/**************************************************************************************************
 * 【题目描述】
 * 给定一个无重复元素的有序数组，找出数组中的最小有序区间，即数组中，存在一个子数组，它们是按1递增(减)的，
 * 如果一个子数组和它左右两侧的元素差值都大于1，则单独输出。
 * 
 *
 * 【输入】
 * No Duplicate and ASC Array = [1,2,3,6]
 * 【输出】
 * Summary Ranges Array = ["1->3", "6"]
 *
 * 【解题思路】
 * 一次遍历即可，因为最小有序子数组中元素差值都是1，所以如果遇到与下一个元素的差值大于1，则输出当前区间，
 * 当然，如果下一个元素越界，就直接输出了。使用一个 pair 结构来保存子数组边界值，初始时它们都等于子数组的
 * 首元素。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-03
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void SummaryRanges(const vector<int>& arr, vector<string>& ranges)
{
	if (arr.empty()) return;

	unsigned int dataSize = arr.size(), nextIdx = 0;
	pair<int, int> border{ arr[0], arr[0] };

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		nextIdx = idx + 1;
		if (nextIdx == dataSize || border.second + 1 != arr[nextIdx])
		{
			if (border.first == border.second)
				ranges.emplace_back(to_string(border.first));
			else
				ranges.emplace_back(to_string(border.first) + "->" + to_string(border.second));

			// 保存下一轮 
			if (nextIdx < dataSize)
				border.first = border.second = arr[nextIdx];
		}
		else
			++border.second;
	}
}

int main(int argc, char** argv)
{
	vector<int> arr{ 0,1,2,4,5,7,8,10 };
	vector<string> ranges;

	cout << "Array data (No duplicate element, ASC order) :\n";
	for (vector<int>::iterator itr = arr.begin(); itr != arr.end(); ++itr)
		cout << *itr << ", ";

	SummaryRanges(arr, ranges);

	cout << "\n\nAfter summary ranges:\n";
	for (vector<string>::iterator itr = ranges.begin(); itr != ranges.end(); ++itr)
		cout << *itr << endl;

	cout << endl << endl;
	return 0;
}
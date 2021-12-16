/**************************************************************************************************
 * 【题目描述】
 * 给定一个二进制数组， 计算其中最大连续 1 的个数。数组元素只能是 0 或 1 两种情况。
 *
 * 【输入】
 * binaryNums = [1,1,1,0,1,1,1,1,0,0,1,1];
 * 【输出】
 * 最大连续1的个数：4
 *
 * 【解题思路】
 * 一次遍历，遇到1统计之，否则和已经保存过的最大连续1的个数进行比较以判断是否要更新。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-12-16
 *************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int MaxConsecutiveOne(vector<int>& binaryNums)
{
	int oneCount = 0;
	int curCount = 0;
	for (vector<int>::iterator itr = binaryNums.begin(); itr != binaryNums.end(); ++itr)
	{
		if (*itr == 1)
		{
			++curCount;
		}
		else
		{
			if (curCount >= oneCount)
				oneCount = curCount;

			curCount = 0;
		}
	}

	return oneCount;
}

int main(int argc, char** argv)
{
	vector<int> binaryNums{ 1,1,1,0,1,1,1,1,0,0,1,1 };
	cout << "The give binary array: \n";
	for (auto& num : binaryNums)
		cout << num << ", ";

	cout << "\n\nThe max consecutive number one: " << MaxConsecutiveOne(binaryNums);

	cout << endl << endl;
	return 0;
}
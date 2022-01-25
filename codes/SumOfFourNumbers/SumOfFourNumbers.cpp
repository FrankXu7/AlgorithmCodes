/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数数组 nums，和一个目标值 targetNum，找到数组中的一个四元组，使得四元组求和会等于 targetNum，
 * 返回所有不重复的四元组，在同一个四元组中，数组元素不能重复使用。
 *
 * 题中给出的数组元素和目标值，取值区间为：[-10^9, 10^9]
 *
 * 【输入】
 * nums = [ 6,6,6,6,6,6,6,6,6,6,6,6 ]; targetNum = 24;
 * 【输出】
 * ansArr = [ [ 6,6,6,6 ] ];
 *
 * 【解题思路】
 * 和三数之和类似，两层遍历以固定四元组中前两个数，然后用双指针找确定剩下的两个数，这里有两个注意点：
 * （1）按题意，整数取值区间为 [-10^9, 10^9]，所以要考虑四元组求和后整数的越界问题（转 long long 计算）；
 * （2）题意要求不能出现重复的四元组，所以各层循环在遍历到当前的元素时，若等于上一个元素，需要排除掉，避
 *      免得到重复的四元组；
 *
 * 【解题分析】
 * 时间复杂度：O(N^3) 实际还要加上排序的复杂度 NlogN
 * 空间复杂度：O(logN) 排序的复杂度，并未算上返回结果，也未考虑排序对原数组的影响
 *
 * @author FrankX
 * @date 2021-01-25
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> SumOfFourNumbers(vector<int>& nums, int targetNum)
{
	if (nums.size() < 4) return {};

	vector<vector<int>> ansArr;

	unsigned int leftIdx = 0, rightIdx = 0, arrSize = nums.size();
	// 题意整数取值区间为 [-10^9, 10^9]，故需要处理可能的整数越界问题 
	long long tempSum = 0;

	sort(nums.begin(), nums.end());
	for (unsigned int first = 0; first < arrSize - 3; ++first)
	{
		// 题意要求四元组不重复，当前元素等于前一个元素时，会得到重复的四元组，排除之 
		if (first > 0 && nums[first] == nums[first - 1])
			continue;

		for (unsigned int second = first + 1; second < arrSize - 2; ++second)
		{
			if (second > first + 1 && nums[second] == nums[second - 1])
				continue;

			leftIdx = second + 1;
			rightIdx = arrSize - 1;

			while (leftIdx < rightIdx)
			{
				/**
				 * 下面的两个针对左/右指针的分支是为了排除掉重复的四元组，在其它三个值确定的情况下，
				 * 左/右指针指向的相等元素，只使用其中一个，具体就是首个左/右指向的相等元素
				 */
				if (leftIdx > second + 1 && nums[leftIdx] == nums[leftIdx - 1])
				{
					++leftIdx;
					continue;
				}
				else if (rightIdx < arrSize - 1 && nums[rightIdx] == nums[rightIdx + 1])
				{
					--rightIdx;
					continue;
				}

				tempSum = static_cast<long long>(nums[first]) +
					nums[second] + nums[leftIdx] + nums[rightIdx];

				if (tempSum == targetNum)
				{
					ansArr.emplace_back(vector<int>({
						nums[first], nums[second], nums[leftIdx], nums[rightIdx] }));

					++leftIdx;
					--rightIdx;
				}
				else if (tempSum < targetNum)
					++leftIdx;
				else
					--rightIdx;
			}
		}
	}

	return ansArr;
}

int main(int argc, char* argv[])
{
	vector<int> nums = { 6,6,6,6,6,6,6,6,6,6,6,6 };
	int targetNum = 24;
	cout << "The given number's array:\n";
	for (int& num : nums) cout << num << ", ";
	cout << "\nThe given target number: " << targetNum;

	vector<vector<int>> ansArr = SumOfFourNumbers(nums, targetNum);
	cout << "\n\nTarget arrays:\n";
	for (auto& arr : ansArr)
	{
		for (int& num : arr)
			cout << num << ", ";
		cout << endl;
	}

	cout << endl << endl;
	return 0;
}
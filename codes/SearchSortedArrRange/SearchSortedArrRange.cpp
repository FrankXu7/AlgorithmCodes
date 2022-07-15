/**************************************************************************************************
 * 【题目描述】
 *
 *
 * 【输入】
 * 【输出】
 *
 * 【解题思路】
 *
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2022-07-14
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

pair<int, int> SearchSortedArrRange(vector<int>& nums, int target)
{
	pair<int, int> range(-1, -1);

	int leftIdx = 0, rightIdx = static_cast<int>(nums.size()) - 1, midIdx = -1;
	int subLeftIdxL = 0, subLeftIdxR = 0, subMidIdxL = -1;
	int subRightIdxL = 0, subRightIdxR = 0, subMidIdxR = -1;

	int count = 0;

	while (leftIdx < rightIdx)
	{
		midIdx = leftIdx + static_cast<int>((rightIdx - leftIdx) / 2);

		++count;

		if (nums[midIdx] < target)
			leftIdx = midIdx + 1;
		else if (nums[midIdx] > target)
			rightIdx = midIdx - 1;
		else
		{
			subLeftIdxL = leftIdx;
			subLeftIdxR = midIdx;
			while (subLeftIdxL < subLeftIdxR)
			{
				subMidIdxL = subLeftIdxL + static_cast<int>((subLeftIdxR - subLeftIdxL) / 2);

				if (nums[subMidIdxL] < target)
					subLeftIdxL = subMidIdxL + 1;
				else if (nums[subMidIdxL] == target)
					subLeftIdxR = subMidIdxL;

				++count;
			}
			range.first = subLeftIdxL;

			subRightIdxL = midIdx;
			subRightIdxR = rightIdx;
			while (subRightIdxL < subRightIdxR)
			{
				subMidIdxR = subRightIdxL + static_cast<int>((subRightIdxR - subRightIdxL) / 2);

				if (nums[subMidIdxR] > target)
					subRightIdxR = subMidIdxR - 1;
				else if (nums[subMidIdxR] == target)
					subRightIdxL = subMidIdxR;

				++count;
			}
			range.second = subRightIdxL;

			break;
		}
	}

	cout << endl << endl << "Execute count: " << count << endl << endl;

	return range;
}

int main(int argc, char** argv)
{
	vector<int> nums = { 1,2,3,3,3,4,5,6,7,8,8,8,9,10,11,12 };
	int target = 8;
	cout << "The given number array:\n";
	for (int n : nums) cout << n << ", ";
	cout << "\nSearch target number: " << target << endl;

	pair<int, int> range = SearchSortedArrRange(nums, target);
	cout << "\n\nThe range: [" << range.first << ", " << range.second << "] ";

	cout << endl << endl;
	return 0;
}
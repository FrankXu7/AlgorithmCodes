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

pair<int, int> SearchSortedArrRange_1(vector<int>& nums, int target)
{
	pair<int, int> range(-1, -1);

	auto BinarySearch = [](vector<int>& nums, int target, bool biggerSide) ->int {
		int leftIdx = 0, rightIdx = static_cast<int>(nums.size()) - 1, midIdx = -1;
		int searchedIdx = -1;

		while (leftIdx < rightIdx)
		{
			midIdx = leftIdx + static_cast<int>((rightIdx - leftIdx) / 2);
			if (nums[midIdx] < target)
				leftIdx = midIdx + 1;
			else if (nums[midIdx] >= target)
			{
				rightIdx = midIdx - 1;
				searchedIdx = midIdx;

				if (biggerSide)
					break;
			}
		}

		return searchedIdx;
	};

	range.first = BinarySearch(nums, target, false);
	range.second = BinarySearch(nums, target, true);

	return range;
}

pair<int, int> SearchSortedArrRange_2(vector<int>& nums, int target)
{
	pair<int, int> range(-1, -1);

	int leftIdx = 0, rightIdx = static_cast<int>(nums.size()) - 1, midIdx = -1;
	int subIdxL = 0, subIdxR = 0, subMidIdx = -1;

	while (leftIdx < rightIdx)
	{
		midIdx = leftIdx + static_cast<int>((rightIdx - leftIdx) / 2);

		if (nums[midIdx] < target)
			leftIdx = midIdx + 1;
		else if (nums[midIdx] > target)
			rightIdx = midIdx - 1;
		else
		{
			subIdxL = leftIdx;
			subIdxR = midIdx;
			while (subIdxL < subIdxR)
			{
				subMidIdx = subIdxL + static_cast<int>((subIdxR - subIdxL) / 2);

				if (nums[subMidIdx] < target)
					subIdxL = subMidIdx + 1;
				else if (nums[subMidIdx] == target)
					subIdxR = subMidIdx;
			}
			range.first = subIdxL;

			subIdxL = midIdx;
			subIdxR = rightIdx;
			while (subIdxL < subIdxR)
			{
				subMidIdx = subIdxL + static_cast<int>((subIdxR - subIdxL) / 2);

				if (nums[subMidIdx] > target)
					subIdxR = subMidIdx - 1;
				else if (nums[subMidIdx] == target)
				{
					subIdxL = subMidIdx;
					if (subIdxL + 1 == subIdxR)
						break;
				}
			}
			range.second = subIdxL;

			break;
		}
	}

	return range;
}

int main(int argc, char** argv)
{
	vector<int> nums = { 1,2,3,3,3,4,5,6,7,8,8,8,9,10,11,12 };
	int target = 8;
	cout << "The given number array:\n";
	for (int n : nums) cout << n << ", ";
	cout << "\nSearch target number: " << target << endl;

	pair<int, int> range1 = SearchSortedArrRange_1(nums, target);
	cout << "\n\n[Solution 1] The range: [" << range1.first << ", " << range1.second << "] ";

	pair<int, int> range2 = SearchSortedArrRange_2(nums, target);
	cout << "\n\n[Solution 2] The range: [" << range2.first << ", " << range2.second << "] ";

	cout << endl << endl;
	return 0;
}
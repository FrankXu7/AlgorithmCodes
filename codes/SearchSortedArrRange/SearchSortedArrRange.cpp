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

	auto BinarySearch = [](vector<int>& nums, int target, bool smallerSide) ->int {
		int leftIdx = 0, rightIdx = static_cast<int>(nums.size()) - 1, midIdx = -1;
		int searchedIdx = static_cast<int>(nums.size());

		while (leftIdx <= rightIdx)
		{
			midIdx = leftIdx + static_cast<int>((rightIdx - leftIdx) / 2);
			if (smallerSide)
			{
				if (nums[midIdx] < target)
					leftIdx = midIdx + 1;
				else
					rightIdx = midIdx - 1;
			}
			else
			{
				if (nums[midIdx] > target)
					rightIdx = midIdx - 1;
				else
					leftIdx = midIdx + 1;
			}
		}

		return smallerSide ? leftIdx : rightIdx;
	};

	range.first = BinarySearch(nums, target, true);
	range.second = BinarySearch(nums, target, false);

	return range;
}

pair<int, int> SearchSortedArrRange_2(vector<int>& nums, int target)
{
	pair<int, int> range(-1, -1);

	int leftIdx = 0, rightIdx = static_cast<int>(nums.size()) - 1, midIdx = -1;
	int subIdxL = 0, subIdxR = 0, subMidIdx = -1;

	// 先利用二分查找，找到等于target的元素的下标，并以此下标为基准，对其左右两侧分别进行二分法查找
	while (leftIdx <= rightIdx)
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
			// 左侧，二分查找首个等于target的元素的下标
			while (subIdxL <= subIdxR)
			{
				subMidIdx = subIdxL + static_cast<int>((subIdxR - subIdxL) / 2);

				// 左侧部分，当元素小于target的时候，往右侧收缩，接近数组中第一个等于target的元素
				if (nums[subMidIdx] < target)
					subIdxL = subMidIdx + 1;
				else 
					subIdxR = subMidIdx - 1;
			}
			range.first = subIdxL;

			subIdxL = midIdx;
			subIdxR = rightIdx;
			// 右侧，二分查找最后一个等于target的元素的下标
			while (subIdxL <= subIdxR)
			{
				subMidIdx = subIdxL + static_cast<int>((subIdxR - subIdxL) / 2);

				// 右侧部分，当元素大于target的时候，往左侧收缩，接近数组中最后一个等于target的元素
				if (nums[subMidIdx] > target)
					subIdxR = subMidIdx - 1;
				else 
					subIdxL = subMidIdx + 1;
			}
			range.second = subIdxR;

			break;
		}
	}

	return range;
}

int main(int argc, char** argv)
{
	vector<int> nums = { 1,2,3,3,3,4,5,6,7,8,8,8,8,8,9,9,10,11,12 };
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
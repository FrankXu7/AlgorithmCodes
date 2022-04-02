/**************************************************************************************************
 * 【题目描述】
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
 * @date 2022-03-22
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int SearchRotatedSortedArr_1(vector<int>& nums, int target)
{
	int resultIdx = -1;
	unsigned int arrLen = nums.size();

	if (target <= nums[0]) // 比首位更小，必然在旋转的右侧 
	{
		for (unsigned int idx = 0; idx < arrLen; ++idx)
		{
			if (target < nums[idx]) continue;
			
			if (target == nums[idx])
			{
				resultIdx = idx;
				break;
			}
		}
	}
	else // 比首位更大，必然在旋转的左侧 
	{
		for (int idx = arrLen - 1; idx >= 0; --idx)
		{
			if (target > nums[idx]) continue;

			if (target == nums[idx])
			{
				resultIdx = idx;
				break;
			}
		}
	}

	return resultIdx;
}

int SearchRotatedSortedArr_2(vector<int>& nums, int target)
{
	int resultIdx = -1;
	return resultIdx;
	
}

int main(int argc, char** argv)
{
	vector<int> nums = { 4,5,6,7,0,1,2 };
	int target = 0;

	cout << "The given array:\n";
	for (int& num : nums) cout << num << "  ";
	cout << "\nThe search target number: " << target;

	cout << "\n\n[Solution 1] Search the index in array: " << SearchRotatedSortedArr_1(nums, target);

	cout << endl << endl;
	return 0;
}
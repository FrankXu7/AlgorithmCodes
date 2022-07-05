/**************************************************************************************************
 * 【题目描述】
 * 整数数组 nums 按升序排列，数组中的值互不相同。在传递给函数之前，nums 在预先未知的某个下标 k 上进行了旋转，
 * 使数组变为 [ nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1] ]
 * 
 * 例如： [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
 * 
 * 给定旋转后的数组 nums 和一个整数 target ，找到 target 在 nums 的下标，没有则返回 -1，设计一个时间复杂度
 * 为 O(log N) 的算法来解决此问题。
 *
 * 【输入】
 * nums = [4,5,6,7,0,1,2], target = 0
 * 【输出】
 * resultIdx = 4
 *
 * 【解题思路】
 * 二分法查找，将一个元素互不相等的升序整数数组，从某个位置分割为两个部分组成新的数组，在新的数组中，从中间分
 * 开的左右子数组中，必然有一个子数组保持升序，可以通过判断子数组首元素是否小于尾元素找到保持升序的子区间。然
 * 后判断target是否在有序的子数组内，是的话继续用二分法查找，否则将无序的子数组从中间分割开，其中必然有一个子
 * 数组有序，重复此步骤直到找到target或左下标大于右下标位置。
 *
 * 【解题分析】
 * 时间复杂度：O(log N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2022-03-22
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int SearchRotatedSortedArr(vector<int>& nums, int target)
{
	int resultIdx = -1, leftIdx = 0, rightIdx = static_cast<int>(nums.size() - 1), midIdx = 0;

	while (leftIdx <= rightIdx)
	{
		midIdx = static_cast<int>((leftIdx + rightIdx) * 0.5f);
		if (target == nums[midIdx])
		{
			resultIdx = midIdx;
			break;
		}

		if (nums[leftIdx] <= nums[midIdx]) // 左子数组升序
		{
			if (nums[leftIdx] <= target && target < nums[midIdx])
				rightIdx = midIdx - 1;
			else
				leftIdx = midIdx + 1;
		}
		else // 右子数组升序
		{
			if (nums[midIdx] < target && target <= nums[rightIdx])
				leftIdx = midIdx + 1;
			else
				rightIdx = midIdx - 1;
		}
	}

	return resultIdx;
	
}

int main(int argc, char** argv)
{
	vector<int> nums = { 4,5,6,7,0,1,2 };
	int target = 0;

	cout << "The given array:\n";
	for (int& num : nums) cout << num << "  ";
	cout << "\nThe search target number: " << target;

	cout << "\n\nSearch the index in array: " << SearchRotatedSortedArr(nums, target);

	cout << endl << endl;
	return 0;
}
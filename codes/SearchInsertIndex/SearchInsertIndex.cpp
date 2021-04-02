/**************************************************************************************************
 * 【题目描述】
 * 存在一个升序排列的有序整数数组，给定一个数，搜索该数的插入位置,
 * 如果给定的数在数组已存在，返回的下标代表插入位置，也代表该数在数组的位置。
 *
 * 【输入】
 * nums=[1,2,3,5,6,7], target=4
 * 【输出】
 * insertIdx=3
 *
 * 【解题思路】
 * 利用二分法搜索，leftIdx，midIdx，rightIdx分别为搜索数组的两端和中间的下标，
 * 目标数字小于中间下标元素，则中间下标-1当作新的右端下标，
 * 目标数字大于中间下标元素，则中间下标+1当作新的左端下标，
 *（加1减1是为了排除已经比较过的元素）。
 * 
 * 因为满足插入的元素存在如下关系：nums[midIdx - 1] < target <= nums[midIdx]，
 * 所以插入位置必定为当 target <= nums[midIdx] 时的midIdx位置。
 * 需要特别注意的是，因为只在 target <= nums[midIdx] 时记录插入下标，
 * 所以插入下标初始值应该为数组长度，即target一直满足 nums[midIdx - 1] < target 时，插入下标就是数组长度。
 * 
 *
 * @author FrankX
 * @date 2021-04-02
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int SearchInsertIndex(vector<int>& nums, int target)
{
	if (nums.size() == 0) return 0;

	int insertIdx = nums.size();
	int leftIdx = 0;
	int midIdx = static_cast<int>(nums.size() / 2);
	int rightIdx = nums.size() - 1;

	while (leftIdx <= rightIdx)
	{
		if (target <= nums[midIdx])
		{
			insertIdx = midIdx;
			rightIdx = midIdx - 1;
		}
		else 
		{
			leftIdx = midIdx + 1;
		}
		midIdx = static_cast<int>((leftIdx + rightIdx) / 2);
	}

	return insertIdx;
}

int main()
{
	vector<int> nums = { 1, 2, 3, 5, 6, 7 };
	cout << "Insert index: " << SearchInsertIndex(nums, 8) << endl;

	return 0;
}

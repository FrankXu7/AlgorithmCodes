/**************************************************************************************************
 * 【题目描述】
 * “原地删除”整数数值中指定的元素，返回删除后数组剩余元素个数，元素顺序可以改变，
 * “原地删除”指的是不能用新的空间，即数组实际长度不变，但有效元素数量为返回的个数。
 *
 * 【输入】
 * nums=[1,2,3,4,4,5,], target=4
 * 【输出】
 * length=4, nums=[1,2,3,5,X,X]
 *
 * 【解题思路】
 * 利用“双指针”，即数组头尾下标，当左下标对应元素等于目标数字时，用右下标的数字替换之，右下标--，此时需要注意的是，
 * 若发生了右下标元素替换左下标元素，则左下标不能++，因为还需要下次遍历判断替换元素是否等于目标元素。
 * 当左下标小于等于右下标时，标识结束，此时数组中等于目标数字的元素都被右下标所指向过的元素替换，
 * 返回（左下标+1）即为有效元素个数。
 * 
 * @author FrankX
 * @date 2021-03-30
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int DeleteTargetNumber(vector<int>& nums, int target)
{
	unsigned int leftIdx = 0;
	unsigned int rightIdx = nums.size() - 1;

	while (leftIdx <= rightIdx)
	{
		if (nums[leftIdx] == target)
		{
			nums[leftIdx] = nums[rightIdx];
			--rightIdx;
		}
		else ++leftIdx;
	}

	return leftIdx;
}

int main()
{
	vector<int> nums = {1,2,3,4,5,5,6,6,6,7,8};
	
	int leftNum = DeleteTargetNumber(nums, 6);

	for (unsigned int i = 0; i < leftNum; ++i)
	{
		cout << nums[i] << ' ';
	}
	cout << endl;

	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数数组 nums 和一个目标值 targetNum，找到 nums 中的三个元素，使它们的和与 targetNum 最为接
 * 近，并返回这个最接近的和。假设 nums 只有一个三元组满足条件，且数组元素数量大于等于3
 *
 * 【输入】
 * nums=[-1,-1,-1,0,-10]; targetNum=-10;
 * 【输出】
 * closestSum=-11;
 * 即为三元组：-1,0,-10
 * 
 * 【解题思路】
 * 按题意，要使三元组之和接近 targetNum ，可以先对数组进行升序排序，然后开始遍历数组，对于当前遍历的下标
 * idx，从 idx+1 开始到末尾的区间，依次求得当前遍历元素与左右指针元素之和，并找到最接近 targetNum 的那组
 * 和，当前求和与目标值会有以下三种情况：
 * （1）三数之和等于 targetNum，显然这是最接近的了，直接返回结果；
 * （2）三数之和小于 targetNum，左指针自加，使得求和结果往 targetNum 靠近；
 * （3）三数之和大于 targetNum，同理，为了使求和结果更靠近 targetNum，右指针需要自减；
 * 
 * 分别计算 targetNum 与当前求所求之和 sum，以及保存的最接近 targetNum 的三元组之和 closestSum 的差值，
 * 通过比较差值的绝对值来判断是否要更新最接近 targetNum 的三元组之和 closestSum
 * 
 * 【解题分析】
 * 时间复杂度：O(N^2) 首先需要排序，而后续的双层遍历中，内层遍历是逐级递减的，故实际值为 O(N*N! + NlogN)
 * 空间复杂度：O(logN) 排序所需的空间复杂度，排序导致改变了原数组，若实际需求中不允许，则需要额外空间存储
 *                     排序后的数组，此时复杂度为 O(logN + N)
 *
 * @author FrankX
 * @date 2021-01-21
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int SumOfThreeNumbersClosest(vector<int>& nums, int targetNum)
{
	/** 题意假定数组长度大于等于3，故不需要防御处理 */

	int closestSum = 0, sum = 0;
	sort(nums.begin(), nums.end());
	unsigned int arrSize = nums.size(), leftIdx = 0, rightIdx = 0;

	for (unsigned int idx = 0; idx < arrSize; ++idx)
	{
		leftIdx = idx + 1;
		rightIdx = arrSize - 1;

		while (leftIdx < rightIdx)
		{
			sum = nums[idx] + nums[leftIdx] + nums[rightIdx];

			// 和相等，肯定是最接近的了，直接返回结果 
			if (sum == targetNum)
				return sum;
			else if (sum < targetNum)
				++leftIdx; // 当前求和小于目标值，左指针自加，使得求和结果靠近目标值 
			else
				--rightIdx; // 当前求和大于目标值，右指针自减，使得求和结果靠近目标值 

			// 比较当前计算的和，与之前保存的最接近的和之间的差值，一定要取绝对值比较 
			if (abs(targetNum - sum) < abs(targetNum - closestSum))
				closestSum = sum;
		}
	}

	return closestSum;
}

int main(int argc, char* argv[])
{
	vector<int> nums{ -1,-1,-1,0,-10 };
	int targetNum = -10;
	cout << "The give number array:\n";
	for (int num : nums) cout << num << ", ";
	cout << "\nThe target number: " << targetNum;

	cout << "\n\nThe closest sum: " << SumOfThreeNumbersClosest(nums, targetNum);

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 找出一个整数数组中具有最大和的连续子数组，并返回其最大和的值
 *
 * 【输入】
 * nums=[-2,1,-3,4,-1,2,1,-5,4]
 * 【输出】
 * maxSum=6, 最大的连续子数组：[4,-1,2,1]
 *
 * 【解题思路】
 * 双层遍历，因为子数组要求是连续的，所以计算每一种子数组的组合，和暂存的最大值进行比较，最终得到一个最大值。
 *
 * @author FrankX
 * @date 2021-04-08
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int MaxSubArraySum(vector<int> & nums)
{
	if (nums.size() == 0) return 0;

	int maxSum = 0;
	int tempSum = 0;
	
	for (vector<int>::iterator itr = nums.begin(); itr != nums.end(); ++itr)
	{
		for (vector<int>::iterator itp = itr; itp != nums.end(); ++itp)
		{
			tempSum += *itp;
			if (tempSum > maxSum) maxSum = tempSum;
		}
		tempSum = 0;
	}

	return maxSum;
}

int main()
{
	vector<int> nums = { -2,1,-3,4,-1,2,1,-5,4 };
	cout << "Max subarray sum: " << MaxSubArraySum(nums) << endl;

	return 0;
}

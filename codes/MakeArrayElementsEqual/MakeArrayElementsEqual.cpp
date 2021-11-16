/**************************************************************************************************
 * 【题目描述】
 * 给你一个长度为 n 的整数数组，每次操作将会使 n-1 个元素增加1，返回让数组所有元素相等的最小操作次数。
 *
 * 【输入】
 * [1,2,3]
 * 【输出】
 * 需要3次：[1,2,3] => [2,3,3] => [3,3,4] => [4,4,4]
 *
 * 【解题思路】
 * 方法一：
 * 每次必须操作 n-1 个元素，可以先排序（有序是为了保证最大元素永远在数组尾部），找到最大元素，除开最大元
 * 素外，剩余的 n-1 个元素增加1，此时会遇到两种情况：
 * （1）最大值唯一，那剩余 n-1 个元素增加1即可；
 * （2）最大值元素有多个，为了保证能有 n-1 个元素增加，并且不破坏有序性，则首个最大值元素需要保持不变，其
 *      后续的相同元素都加1；
 * 
 * 方法二：
 * 可以换一个方向，将 n-1 个元素增加1，最终使得数组内所有元素相等，也可以反过来理解为，只将 1 个元素减去1，
 * 最终也会使得数组内所有元素相等。两个方向达成数组内部元素相等的操作次数是相同的，同时，因为只需要操作一
 * 个数，所以可先找出数组中的最小值，计算其它元素和它的差值，该差值就是单个元素需要减去1的次数，这些差值
 * 之和，即为总的操作次数。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N^2)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-11-16
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MakeArrayElementsEqual_1(vector<int> nums)
{
	sort(nums.begin(), nums.end());

	int opCount = 0;

	unsigned int maxIdx = nums.size() - 1;
	bool bFirstMatch = true;
	while (nums[0] != nums[maxIdx])
	{
		bFirstMatch = true;
		for (unsigned int idx = 0; idx <= maxIdx; ++idx)
		{
			if (nums[idx] < nums[maxIdx])
			{
				++nums[idx];
			}
			else if (bFirstMatch)
			{
				// 存在多个最大值元素时，保持首个出现的最大值不变，后面的最大值元素加1 
				bFirstMatch = false;
				continue;
			}
			else
			{
				++nums[idx];
			}
		}

		++opCount;
	}

	return opCount;
}

int MakeArrayElementsEqual_2(vector<int> nums)
{
	int opCount = 0;
	
	int minElement = *min_element(nums.begin(), nums.end());
	for (int& num : nums)
	{
		opCount += (num - minElement);
	}

	return opCount;
}

int main(int argc, char** argv)
{
	vector<int> nums = { 14,1,9,2,21,7 };
	cout << "The given array is:\n";
	for (auto& num : nums) cout << num << ", ";

	cout << "\n\n[Solution 1] The minimum operate times: "
		<< MakeArrayElementsEqual_1(nums);

	cout << "\n\n[Solution 2] The minimum operate times: "
		<< MakeArrayElementsEqual_2(nums);

	cout << endl << endl;
	return 0;
}
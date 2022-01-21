/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数数组nums，找出其中三个元素 a,b,c 使得 a + b + c = 0，返回所有符合该等式的不重复的三元组。
 * 
 * 【输入】
 * nums=[-1,0,1,2,-1,-4,4,-6];
 * 【输出】
 * [
 *     [-6, 2, 4],
 *     [4, 0, 4],
 *     [-1, -1, 2],
 *     [-1, 0, 1]
 * ]
 * 其中，存在两组 [-1, 0, 1] 的三元组满足题中所给等式，但题意要求三元组不重复，故剔除之
 * 
 * 【解题思路】
 * 按题意，要使得非全零的三元组和为零，则其中必然有正负整数的存在，故可以先对数组进行升序排序，然后开始遍
 * 历数组，对于当前遍历的下标 idx，从 idx+1 开始到末尾的区间，利用双指针找到所有和当前遍历元素求和为零的
 * 左右指针，会有如下三种情况：
 * （1）三数之和等于零，则保存之，然后左右指针向彼此移动；
 * （2）三数之和小于零，因为数组是有序的，需要将左指针自加，使求和结果趋于零；
 * （3）三数之和大于零，同理，为了使求和结果更趋于零，右指针需要自减；
 * 
 * 此外，针对当前遍历的元素，有两种特殊情况需要注意：
 * （1）当前遍历的元素大于零，因为数组是有序的，故此后的元素都会大于零，显然找不到三数之和为零的三元组了，
 *      此时直接终止算法，返回最终结果；
 * （2）当前遍历元素等于前一个元素，这样相当于当前元素的值被查找了大于一次，故找到的三元组会和前一个元素
 *      相同，按题意需要剔除之；
 * 
 * 【解题分析】
 * 时间复杂度：O(N^2) 首先需要排序，而后续的双层遍历中，内层遍历是逐级递减的，故实际值为 O(N*N! + NlogN)
 * 空间复杂度：O(logN) 排序所需的空间复杂度，排序导致改变了原数组，若实际需求中不允许，则需要额外空间存储
 *                     排序后的数组，此时复杂度为 O(logN + N)
 *
 * @author FrankX
 * @date 2021-01-20
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 来一个方便打印所得结果的宏定义 
#define PRINT_ARR(arrs) \
for (auto &arr : arrs) \
{ \
	for (auto& num : arr) cout << num << ", "; \
	cout << endl; \
}

vector<vector<int>> SumOfThreeNumbers_1(vector<int>& nums)
{
	if (nums.size() < 3) return {};

	vector<vector<int>> ansArr;

	sort(nums.begin(), nums.end());
	unsigned int arrSize = nums.size(), leftIdx = 0, rightIdx = 0;
	int sum = 0;

	for (unsigned int idx = 0; idx < arrSize; ++idx)
	{
		// 因为已排序，当前元素大于零，那从它后面找两个元素一起求和必然大于零 
		if (nums[idx] > 0)
			break;
		else if (idx > 0 && nums[idx] == nums[idx - 1])
			// 排序后相等元素相邻，只处理首个，避免找到相同的三元组 
			continue;

		leftIdx = idx + 1;
		rightIdx = arrSize - 1;
		while (leftIdx < rightIdx)
		{
			sum = nums[idx] + nums[leftIdx] + nums[rightIdx];

			/**
			 * 当前左右下标刚好符合题意，那在赋值后，它们必须同时移动。如果左指针不变而右指针自减，因为数
			 * 组有序，故之后的结果必然小于等于零（此处等于零时取得的三元组和右指针操作之前的三元组相同，
			 * 不可取），反之，左指针自加而右指针不变，亦然
			 */
			if (sum == 0)
				ansArr.emplace_back(vector<int>({ nums[idx], nums[leftIdx++], nums[rightIdx--] }));
			else if (sum < 0)
				++leftIdx; // 三数之和太小，左指针自加，使得求和结果更趋于零 
			else
				--rightIdx; // 三数之和太大，右指针自减，使得求和结果更趋于零 
		}
	}

	return ansArr;
}

int main(int argc, char** argv)
{
	vector<int> nums{ -1,0,1,2,-1,-4,4,-6 };
	cout << "The given number's array:\n";
	for (int num : nums) cout << num << ", ";

	cout << "\n\nThe result array:\n";
	PRINT_ARR(SumOfThreeNumbers_1(nums));

	cout << endl << endl;
	return 0;
}
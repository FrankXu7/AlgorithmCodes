/**************************************************************************************************
 * 【题目描述】
 * 计算一个升序数组中是否存在两个元素之和会等于给定的数，并找出它们的下标，假设数组中只有一组答案，
 * 且同数组元素只能使用一次，返回的下标从 1 开始计数。
 *
 * 【输入】
 * array=[1, 4, 6, 7, 8, 12], target=12
 * 【输出】
 * index=[2, 5] 第二个数4和第五个数8，相加之和为12
 *
 * 【解题思路】
 * 方法一：
 * 最简单直观的方式就是暴力法，两层嵌套循环相加后与目标值比较。但需要注意到的是，给定数组的特殊性：是一个升序数组。
 * 所以可以采用二分查找，减少遍历次数。当然还是需要两层嵌套循环，第一层循环确定一个数字，通过目标数字与
 * 确定的数字的差值，可得出满足题意所需要的数字。这个数字会在第二层遍历中用二分法在升序数组中得出。
 * 大致步骤：
 * （1）第一层遍历，依次遍历数据，得到目标数字与遍历数字的差值，此值即为需要在第二层遍历中找到的数字；
 * （2）利用二分法查找，如果中间下标的数字大于需要的数字，则在左侧子区间继续二分查找，反之亦然。
 * （3）当左下标大于右下标时还没找到，则中止循环，继续在第一层遍历中处理下一个数字。
 *
 * 方法二：
 * 因为数组是升序的，也可以使用双指针法，进一步降低时间复杂度。将左右指针分别指向升序数组头尾数字，左右指针
 * 指向数据之和，如果小于目标数字，则左指针++，若大于目标数字，则右指针--，逐渐逼近目标数字。当左指针大于右指针时
 * 还没找到，即终止循环，结束算法。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(NlogN) 第一层遍历时间复杂度为O(N)，第二层遍历时间复杂度为O(logN)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-07-02
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

/** 这里返回的容器，要么是找到了数组中两个数，返回两个下标，要么就是没找到，返回空容器 */
template <typename T>
vector<unsigned int> SumOfTwoNumbersSorted_1(vector<T> &dataArr, T &targetNum)
{
	if (dataArr.empty())
		return {};

	unsigned int dataSize = dataArr.size();

	unsigned int leftIdx = 0;
	unsigned int rightIdx = 0;
	unsigned int midIdx = 0;
	T desireData = targetNum;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		leftIdx = idx + 1;
		rightIdx = dataSize - 1;
		desireData = targetNum - dataArr[idx];

		while (leftIdx <= rightIdx)
		{
			midIdx = static_cast<unsigned int>((leftIdx + rightIdx) / 2);

			if (dataArr[midIdx] < desireData)
				++leftIdx;
			else if (dataArr[midIdx] > desireData)
				--rightIdx;
			else
				return {idx + 1, midIdx + 1};
		}
	}

	return {};
}

/** 这里返回的容器，要么是找到了数组中两个数，返回两个下标，要么就是没找到，返回空容器 */
template <typename T>
vector<unsigned int> SumOfTwoNumbersSorted_2(vector<T> &dataArr, T &targetNum)
{
	if (dataArr.empty())
		return {};

	unsigned int leftIdx = 0;
	unsigned int rightIdx = dataArr.size() - 1;

	T addSum = 0;

	while (leftIdx <= rightIdx)
	{
		addSum = dataArr[leftIdx] + dataArr[rightIdx];
		if (addSum < targetNum)
			++leftIdx;
		else if (addSum > targetNum)
			--rightIdx;
		else
			return {leftIdx + 1, rightIdx + 1};
	}

	return {};
}

int main()
{
	vector<int> dataArr({1, 7, 9, 12, 19, 21, 28, 32, 44});
	int targetNum = 8;

	cout << "Data array:\n";
	for (vector<int>::iterator itr = dataArr.begin(); itr != dataArr.end(); ++itr)
		cout << *itr << ", ";

	cout << "\nTarget number: " << targetNum << endl;

	cout << "\n[Solution 1] Target idx: ";
	vector<unsigned int> idxVec = SumOfTwoNumbersSorted_1(dataArr, targetNum);
	for (vector<unsigned int>::iterator itr = idxVec.begin(); itr != idxVec.end(); ++itr)
		cout << *itr << ", ";

	idxVec.clear();
	cout << "\n[Solution 2] Target idx: ";
	idxVec = SumOfTwoNumbersSorted_2(dataArr, targetNum);
	for (vector<unsigned int>::iterator itr = idxVec.begin(); itr != idxVec.end(); ++itr)
		cout << *itr << ", ";

	cout << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数数组nums，求出下标区间 [leftIdx, rightIdx] 包含元素的和，实现一个 NumArray 类，要求：
 * （1）构造函数初始化数组；
 * （2）包含接口：int SumRange(unsinged int, unsigned int)，传入下标区间最值，返回该下标区间元素之和。
 * 
 * 【输入】
 * 构造数组：[-2, 0, 3, -5, 2, -1]
 * 求和：SumRange(0, 2)
 * 求和：SumRnage(2, 5)
 * 求和：SumRange(0, 5)
 * 【输出】
 * 构造NumArray对象
 * 返回：1
 * 返回：-1
 * 返回：-3
 * 
 * 【解题思路】
 * 方法一：
 * 最先想到的是简单粗暴的遍历求解，先将数组保存为类的私有成员，每次求和时，遍历传入的下标区间，将区间内的
 * 元素求和并返回。
 * 
 * 方法二：
 * 如果数组只是用来求和，频繁遍历计算并非最优解，可考虑类似动态规划的思想，将数组元素替换为前N个元素之和，
 * 比如下标为3的元素，替换为下标[0, 3]元素之和，如此，下标为 i 的元素与下标为 (i-1) 的元素之和，并将结果
 * 赋值给第 i 个元素。即为下标区间 [0, i] 的元素之和，满足表达式：sums[i] = nums[i] + sums[i-1]，简而言
 * 之，通过这一通计算，数组中下标为 i 的元素，表示下标区间[0, i]的元素之和。
 * 
 * 这样就建立了一个状态转移方程：sums[i, j] = nums[j] + nums[i-1]，求下标区间[i,j]的和被转换为求nums[j]
 * 与 nums[i-1] 的差值，题意要求是闭区间，所以减去的是 nums[i-1]，就是下标小于 i 的元素之和。
 * 
 * 这里需要特别注意的是，当 i=0 时，求的就是 [0, j] 的区间和，下标0的前N项和等于0，此时减数就是0
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N) 需要存储数组元素
 * 方法二：
 * 时间复杂度：O(1) 初始时需要构造一个元素为前N项和的数组，复杂度为O(N)，之后求区间和只需计算一个差值即可
 * 空间复杂度：O(N) 需要存储数组元素，元素为其所在下标前的元素之和
 * 
 * @author FrankX
 * @date 2021-09-26
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

class NumArray_1
{
public:
	explicit NumArray_1(vector<int>&& nums)
	{
		sumsArr = nums;
	}

	int SumRange(unsigned int leftIdx, unsigned int rightIdx)
	{
		auto dataSize = sumsArr.size();
		if (leftIdx >= dataSize || rightIdx >= dataSize)
		{
			cout << "\n[error] NumArray_1: Input out of range indexs!\n";
			return -1;
		}

		int calcSum = 0;
		for (unsigned int idx = leftIdx; idx <= rightIdx; ++idx)
		{
			calcSum += sumsArr[idx];
		}

		return calcSum;
	}

private:
	vector<int> sumsArr;
};

class NumArray_2
{
public:
	explicit NumArray_2(vector<int>&& nums)
	{
		sumsArr = nums;

		int tempSum = 0;
		for (auto itr = sumsArr.begin(); itr != sumsArr.end(); ++itr)
		{
			tempSum += *itr;
			*itr = tempSum;
		}
	}

	int SumRange(unsigned int leftIdx, unsigned int rightIdx)
	{
		auto dataSize = sumsArr.size();
		if (leftIdx >= dataSize || rightIdx >= dataSize)
		{
			cout << "\n[error] NumArray_2: Input out of range indexs!\n";
			return -1;
		}

		return (sumsArr[rightIdx] - (leftIdx == 0 ? 0 : sumsArr[leftIdx - 1]));
	}

private:
	vector<int> sumsArr;
};

int main(int argc, char** argv)
{
	auto ob1 = new NumArray_1({ -2, 0, 3, -5, 2, -1 });
	auto ob2 = new NumArray_2({ -2, 0, 3, -5, 2, -1 });
	unsigned int leftIdx = 0, rightIdx = 5;

	cout << "[solution_1] The sum between indexs [" << leftIdx << ", " << rightIdx << "] : "
		<< ob1->SumRange(leftIdx, rightIdx);

	cout << "\n\n[Solution_2] The sum between indexs [" << leftIdx << ", " << rightIdx << "] : "
		<< ob2->SumRange(leftIdx, rightIdx);

	cout << endl << endl;
	return 0;
}
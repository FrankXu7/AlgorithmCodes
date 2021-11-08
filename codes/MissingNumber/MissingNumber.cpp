/**************************************************************************************************
 * 【题目描述】
 * 给定一个取值范围为 [0, N] 的数组 nums，其长度为 N，数组中缺少一个数字，且数组中数值唯一，找到那个缺失
 * 的数字。实际上，就是在一个从0到N的自然数序列中，找到缺失的那个数字。
 *
 * 【输入】
 * Data Array = [0, 2, 5, 4, 1]
 * 【输出】
 * Missing Number = 3
 *
 * 【解题思路】
 * 方法一：
 * 可以理解为一个从0到N的自然数序列，缺失了一个数字，所以可先将nums数组是按升序排序一下，那么数组元素两两
 * 差值为1，遍历到相邻元素差值大于1（实际上只可能为2）的情况，则可以找出缺失的数字。
 * 
 * 方法二：
 * 通过数据结构set集合来找，先将数组元素一次放入一个set集合，然后从0开始遍历到N，注意遍历的边界包含N，将
 * 遍历索引作为数据在set集合中查找存在性，找到不存在于set集合中的索引，即为缺失的那个数字。
 * 
 * 方法三：
 * 从0到N的自然数可以看成是一个等差为1的等差数列，可对该等差数列求和，然后对数组中元素求和，做个减法，减
 * 出来的差值即为缺失的那个数字。
 * 
 * 方法四：
 * 可以采用异或运算，根据相同的两个数进行异或计算结果为0，可将0到N的自然数序列与nums数组元素依次进行异或
 * 计算，并将结果异或赋值到一个变量，因为异或运算满足交换律，所以nums即使无序也没关系，在计算过程中，0到N
 * 的自然数序列，有一个数字会因为在nums中找不到和它相等的元素而剩下来，这个元素即为那个缺失的元素。这个方
 * 法需要特别注意的是，对nums数组遍历计算过后，因为nums缺少一个元素，所以遍历不能完全覆盖从0到N的所有自然
 * 数，会剩余最后一个数字N，这个N在数值上刚好等于nums数组的长度值。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(NlogN) 提供的算法接口排序的平均复杂度为O(logN)，遍历找到差值大于1的相邻元素为O(N)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N) 集合提供了常数级别的复杂度，所以最终复杂度就是线性遍历的复杂度 
 * 空间复杂度：O(N)
 * 方法三：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法四：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-18
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

unsigned int MissingNumber_1(vector<unsigned int>& nums)
{
	// 先按升序排序 
	sort(nums.begin(), nums.end());
	unsigned int dataSize = nums.size();

	// 找出相邻差值大于1的情况 
	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		if (idx + 1 < dataSize && nums[idx + 1] - nums[idx] > 1)
		{
			return (nums[idx] + 1);
		}
	}

	cout << "\n\n[error] Can't find the missing number : MissingNumber_1\n\n";
	return UINT_MAX;
}

unsigned int MissingNumber_2(vector<unsigned int>& nums)
{
	unordered_set<unsigned int> numsSet;
	for (auto itr = nums.begin(); itr != nums.end(); ++itr)
	{
		numsSet.insert(*itr);
	}

	unsigned int cycleNum = nums.size() + 1;
	for (unsigned int idx = 0; idx < cycleNum; ++idx)
	{
		if (numsSet.find(idx) == numsSet.end())
		{
			return idx;
		}
	}

	cout << "\n\n[error] Can't find the missing number : MissingNumber_2\n\n";
	return UINT_MAX;
}

unsigned int MissingNumber_3(vector<unsigned int>& nums)
{
	// 计算未丢失那个数字时等差数列之和 
	unsigned int realSize = nums.size() + 1;
	unsigned int realSum = realSize * (realSize - 1) / 2;

	// 计算当前数组实际的和 
	unsigned int curSum = 0;
	for (auto itr = nums.begin(); itr != nums.end(); ++itr)
		curSum += *itr;

	return (realSum - curSum);
}

unsigned int MissingNumber_4(vector<unsigned int>& nums)
{
	unsigned int dataSize = nums.size();
	unsigned int bitCalcSum = 0;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		bitCalcSum ^= idx ^ nums[idx];
	}

	// 因为nums数组缺失一个元素，所以无法遍历完0到N全部自然数，剩余一个N没有处理，N的值会等于数组长度值 
	return bitCalcSum ^ dataSize;
}

int main(int argc, char* argv[])
{
	vector<unsigned int> nums{ 12,0,1,13,2,19,8,20,4,6,7,9,10,14,3,15,16,17,5,18, };

	cout << "The number array (size=" << nums.size() - 1 << "): \n";
	for (auto itr = nums.begin(); itr != nums.end(); ++itr)
		cout << *itr << ", ";

	cout << "\n\n[Solution 1] The missing number: " << MissingNumber_1(nums);

	cout << "\n\n[Solution 2] The missing number: " << MissingNumber_2(nums);

	cout << "\n\n[Solution 3] The missing number: " << MissingNumber_3(nums);

	cout << "\n\n[Solution 4] The missing number: " << MissingNumber_4(nums);

	cout << endl << endl;
	return 0;
}
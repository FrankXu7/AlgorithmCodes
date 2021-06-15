/**************************************************************************************************
 * 【题目描述】
 * 给定一个非空整数数组，除了某一个元素只出现一次以外，其余元素均出现两次。需要找出那个只出现一次的元素。
 * 要求算法具有线性时间复杂度（最差O(k·n)），且不能使用额外空间（最差O(1)）。
 *
 * 【输入】
 * array=[1,1,3,3,4,5,5,6,6]
 * 【输出】
 * targetNum=4
 *
 * 【解题思路】
 * 按题目所说的数组，假设数组是有序的情况下，那么数组中从头开始两两元素相等，直到遇到那个只出现一次的元素，
 * 所以首先会想到排序。
 * 但是题目要求具有线性时间复杂度（基础排序算法普遍不具备），基础排序算法中，只有桶排序最差的时间复杂度为O(nk)，
 * 与此同时，题目又要求不能使用额外空间，而桶排序的空间复杂度为O(n+k)。
 * 
 * 在看题解后，可以考虑【异或】运算，异或运算具有如下性质：
 * （1）任何数和0进行异或运算，结果仍是原来的数；
 * （2）任何数和自身异或运算，结果为0；
 * （3）异或运算满足 交换律 和 结合律；
 * （4）自反性：A^N^N=A，任何数与另一个数字（包括自己）进行两次异或运算，结果仍是原来的数；
 *
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

void SortArray(vector<int>& nums);

/**
 * @return 如果该数字不存在，返回空指针用以判断 
 */
int* AppearOnceNumber(vector<int>& nums)
{
	if (nums.empty()) return nullptr;

	// 将数组有序化 .
	SortArray(nums);

	// 最后一位不越界，长度减一处理 .
	unsigned int dataSize = nums.size() - 1; 
	for (unsigned int idx = 0; idx < dataSize; idx += 2)
	{
		if (nums[idx] != nums[idx + 1])
		{
			return &nums[idx]; 
		}
	}

	return nullptr;
}

/**
 * @brief 对给定的数组从小到大排序
 * @param nums 数组容器引用
 */
void SortArray(vector<int>& nums)
{
	unsigned int leftIdx = 0;
	unsigned int rightIdx = 0;
}

int main()
{
	vector<int> nums = { 1,1,3,3,4,5,5,6,6 };
	cout << "Input Array:\n";
	for (vector<int>::iterator itr = nums.begin(); itr != nums.end(); ++itr)
		cout << *itr << ", ";

	int* targetNum = AppearOnceNumber(nums);
	if (targetNum) cout << "\nThe targe number is: " << *targetNum << endl;
	else cout << "\nNumber don't exist!\n";
	cout << (nums[0] == 106);
	return 0;
}
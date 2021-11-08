/**************************************************************************************************
 * 【题目描述】
 * 给定一个非空整数数组，除了某一个元素只出现一次以外，其余元素均出现两次。需要找出那个只出现一次的元素。
 * 要求算法具有线性时间复杂度（最差O(K·N)），且不能使用额外空间（最差O(1)）。
 *
 * 【输入】
 * array=[1,1,3,3,4,5,5,6,6]
 * 【输出】
 * targetNum=4
 *
 * 【解题思路】
 * 按题目所说的数组，假设数组是有序的情况下，那么数组中从头开始两两元素相等，直到遇到那个只出现一次的元素，
 * 所以首先会想到排序。但是题目要求具有线性时间复杂度（基础排序算法普遍不具备），基础排序算法中，只有桶排
 * 序最差的时间复杂度为O(NK)，与此同时，题目又要求不能使用额外空间，而桶排序的空间复杂度为O(N+K)。
 * 
 * 在看题解后，可以考虑【异或】运算，异或运算具有如下性质：
 * （1）任何数和0进行异或运算，结果仍是原来的数；
 * （2）任何数和自身异或运算，结果为0；
 * （3）异或运算满足 交换律 和 结合律；
 * （4）自反性：A^N^N=A，任何数与另一个数字（包括自己）进行两次异或运算，结果仍是原来的数；
 *
 * 所以，可将数组中元素逐一异或运算，因为除了只出现一次的元素之外，其余元素都出现两次，异或结果为0，最终
 * 相当于只出现一次的数字与 (len-1)/2 个0进行异或运算，其结果为原来的数，即找到了那个只出现一次的数字。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-16
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

int AppearOnceNumber(vector<int> &nums)
{
	unsigned int dataSize = nums.size();
	int targetNum = 0;
	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		targetNum ^= nums[idx];
	}

	return targetNum;
}

int main()
{
	vector<int> nums = {1, 1, 3, 3, 5, 9, 5, 6, 6};
	cout << "Input Array:\n";
	for (vector<int>::iterator itr = nums.begin(); itr != nums.end(); ++itr)
		cout << *itr << ", ";

	if (nums.size() % 2 == 0)
		cout << "\nNot exist!\n";
	else
		cout << "\nThe targe number is: " << AppearOnceNumber(nums) << endl;

	return 0;
}

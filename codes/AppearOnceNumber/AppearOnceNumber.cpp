/**************************************************************************************************
 * 【题目描述】
 * 
 *
 * 【输入】
 * 
 * 【输出】
 * 
 *
 * 【解题思路】
 * 
 *
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
	for (unsigned int idx = 0; idx < dataSize; ++idx) 
	{
		if (nums[idx] != nums[++idx]) 
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

	return 0;
}
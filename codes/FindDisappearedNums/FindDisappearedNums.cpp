/**************************************************************************************************
 * 【题目描述】
 * 给定一个含有 n 个整数的数组 nums，其任何元素的取值区间为[1,n]，找出所有在[1,n]范围内但没有出现在 num 
 * 中的数字，并以数组的形式返回。
 * 
 * 【输入】
 * nums = [ 1,2,3,4,9,2,7,5,5 ];
 * 【输出】
 * 缺失数字数组：[6, 8]
 * 
 * 【解题思路】
 * 方法一：
 * 按照题意，数组元素必然为正整数，可以新建一个同样长度的bool数组 existNums，以数组下标的值来映射元素值，
 * 即下标值加上1就等于元素值。遍历 nums 数组，将其元素减去1作为 existNums 数组的下标，并将对应的元素设置
 * 为 true，标记这个数字是存在的。然后再遍历 existNums 数组，找到其中元素为 false 的下标，其下标值加上 1
 * 即为缺失的数字。
 * 
 * 方法二：
 * 在方法一中，空间复杂度会比较高，如果可以修改数组本身，则可以优化空间复杂度。还是先遍历数组，因为数组元
 * 素必然在[1,n]区间内，所以数组元素减去1后的值是nums的合法下标，将其与[1,n]的数字进行映射，即将计算后的
 * 下标值对应的元素设置为0，然后再对数组进行一次遍历，找到其中元素为 0 的下标，其下标值加上 1 即为缺失的
 * 数字。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(2N)，找到并标记已存在数字，找到缺失数字 
 * 空间复杂度：O(N) 不包含返回结果本身需要的空间 
 * 方法二：
 * 时间复杂度：O(N) 实际为O(2N)，原地标记已存在数字，找到缺失数字 
 * 空间复杂度：O(1) 不包含返回结果本身需要的空间 
 *
 * @author FrankX
 * @date 2021-11-12
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> FindDisappearedNums_1(vector<int>& nums)
{
	int fullSize = nums.size();
	vector<bool> existNums(fullSize, false);
	for (auto& num : nums)
		existNums[num - 1] = true;
		
	vector<int> lostNums;
	for (int idx = 0; idx < fullSize; ++idx)
	{
		if (!existNums[idx])
			lostNums.emplace_back(idx + 1);
	}
	
	return lostNums;
}

vector<int> FindDisappearedNums_2(vector<int> nums)
{
	for (int& num : nums)
	{
		if (num > 0)
			nums[num - 1] = 0;
	}

	int fullSize = nums.size();
	vector<int> lostNums;
	for (int idx = 0; idx < fullSize; ++idx)
	{
		if (nums[idx] > 0)
			lostNums.emplace_back(idx + 1);
	}

	return lostNums;
}

int main(int argc, char** argv)
{
	vector<int> nums = { 1,2,3,4,9,2,7,5,5 };
	cout << "The given number array:\n";
	for (int& num : nums) cout << num << ", ";
	
	vector<int> lostNums1 = FindDisappearedNums_1(nums);
	cout << "\n\n[Solution 1] Found the lost numbers:\n";
	for (int& num : lostNums1) cout << num << ", ";
	
	vector<int> lostNums2 = FindDisappearedNums_2(nums);
	cout << "\n\n[Solution 2] Found the lost numbers:\n";
	for (int& num : lostNums2) cout << num << ", ";
	
	cout << endl << endl;
	return 0;
}

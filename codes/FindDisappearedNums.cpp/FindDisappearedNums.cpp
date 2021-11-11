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
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> FindDisappearedNums_1(vector<int>& nums)
{
	unordered_set<int> fullNums;
	unsigned int fullSize = nums.size();
	for (unsigned int n = 1; n <= fullSize; ++n)
		fullNums.emplace(n);

	for (auto& num : nums)
		fullNums.erase(num);

	vector<int> lostNums;
	lostNums.assign(fullNums.begin(), fullNums.end());

	return lostNums;
}

vector<int> FindDisappearedNums_2(vector<int> nums)
{
	unordered_set<int> existNums;
	for (auto& num : nums)
	{
		if (existNums.emplace(num).second)
			num = 0;
	}

	vector<int> lostNums;
	for (auto& num : nums)
	{
		if (num != 0)
			lostNums.emplace_back(num);
	}

	return lostNums;
}

vector<int> FindDisappearedNums_3(vector<int> nums)
{
	int fullSize = nums.size();
	for (int& num : nums)
	{
		int x = (num - 1) % fullSize;
		nums[x] += fullSize;
	}
		
	
	vector<int> lostNums;
	for (int idx = 0; idx < fullSize; ++idx)
	{
		if (nums[idx] < fullSize)
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

	vector<int> lostNums3 = FindDisappearedNums_3(nums);
	cout << "\n\n[Solution 3] Found the lost numbers:\n";
	for (int& num : lostNums3) cout << num << ", ";

	cout << endl << endl;
	return 0;
}

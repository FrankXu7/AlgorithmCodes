/************************************************************************************************** 
 * 【题目描述】
 * 计算数组中是否存在两个元素之和会等于给定的数，并找出它们的下标，假设数组中只有一组答案，且同数组元素只
 * 能使用一次。
 *
 * 【输入】
 * array=[9, 0, 1, 8, 7, 5, 4, 2, 3, 6], target=16
 * 【输出】
 * index=[0, 4]
 *
 * 【解题思路】
 * 可以将给定的数与遍历的元素相减，得出的差值放入一个无序map，并且以该差值作为key，遍历的下标作为value，
 * 故在后续的遍历中，给定的数与元素相减能在无序map中匹配到，即找到一组元素，它们的和会等于给定的数。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 
 * @author FrankX
 * @date 2021-03-30
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

vector<unsigned int> SumOfTwoNumbers(vector<int>& nums, int target)
{
	size_t len = nums.size();
	unordered_map<int, unsigned int> tempMap;

	unordered_map<int, unsigned int>::iterator itMap;
	// 无序map中放入数组首个元素，减少一次遍历
	tempMap[nums[0]] = 0;

	for (unsigned int idx = 1; idx < len; ++idx)
	{
		itMap = tempMap.find(target - nums[idx]);
		if (itMap != tempMap.end())
		{
			return { itMap->second, idx };
		}
		tempMap[nums[idx]] = idx;
	}

	return {};
}

int main()
{
	vector<int> nums = {9, 0, 1, 8, 7, 5, 4, 2, 3, 6};

	vector<unsigned int> idxArr = SumOfTwoNumbers(nums, 16);

	for (unsigned int idx = 0; idx < idxArr.size(); ++idx)
		cout << idxArr[idx] << ' ';
	cout << endl;

	return 0;
}

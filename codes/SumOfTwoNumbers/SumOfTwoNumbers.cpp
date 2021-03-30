/* No.1 In a number array, find two different numbers that the sum is equal to the given number. */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

/*
 * @brief Find two differwnt numbers that the sum is equal to the given number
 * @param nums The number array
 * @param target The given target number
 * */
void TwoNumSum(vector<int>& nums, int target)
{
	int len = nums.size();
	// Temp map for the numbers that is not equal to the minus of the target number and current cycle number
	unordered_map<int, int> tempMap;

	unordered_map<int, int>::iterator itMap;
	// For reduce one cycle, take the first position of map
	tempMap[nums[0]] = 0;

	for (int idx = 1; idx < len; ++idx)
	{
		itMap = tempMap.find(target - nums[idx]);
		if (itMap != tempMap.end())
		{
			cout << itMap->second << "\t" << idx << endl;
			cout << itMap->first << "+" << nums[idx] << "=" << itMap->first + nums[idx] << endl;

			break;
		}

		tempMap[nums[idx]] = idx;
	}
}

int main()
{
	cout << "[9,0,1,8,7,5,4,2,3,6]" << endl;
	vector<int> nums = {9, 0, 1, 8, 7, 5, 4, 2, 3, 6};

	TwoNumSum(nums, 16);

	return 0;
}

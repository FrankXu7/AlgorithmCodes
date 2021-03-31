#include <iostream>
#include <vector>

using namespace std;

int removeElement(vector<int>& nums, int target)
{
	unsigned int leftIdx = 0;
	unsigned int rightIdx = nums.size() - 1;

	while (leftIdx <= rightIdx)
	{
		if (nums[leftIdx] == target)
		{
			nums[leftIdx] = nums[rightIdx];
			--rightIdx;
		}
		else ++leftIdx;
	}

	return leftIdx;
}

int main()
{
	vector<int> nums = {1,2,3,4,5,5,6,6,6,7,8};
	
	int leftNum = removeElement(nums, 6);

	for (unsigned int i = 0; i < leftNum; ++i)
	{
		cout << nums[i] << ' ';
	}
	cout << endl;

	return 0;
}

#include <iostream>
#include <vector>

using namesapce std;

int MaxSubArraySum(vector<int> & nums)
{
	if (nums.size() == 0) return 0;

	int maxSum = 0;
	
	for (vector<int>::iterator itr = nums.begin(); itr != nums.end(); ++itr)
	{
		maxSum += *itr;
		if (maxSum == *itr)
		{
			maxSum = (*itr)++;
		}
	}

	return maxSum;
}

int main()
{


	return 0;
}

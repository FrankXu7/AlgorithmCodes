#include <iostream>
#include <vector>

using namespace std;
 
vector<unsigned int> ArrayPlusOne(vector<unsigned int>& digits)
{
	unsigned int resultNum = 0;
	unsigned int addOne = 1;

	for (vector<unsigned int>::iterator itr = digits.end(); itr != digits.begin(); --itr)
	{
		if (addOne == 1)
		{
			if (*itr + 1 < 10)
			{
				//++(*itr);
				*itr = *itr + 1;
				addOne = 0;
			}
			else
			{
				*itr = 0;
			}
		}
		else 
			break;
	}

	return digits;
}

int main()
{
	vector<unsigned int> nums = {1, 4, 7, 8};

	ArrayPlusOne(nums);

	for (vector<unsigned int>::iterator itr = nums.begin(); itr != nums.end(); ++itr)
	{
		cout << *itr;
	}
	cout << endl;

	return 0;
}

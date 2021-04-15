/**************************************************************************************************
 * 【题目描述】
 * “原地删除”一个升序整数数组中的重复元素，只保留一个，元素顺序不能改变。
 * “原地删除”指的是不能用新的空间，即数组实际长度不变，但有效元素数量为返回的个数。
 *
 * 【输入】
 * nums=[1,2,3,3,3,4,5]
 * 【输出】
 * length=5, nums=[1,2,3,4,5,X,X]
 *
 * 【解题思路】
 * 利用快慢指针，即两个下标变量，快指针遍历速度快于慢指针，初始时都指向首元素：
 *（1）若快慢指针对应元素不同，快指针对应元素替换 慢指针+1 对应元素，快慢指针都++，
 * 此时若快慢指针相邻，实则为自身赋值，增加了非必要的运算，但简化了逻辑；
 *（2）若快慢指针对应元素相同，快指针++；
 * 重复（1）（2）直至快指针遍历完数组。
 *
 * @author FrankX
 * @date 2021-03-30
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

unsigned int DeleteRepeatNumber(vector<int>& nums)
{
	if (nums.size() == 0) return 0;

	unsigned int slowIdx = 0;
	unsigned int fastIdx = 0;

	while (fastIdx < nums.size())
	{
		if (nums[slowIdx] != nums[fastIdx])
		{
			// 牺牲 slowIdx + 1 == fastIdx 时的赋值运算来简化代码逻辑
			nums[slowIdx + 1] = nums[fastIdx];
			++slowIdx;
		}

		++fastIdx;
	}

	return slowIdx + 1;
}

int main()
{
	vector<int> inputNums = {1,2,3,4,5,5,6,7,8,9,9};

	unsigned int leftCount = DeleteRepeatNumber(inputNums);

	cout << "Left element count: " << leftCount << endl;
	for (unsigned int idx = 0; idx < inputNums.size(); ++idx)
		(idx < leftCount) ?
			cout << inputNums[idx] << ' ' :
			cout << '[' << inputNums[idx] << "] ";
	cout << endl;

	return 0;
}

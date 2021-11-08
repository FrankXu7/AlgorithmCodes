/**************************************************************************************************
 * 【题目描述】
 * 给定一个数组 nums，将数组中所有的 0 移动到数组末尾，同时保持非零元素的相对顺序不变。必须在原数组上操作，
 * 不能使用辅助空间，且需要尽量减少操作次数。
 *
 * 【输入】
 * Array = [66,0,1,0,3,12,5,0,7,8,0];
 * 【输出】
 * Array = [66,1,3,12,5,7,8,0,0,0,0];
 *
 * 【解题思路】
 * 可使用快慢指针法，将快指针指向元素替换到慢指针指向元素，如果快指针指向的是0，则快直接指针后移一位不进
 * 行替换。当快指针指向边界时，慢指针指向的元素左侧是该数组全部非0元素，故将慢指针右侧都直接赋值为0即可。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-23
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

void MoveZeroes(vector<int>& arr)
{
	auto dataSize = arr.size();
	unsigned int slowIdx = 0, fastIdx = 0;

	// 快指针肯定跑的更快，只要对它进行边界判断即可 
	for (; fastIdx < dataSize; ++fastIdx)
	{
		if (arr[fastIdx] != 0)
		{
			arr[slowIdx++] = arr[fastIdx];
		}
	}

	// 此时慢指针指向数组最后一个非0元素，其后续元素需要赋值为0 
	while (slowIdx < dataSize)
	{
		arr[slowIdx++] = 0;
	}
}

int main(int argc, char* argv[])
{
	vector<int> arr{ 66,0,1,0,3,12,5,0,7,8,0 };

	cout << "Array data befor movement: \n";
	for (auto num : arr) cout << num << ", ";

	MoveZeroes(arr);

	cout << "\n\nArray data after movement: \n";
	for (auto num : arr) cout << num << ", ";

	cout << endl << endl;
	return 0;
}
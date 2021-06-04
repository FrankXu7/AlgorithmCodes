/**************************************************************************************************
 * 【题目描述】
 * 给定一个非负整数数组，数组元素为单个数字，所有元素组成一个非负整数，
 * 给这个整数加1，并输出这个数组代表的整数。
 *
 * 【输入】
 * digits=[1, 6, 8, 9]
 * 【输出】
 * num=1690
 *
 * 【解题思路】
 * 反序遍历数组，元素加1后判断是否超过10，若超过则标记需要进位，若不超过，表示加法完成，直接退出循环。
 * 遍历开始时，默认标记需要进位。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-04-09
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;
 
vector<unsigned int> ArrayPlusOne(vector<unsigned int>& digits)
{
	if (digits.size() == 0)
	{
		digits.push_back(0);
		return digits;
	}

	unsigned int resultNum = 0;
	unsigned int carryOne = 1;

	for (vector<unsigned int>::reverse_iterator itr = digits.rbegin(); itr != digits.rend(); ++itr)
	{
		if (carryOne == 0) break;

		// ++ 运算符优先级高于 * 
		(*itr + 1 < 10) ? (++(*itr), carryOne = 0) : (*itr = 0);
	}

	return digits;
}

int main()
{
	vector<unsigned int> digits = {1, 4, 9, 9};

	ArrayPlusOne(digits);

	for (vector<unsigned int>::iterator itr = digits.begin(); itr != digits.end(); ++itr)
	{
		cout << *itr;
	}
	cout << endl;

	return 0;
}

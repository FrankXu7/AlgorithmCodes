/**************************************************************************************************
 * 【题目描述】
 * 给定一个非负整数 num，反复将各位上的数字相加，直到结果为1为止。
 *
 * 【输入】
 * num = 57481, num = 5 + 7 + 4 + 8 + 1 = 25, num = 7 
 * 【输出】
 * result num = 7
 *
 * 【解题思路】
 * 方法一：
 * 最先想到的就是简单粗暴的对10取余后再整除10，一轮下来后如果数字大于等于10，就再来一轮直到小于10为止。
 * 
 * 方法二：
 * 题中所求的其实就是一个数字的数根（数字根）。
 * 数（字）根：是自然数的一种性质，每一个自然数都有一个数字根，数字根是一个不超过10的正整数。
 * 
 * 数根有循环性质，从数字1开始，数根从1-9反复循环，比如：
 * 数字：1   2   3   ...   7   8   9   10  11  12  ...  17  18  19  20  21  22  ...
 * 数根：1   2   3   ...   7   8   9   1   2   3   ...  8   9   1   2   3   4   ...
 * 
 * 所以，考虑正整数对9取余，即可得到数根，但有一种特殊的情况，即取余结果为0时的情况。因为正整数各位之和是
 * 不可能等于0的，所以需要先将正整数-1后，对9取余，然后再加上1，即为一个正整数的数根。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O((logN)^2) 一个数字的位数是logN向上取整 
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-17
 **************************************************************************************************/
#include <iostream>
using namespace std;

unsigned int AddNumDigits_1(unsigned int num)
{
	unsigned int tempNum = 0;
	
	while (num >= 10)
	{
		while (num > 0)
		{
			tempNum += (num % 10);
			num /= 10;
		}

		num = tempNum;
		tempNum = 0;
	}

	return num;
}

unsigned int AddNumDigits_2(unsigned int num)
{
	/**
	 * 这一步主要目的是排除0，顺便将10以内自然数也排除了减少点运算，
	 * 排除0是因为此算法核心算子采用数根思想，数根在数学上针对的是正整数，
	 * 而(0-1)就要面对负数取余的问题了（负数取模计算不统一），此外 unsigned int 为负也会越界。
	 */
	if (num < 10 ) return num;

	return ((num - 1) % 9 + 1);
}

int main(int argc, char** argv)
{
	unsigned int inputNum = 0;

	cout << "The input number is: " << inputNum;

	cout << "\n\n[Solution 1] Add every digits to one: " << AddNumDigits_1(inputNum);

	cout << "\n\n[Solution 2] Add every digits to one: " << AddNumDigits_2(inputNum);

	cout << endl << endl;
	return 0;
}
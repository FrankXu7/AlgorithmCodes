/**************************************************************************************************
 * 【题目描述】
 * 判断一个整数是否为回文数，回文数即正序和反序读，数字都一样，如：12321 之类。
 *
 * 【输入】
 * integer=123321
 * 【输出】
 * 判断是否为回文数
 *
 * 【解题思路】
 * 因为回文数具有对称性，翻转回文数后半部分的数字，会等于前半部分，所以依次剥离其个位数（对10取余），并从
 * 个位开始添加到一个新数字当中，当指定的数字减小到小于等于新的数字后，将相当于将该整数对半分开了，如果两
 * 个对半分开的数字相等，则原整数是回文数。需要特别注意的是，奇数位的整数，正中间的数字和它自身对称，如：
 * 12321 也是回文数。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-03-30
 **************************************************************************************************/
#include <iostream>

using namespace std;

bool PalindromeInteger(int num)
{
	if (num <= 0 || num % 10 == 0) return false;

	int tempNum = 0;
	while (num > tempNum)
	{
		tempNum = tempNum * 10 + num % 10;
		num = static_cast<int>(num / 10);
	}
	
	// 针对两种情况：1221 或 12321
	return (tempNum == num || static_cast<int>(tempNum / 10) == num);
}

int main()
{
	int inputNum = 0;
	cout << "Input:  ";
	cin >> inputNum;

	PalindromeInteger(inputNum) ? 
		cout << "This is a Palindrome number." << endl:
		cout << "Not a Palindrome number." << endl;

	return 0;
}

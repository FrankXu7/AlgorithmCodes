/**
 * 【题目描述】
 * 判断一个整数是否为回文数，回文数即正序和反序读，数字都一样，如：12321 之类。
 *
 * 【输入】
 * integer=123321
 * 【输出】
 * 判断是否为回文数
 * 
 * @author FrankX
 * @date 2021-03-30
 */
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

	PalindromeInteger(inputNum);

	PalindromeInteger(inputNum) ? 
		cout << "This is a Palindrome number." << endl:
		cout << "Not a Palindrome number." << endl;

	return 0;
}

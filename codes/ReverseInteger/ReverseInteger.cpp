/**************************************************************************************************
 * 【题目描述】
 * 将一个整数翻转
 *
 * 【输入】
 * integer=12345
 * 【输出】
 * integer=54321
 *
 * 【解题思路】
 * 准备一个新整数作为翻转结果：
 * （1）将原数对10取余得到其个位数；
 * （2）新整数乘10后加上该个位数，然后原数除10；
 * 重复（1）（2）步骤直至原数等于0为止。
 *
 * 【解题分析】
 * 时间复杂度：O(lg(N)) 循环的次数就是整数按十进制算的位数 
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2022-01-14
 **************************************************************************************************/
#include <iostream>
#include <climits>

using namespace std;

int ReverseInteger(int inputNum)
{
	int resultNum = 0;

	while (inputNum != 0)
	{
		resultNum = resultNum * 10 + inputNum % 10;
		inputNum = static_cast<int>(inputNum / 10);
	}

	return resultNum;
}

int main()
{
	int inputNum = 0;
	cout << "Input an Integer: ";
	cin >> inputNum;

	int resultNum = ReverseInteger(inputNum);
	if (resultNum < INT_MIN || resultNum > INT_MAX) resultNum = 0;

	cout << "Overturn Number: " << resultNum << endl;
	cout << endl << "Integer Range: " << endl << INT_MIN << endl << INT_MAX << endl;

	return 0;
}

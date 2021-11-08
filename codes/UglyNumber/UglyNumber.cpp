/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数，判断其是否为丑数，丑数即质因数只包含：2、3、5的数，数字1被视为是丑数。
 *
 * 补充：任何一个数，都可以拆分为唯一的一组质数相乘。
 *
 * 【输入】
 * Input number = 900
 * 【输出】
 * YES
 * 
 * 【解题思路】
 * 依题，首先0和负数都不是丑数，所以数据结构采用 unsigned int，其次题设数字1是丑数，所以算法开始需要针对
 * 0和1进行分支处理。如果一个数是丑数，将它对2取余，若结果为0则再整除2，然后继续上述操作直到对2取余不为0，
 * 再之后，继续对3和5进行同样的处理，因为都有取余判断，故丑数经过这一系列计算后结果必为1，否则就不是丑数。
 * 
 * 
 * 【解题分析】
 * 时间复杂度：O(logN) 因为至少都是对2整除
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-17
 **************************************************************************************************/
#include <iostream>
using namespace std;

bool UglyNumber(unsigned int num)
{
	if (num == 0) return false;
	else if (num == 1) return true; // 题意设定1视为丑数 

	while (num % 2 == 0) num /= 2;
	while (num % 3 == 0) num /= 3;
	while (num % 5 == 0) num /= 5;
		
	return (num == 1);
}

int main(int argc, char* argv[])
{
	unsigned int inputNum = 900;

	cout << "Input number is: " << inputNum;

	cout << "\n\nIs an ugly number? " << (UglyNumber(inputNum) ? "YES\n" : "NO\n");

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 实现一个字字符串转数字的算法：
 * （1）在没有读取到数字字符前（包含读取到首个正负号字符的情况），忽略字符串的前导空格字符；
 * （2）读取首个正负号字符作为数字的符号，如果后面又读到正负号字符则终止读取；
 * （3）已经读取到数字字符的情况下，后续遇到任意非数字字符，则终止读取；
 * （4）假设系统只有32位有符号的整数，取值区间位 [-2^31, 2^31 - 1]，若发生越界，取边界值作为返回结果；
 * （5）如果没有读取到任何有效数字字符（所谓有效，即读取数字字符前不会被终止），则返回0作为结果；
 * 
 * 【输入】
 * str1 = "    666 abc888";
 * str2 = "  -  123 -456 +789";
 * str3 = " abc 2333 def";
 * str4 = " + - 567";
 * str5 = "+123 456";
 * str6 = "2147483649";
 * 【输出】
 * num1 = 666;
 * num2 = -123;
 * num3 = 0;
 * num4 = 0;
 * num5 = 123;
 * num6 = 2147483647; // str6 发生越界，取正数最大值，即 2^31 - 1
 *
 * 【解题思路】
 * 利用分支满足题设条件：
 * （1）num == 0，即还未读取到数字字符，遇到前导零忽略之，遇到首个正负号字符，先设置符号 sign，再设置符
 *      号的标记状态 bSigned，就是标记是否设置过符号了，下次再遇到正负号字符就是代表终止读取；
 * （2）读取到数字字符时，更新 num 的值，因为整数越界会导致异号，所以 sign 和 num 异号时，表示有越界发生，
 *      num 设置为边界值并终止循环；
 * （3）num != 0，即已经读取到数字字符，此时读取遇到任意非数字字符，则终止读取；
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2022-01-14
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

int StringToInteger(string& str)
{
	if (str.empty()) return 0;

	int num = 0;
	int sign = 1;
	bool bSigned = false;
	char ch = '\0';

	for (unsigned int idx = 0; idx < str.length(); ++idx)
	{
		ch = str[idx];

		// 在没有读取到数字前，忽略前导零 
		if (num == 0 && ch == ' ') continue;
		
		// 读取首个正负号字符即确定数字的符号，下次遇到就是终止读取了 
		if (!bSigned && (ch == '-' || ch == '+'))
		{
			if (ch == '-') sign = -1;
			bSigned = true;
		}
		else if ('0' <= ch && ch <= '9')
		{
			// 在没有读取到正负号字符前读取到数字，标识为正数，后续再遇到正负号字符就是终止读取了 
			if (!bSigned) bSigned = true;

			num = num * 10 + sign * (ch - '0');
			// 标识为正数时，实际却小于零，即代表发生了越界，取边界值，反之亦然 
			if (sign > 0 && num < 0)
			{
				num = INT_MAX;
				break;
			}
			else if (sign < 0 && num > 0)
			{
				num = INT_MIN;
				break;
			}
		}
		else
			break; // 遇到非数字字符，终止读取 
	}

	return num;
}

int main(int argc, char** argv)
{
	string str = "   +   667  +636 -6 gasgadju";
	cout << "The given string: " << str;

	cout << "\n\nTo integer: " << StringToInteger(str);

	cout << "\n\nMinimum Integer: " << INT_MIN << "\nMaximum Integer: " << INT_MAX << endl;
	return 0;
}
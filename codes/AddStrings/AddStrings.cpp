/**************************************************************************************************
 * 【题目描述】
 * 给定两个字符串形式的正整数 num1 和 num2，己算这两个字符串形式的和并同样以字符串返回。
 * 
 * 要求：不能使用针对这种情况的库函数，也不能使用接口将字符串转换为数字操作。
 * 
 * 【输入】
 * num1="33", num2="35"
 * 【输出】
 * 相加之和：68
 * 
 * 【解题思路】
 * 提议要求不能使用库函数，那就按照手算加法的方法，将数位对齐，从低位到高位依次计算，如果当前位相加结果超
 * 过10（两个小于10的正整数之和最大为18，即使加上进位也就是19），则向前进一位。依据这个思路，可以同时从两
 * 字符串末尾开始往头部遍历，将它们同下标（即同数位）的字符相加，因为字符0的ASCII码是48，所以两个字符之和
 * 即为其字符ASCII码减去字符0的ASCII码之和，而后再加上进位即可。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-11-09
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

string AddStrings(string& num1, string& num2)
{
	string resultStr;
	bool bCarry = false;
	int idx1 = num1.length() - 1, idx2 = num2.length() - 1;
	
	unsigned int addResult = 0;

	for (; (idx1 >= 0 || idx2 >= 0); --idx1, --idx2)
	{
		// 两个小于10的正整数之和，即为其字符ASCII码减去字符0的ASCII码之和 
		addResult = (idx1 >= 0 ? num1[idx1] : '0') + (idx2 >= 0 ? num2[idx2] : '0') - 96;

		if (bCarry)
		{
			bCarry = false;
			++addResult;
		}
		
		if (addResult >= 10)
		{
			bCarry = true;
			addResult -= 10;
		}

		resultStr.insert(resultStr.begin(), static_cast<char>(addResult + 48));
	}

	return resultStr;
}

int main(int argc, char** argv)
{
	string num1 = "1136", num2 = "95";
	cout << "String 1 is: " << num1 << "\nString 2 is: " << num2;

	cout << "\n\nResult of two strings addition: " << AddStrings(num1, num2);

	cout << endl << endl;
	return 0;
}
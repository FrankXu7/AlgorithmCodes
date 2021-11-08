/**************************************************************************************************
 * 【题目描述】
 * 给定两个代表二进制数的字符串，只包含字符‘0’和‘1’，计算这两个二进制字符串的的和，并返回和的二进制字符串。
 *
 * 【输入】
 * s1="1010", s2="1011"
 * 
 * 【输出】
 * resultStr="10101"
 *
 * 【解题思路】
 * 以最长的字符串长度作为遍历边界，反序遍历两个字符串。对同下标的两个字符代表的数字，与进位的值相加：
 * c1 + c2 + carry，依题可知这三个数只可能是0或1，它们的和（这里是在十进制规则下相加的和）的个位数，即为
 * 结果字符串对应下标的字符，有偶数个1，则和的个位数是0，有奇数个1，则和的个位数是1；需要注意进位的情况，
 * 若这三个数之和大于2，代表有进位。针对字符串中非“0”和“1”的字符，统一用“0”填充。
 * 
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-04-09
 **************************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

string BinaryPlus(string& s1, string& s2)
{
	string resultStr = "";
	int carry = 0;

	// 减少获取属性接口的重复调用 
	string::iterator head = resultStr.begin();
	int len1 = s1.length(), len2 = s2.length();

	int idx = (len1 < len2 ? len2 : len1) - 1;
	for (; idx >= 0; --idx)
	{
		// 将当前下标对应的两个字符代表的数字，加到进位变量 
		carry += (idx < len1 && s1[idx] == '1' ? 1 : 0) + (idx < len2 && s2[idx] == '1' ? 1 : 0);
		resultStr.insert(head, (carry % 2 == 0) ? '0' : '1');
		carry = (carry >= 2) ? 1 : 0;
	}

	if (carry == 1) resultStr.insert(head, '1');
	
	return resultStr;
}

int main()
{
	string s1 = "1010";
	string s2 = "1011";

	cout << BinaryPlus(s1, s2) << endl;

	return 0;
}

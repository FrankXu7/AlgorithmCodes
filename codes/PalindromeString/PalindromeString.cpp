/**************************************************************************************************
 * 【题目描述】
 * 给定一个字符串，只考虑其中的字母和数字，判断它是否为一个回文字符串。
 * 其中字母不区分大小写，如果是空字符串，也被认为是回文字符串。
 *
 * 【输入】
 * str="A...B.B..A"
 * 【输出】
 * 是回文字符串
 *
 * 【解题思路】
 * 考虑使用双指针，遍历到字符串中点为止。
 * 遍历过程中，排除非字母和数字字符，因题目要求不区分大小写，故将大写字母转化为小写，
 * 在此情况下，判断两个字符是否相等，遇到不相等的就可以中止判断了。
 * 
 * 字符判断使用ASCII码判断。
 *
 * 【解题分析】
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-10
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

char FormatChar(char ch);

/**
 * @brief 数字和字母的ASCII码：
 * [0-9]:[48-57];
 * [A-Z]:[65-89];
 * [a-z]:[97-122];
 */
bool PalindromeString(string& str)
{
	if (str.empty()) return true;

	bool isPalindrome = true;

	unsigned int leftIdx = 0;
	unsigned int rightIdx = str.length() - 1;

	char leftChar = '\0';
	char rightChar = '\0';

	while (leftIdx < rightIdx)
	{
		if (!leftChar) leftChar = FormatChar(str[leftIdx]);
		if (!leftChar)
		{
			++leftIdx;
			continue;
		}

		if(!rightChar) rightChar = FormatChar(str[rightIdx]);
		if (!rightChar)
		{
			--rightIdx;
			continue;
		}

		// 执行到此，左右字符存在且必然是小写字母和数字，若不相等就可以直接中止处理了 
		if (leftChar != rightChar)
		{
			isPalindrome = false;
			break;
		}

		++leftIdx;
		--rightIdx;
	}

	return isPalindrome;
}

/**
 * @brief 判断字符是否属于数字或字母
 * @param ch 传入的字符
 * @return 若是字母或数字，返回该字符，且如果是大写字母，转化为小写返回，否则返回空字符
 */

char FormatChar(char ch)
{
	if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z')) return ch;
	else if ('A' <= ch && ch <= 'Z') return (ch + 32); // 相同大小写字母ASCII码值相差32，通过+32转化为小写字母 
	else return '\0';
}

int main()
{
	string str = "A man, a plan, a canal: Panama";
	cout << "Operate string:\n";
	cout << str << endl;

	cout << "Is a palindrome string: " << (PalindromeString(str) ? "YES\n" : "NO\n");

	return 0;
}
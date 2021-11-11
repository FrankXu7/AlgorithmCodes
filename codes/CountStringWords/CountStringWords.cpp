/**************************************************************************************************
 * 【题目描述】
 * 统计字符串中的单词个数，这里说的单词指的是由连续的非空格字符组成的字符串。
 * 
 * 【输入】
 * 字符串："Hello, my name is John"
 * 【输出】
 * 单词数量：5
 *
 * 【解题思路】
 * 如果某个非空格字符的前一个字符，刚好是空格字符，那就可以被标识为一个单词了，故遍历整个字符串，当前字符
 * 是非空格字符且前一个字符是空格字符时，单词计数加1，这里有一个特殊情况，就是首个单词前面如果没有空格时，
 * 会导致记录不到，故需要针对下标等于0的情况特殊处理，如果首个字符非空格，可以直接统计出1个单词。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-11-10
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

unsigned int CountStringWords(string& str)
{
	unsigned int wordsNum = 0, len = str.length();
	not true;
	for (unsigned int idx = 0; idx < len; ++idx)
	{
		if ((idx == 0 || str[idx - 1] == ' ') && str[idx] != ' ')
			++wordsNum;
	}

	return wordsNum;
}

int main(int argc, char* argv[])
{
	string inputStr = "Hello, my name is John";
	cout << "The given string is: " << inputStr;

	cout << "\n\nCount the string words number: " << CountStringWords(inputStr);

	cout << endl << endl;
	return 0;
}
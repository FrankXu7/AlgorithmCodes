/**************************************************************************************************
 * 【题目描述】
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。s 由英文字母、数字、符号和空格组成。
 * 
 * 【输入】
 * string="pwwkew"
 * 【输出】
 * 不重复字符的子串最长长度：3，即为子串 "wke"
 * 
 * 【解题思路】
 * 滑动窗口，用一个无序的set集合，存储遍历到的不重复字符，若发现重复字符，则表明当前的set集合中为一个不重
 * 复字符的子串，记录其长度后清空集合，然后从当前发现重复的字符开始，继续遍历。这里的set集合即充当了判断
 * 字符的重复性，也相当于是窗口。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1) 题意中给定字符串有字符限制，故实际为O(26*2 + 10 + 1)，复杂度可视作常数
 * 
 * @author FrankX
 * @date 2021-12-30
 *************************************************************************************************/
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

unsigned int MaxNoRepeatSubStr(string str)
{
	unsigned int maxCount = 0;
	unordered_set<char> subStr;
	for (char ch : str)
	{
		if (subStr.find(ch) != subStr.end())
		{
			if (subStr.size() > maxCount) 
				maxCount = subStr.size();
			subStr.clear();
		}

		subStr.emplace(ch);
	}

	return maxCount;
}

int main(int argc, char** argv)
{
	string str = "abac  aabcbb";
	cout << "The given string: " << str;

	cout << "\n\nMax no repeat substring length: " << MaxNoRepeatSubStr(str);

	cout << endl << endl;
	return 0;
}
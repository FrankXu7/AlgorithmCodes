/**************************************************************************************************
 * 【题目描述】
 * 判断两个给定字符串是否互相同构，两个字符串长度相等。同构：即两个字符串s和t，s中的字符仅有一种方式映射
 * 到t，反之亦然。
 * 
 * 
 * 【输入】
 * s="abcddd" t="defggg"
 * 【输出】
 * 是同构字符串
 * 
 * 【解题思路】
 * 利用两个Map，以一个字符串中的字符作为key，另一个字符串中同下标的字符作为value，构造两个映射关系。当存
 * 在一对多映射时，不满足同构条件。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(N) 最坏的情况是2N，即字符串同构，且串内无相同字符
 *
 * @author FrankX
 * @date 2021-08-27
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <map>
using namespace std;

bool IsomorphismString(const string& s, const string& t)
{
	unsigned int cycleCount = min(s.length(), t.length());
	map<char, char> sMt, tMs;

	for (unsigned int idx = 0; idx < cycleCount; ++idx)
	{
		if (sMt.find(s[idx]) == sMt.end())
		{
			sMt[s[idx]] = t[idx];
		}
		else if (sMt[s[idx]] != t[idx])
		{
			return false;
		}

		if (tMs.find(t[idx]) == tMs.end())
		{
			tMs[t[idx]] = s[idx];
		}
		else if (tMs[t[idx]] != s[idx])
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	string s = "abc4";
	string t = "defd";

	cout << "String 1: " << s << "\nString 2: " << t << endl;
	cout << "Is isomorphism string? " << (IsomorphismString(s, t) ? "YES" : "NO");

	cout << endl << endl;
	return 0;
}
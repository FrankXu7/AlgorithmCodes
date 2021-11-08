/**************************************************************************************************
 * 【题目描述】
 * 给定一个字符串，找到它的第一个不重复的字符，并返回其所在下标，如果不存在，则返回-1；
 * 
 * 【输入】
 * Input String="leetcode love!"
 * 【输出】
 * Index=3
 *
 * 【解题思路】
 * 判断字符串中的字符是否不重复，首先想到的便是统计它们，使用一个无序的map统计各个字符出现的次数，需要找
 * 出只出现一次的字符，按题意还要找到第一个这样的字符，因为map的元素顺序可能和插入顺序不一致，故统计后需
 * 要再次遍历字符串，找到首个统计次数为1的字符，并返回其下标；
 * 
 * 【解题分析】
 * 时间复杂度：O(N) 实际为O(logN)，统计字符数量和找出首个不重复字符，分别需要进行一次遍历
 * 空间复杂度：O(N) 最坏的情况就是字符串中每个字符都不重复
 *
 * @author FrankX
 * @date 2021-10-20
 **************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int FirstUniqueChar(string& str)
{
	// 统计各字符在字符串出现的次数 
	unordered_map<char, unsigned int> countMap;

	decltype(countMap)::iterator endItr = countMap.end();
	for (auto&ch : str)
	{
		if (countMap.find(ch) == endItr)
			countMap.insert(make_pair(ch, 1));
		else
			++countMap[ch];
	}

	// map元素顺序可能不同于插入顺序，故需遍历字符串在map中找到首个统计次数为1的字符的下标 
	unsigned int strLen = str.length();
	for (unsigned int idx = 0; idx < strLen; ++idx)
	{
		if (countMap[str[idx]] == 1)
		{
			return idx;
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	string inputStr = "leetcode love!";

	cout << "Input string: " << inputStr
		<< "\n\nThe first unique character's index is: " << FirstUniqueChar(inputStr);

	cout << endl << endl;
	return 0;
}
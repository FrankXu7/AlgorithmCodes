/**************************************************************************************************
 * 【题目描述】
 * 给定一种规律 pattern 和一个字符串 str，判断 str 是否遵循相同的规律。这里的规律指的是 pattern 中的每个
 * 字母和字符串 str 的每个非空单词存在映射关系。其中，pattern 中的空格字符被认为无效，str 中的空格被用来
 * 分割单词。
 *
 * 【输入】
 * pattern = "abab"
 * str = "cat dog cat dog"
 * 【输出】
 * true
 *
 * 【解题思路】
 * 本质上就是确立 pattern 中某个字符映射到 str 中对应的单词，并且 pattern 中所有该字符都能映射到 str 中
 * 同一个单词。利用无序map建立映射关系，依次遍历 pattern 中的字符，同时提取 str 中用空格分割的单词，空格
 * 可能有多个连续的，被处理为一个空格，如果不存在于map，则新建映射，否则将映射的单词与提取的单词进行比较。
 * 当 patter 遍历完成后，需要检查 str 是否还有剩余单词，因为按题意 pattern 应该与 str 中的单词一一对应。
 * 
 * 【解题分析】
 * 时间复杂度：O(M+N) 需要遍历 pattern 和 str，两个字符串中每个字符都只访问依次 
 * 空间复杂度：O(M+N) 如果 pattern 中存在相同字符，实际上要小于该空间复杂度，无序map只存储映射关系 
 *
 * @author FrankX
 * @date 2021-09-23
 **************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool WordsPattern(string& pattern, string& str)
{
	unordered_map<char, string> wordsMap;
	
	unsigned int idx = 0;
	unsigned int strLen = str.length();
	string curWord = "";

	for (auto ch : pattern)
	{
		// 排除规则中的空格字符 
		if (ch == ' ') continue;
		// 规则字符数大于单词数 
		if (idx >= strLen) return false;

		// 提取单词 
		curWord = "";
		while (idx < strLen)
		{
			// 排除掉单词间的空格，包含空格有多个的情况 
			if (str[idx] == ' ')
			{
				if (curWord.length()) break;
				++idx;
			}
			else 
				curWord += str[idx++];
		}

		if (wordsMap.find(ch) == wordsMap.end())
		{
			// 添加新的映射关系 
			wordsMap.insert(make_pair(ch, curWord));
			continue;
		}
		else if (wordsMap[ch] != curWord)
		{
			// 已存在的映射和当前单词不匹配 
			return false;
		}
	}

	return (idx >= strLen);
}

int main(int argc, char** argv)
{
	string pattern = "abab";
	string str = "cat dog cat dog";

	cout << "Pattern string (no space): " << pattern;
	cout << "\nWords string (must divide by space): " << str;

	cout << "\n\nAre the words mattching the pattern? " 
		<< (WordsPattern(pattern, str) ? "YES" : "NO");

	cout << endl << endl;
	return 0;
}
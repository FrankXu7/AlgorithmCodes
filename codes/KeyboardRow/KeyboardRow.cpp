/**************************************************************************************************
 * 【题目描述】
 * 给你一个字符串数组 words ，只返回可以使用在 美式键盘 同一行的字母打印出来的单词。美式键盘中：
 * (1) 第一行由字符 "QWERTYUIOP" 组成。
 * (2) 第二行由字符 "ASDFGHJKL" 组成。
 * (3) 第三行由字符 "ZXCVBNM" 组成。
 * 
 * 【输入】
 * words = ["Hello","Alaska","Dad","Peace"]
 * 【输出】
 * 可在键盘一行字母中打印的字符串：["Alaska","Dad"]
 * 
 * 【解题思路】
 * 方法一：
 * 定义一个局部静态无序map变量，保存26个大写字母分别所在的行数，循环过程中将遍历到的小写字母转换为大写字
 * 母来处理，针对每个单词，判断除首个字符外所有字符是否和首个字符在同一行（这样可以减少局部变量的定义），
 * 遇到不在同一行的情况是跳出循环，并以循环下标作为标识判断当前单词是否满足题意，然后推入返回数组。
 * 
 * 方法二：
 * 可以简化方法一中的map变量，用一个字符串（letterRow）来标识各个大写字母所在行数，该字符串有26个字符表
 * 示A-Z的大写英文字母，对应下标位置的字符表示当前字母所在行数，然后和方法一原理类似，通过比较每个单词，
 * 除首字符外所有字符的大写字母下标在 letterRow 中对应的行数来判断是否满足题意。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为字符串数组中每个字符串长度的总和 
 * 空间复杂度：O(1) 实际为26，即所有大写英文字母都需要存储一份在无序map中
 * 方法二：
 * 时间复杂度：O(N) 实际为字符串数组中每个字符串长度的总和 
 * 空间复杂度：O(1) 实际为26，字母行数的字符串需要存储的字符个数 
 * 
 * @author FrankX
 * @date 2021-12-22
 *************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// 返回英文字母的大写 
#define CAPITAL(ch) ('a' <= ch && ch <= 'z' ? ch - 32 : ch)

vector<string> KeyboardRow_1(vector<string>& words)
{
	// 英文字母总共就3行，定义局部静态变量 
	static unordered_map<char, int> chRowMap{
		{'Q', 1}, {'W', 1}, {'E', 1}, {'R', 1}, {'T', 1}, {'Y', 1}, {'U', 1}, {'I', 1}, {'O', 1}, {'P', 1},
		{'A', 2}, {'S', 2}, {'D', 2}, {'F', 2}, {'G', 2}, {'H', 2}, {'J', 2}, {'K', 2}, {'L', 2} ,
		{'Z', 3}, {'X', 3}, {'C', 3}, {'V', 3}, {'B', 3}, {'N', 3}, {'M', 3}
	};

	vector<string> rowStrArr;
	char curCh = '\0';
	unsigned int chIdx = 0;
	for (string& str : words)
	{
		for (chIdx = 1; chIdx < str.length(); ++chIdx)
		{
			curCh = CAPITAL(str[chIdx]);
			if (chRowMap.find(curCh) == chRowMap.end() || chRowMap[curCh] != chRowMap[str[0]])
				break;
		}

		if (chIdx >= str.length())
		{
			rowStrArr.emplace_back(str);
		}
	}

	return rowStrArr;
}

vector<string> KeyboardRow_2(vector<string>& words)
{
	// 对应下标字符表示按顺序书写的26个大写字母所在行数，比如字母A在第2行，字母B在第3行 
	static string letterRow = "23321222122233111121131313";

	vector<string> rowStrArr;
	unsigned int chIdx = 0;
	for (string& str : words)
	{
		for (chIdx = 1; chIdx < str.length(); ++chIdx)
		{
			if (letterRow[CAPITAL(str[chIdx]) - 'A'] != letterRow[CAPITAL(str[0]) - 'A'])
				break;
		}

		if (chIdx >= str.length())
		{
			rowStrArr.emplace_back(str);
		}
	}

	return rowStrArr;
}


int main(int argc, char** argv)
{
	vector<string> words{ "Hello", "Alaska", "Dad", "Peace" };
	cout << "The strings of string array:\n";
	for (string& str : words) cout << str << ", ";

	vector<string> rowStrArr1 = KeyboardRow_1(words);
	cout << "\n\n[Solution 1] Type in one keyboard row strings:\n";
	for (string& str : rowStrArr1) cout << str << ", ";

	vector<string> rowStrArr2 = KeyboardRow_2(words);
	cout << "\n\n[Solution 2] Type in one keyboard row strings:\n";
	for (string& str : rowStrArr2) cout << str << ", ";

	cout << endl << endl;
	return 0;
}
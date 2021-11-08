/**************************************************************************************************
 * 【题目描述】
 * 搜索字符串中是否包含某个子字符串，返回其下标；
 * （1）当子字符串为空串，返回下标0；
 * （2）当子字符串长度大于搜索字符串长度，返回-1；
 *
 * 【输入】
 * haystack="1266634", needle="666"
 * 【输出】
 * 是否有效括号配对
 * index=2
 *
 * 【解题思路】
 * 遍历搜索字符串，如果发现某个字符和子字符串首字符相同，则标识开始匹配，当字符串搜索完后，即得到结果；如
 * 果匹配搜索发现有字符不相等，需要重置搜索数据（重置记录的搜索起始下标和搜索下标）；特殊情况：当首字符相
 * 等，开始匹配时，如果子字符串长度，大于搜索字符串剩余未比较字符数，返回-1，标识未匹配到。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-04-01
 **************************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int StrStr(string& haystack, string& needle)
{
	if (needle.length() == 0) return 0;
	else if (needle.length() > haystack.length()) return -1;

	int strIdx = -1;
	unsigned int searchIdx = 0;

	for (unsigned int idx = 0; idx < haystack.length(); ++idx)
	{
		if (haystack[idx] == needle[searchIdx])
		{
			if (strIdx == -1)
			{
				// 开始匹配时，子字符串大于目标字符串剩余未匹配字符数，标识为未匹配到
				if (haystack.length() - idx < needle.length() - searchIdx) break;
				strIdx = idx;
			}
			++searchIdx;

			// 子字符串搜索完成，且匹配到
			if (searchIdx >= needle.length()) break;
		}
		else if (searchIdx > 0)
		{
			// 之前的匹配不成功，重置搜索数据
			strIdx = -1;
			searchIdx = 0;
		}
	}

	return strIdx;
}

int main()
{
	string haystack = "";
	string needle = "";

	cout << "Input target string: " << endl;
	cin >> haystack;
	cout << "Input search string:" << endl;
	cin >> needle;

	cout << "Search Index: " << StrStr(haystack, needle) << endl;

	return 0;
}


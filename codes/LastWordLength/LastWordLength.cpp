/**************************************************************************************************
 * 【题目描述】
 * 刷出一句英文中最后一个单词的长度，单词以空格分割。
 *
 * 【输入】
 * string="Hello world"
 * 【输出】
 * lastWorldLen=5
 *
 * 【解题思路】
 * 反序遍历字符串，遇到空格或tab即停止，需要特别注意的是，最后一个单词后，可能还会有空格和tab，需要排除。
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

unsigned int LastWordLength(string& str)
{
	unsigned int len = 0;
	for (int idx = str.length() - 1; idx >= 0; --idx)
	{
		if (str[idx] != ' ' && str[idx] != '\t')
			++len;
		else if (len > 0) // 此处长度必须大于零是为了排除字符串末尾有空格或tab 
			break;
	}

	return len;
}

int main()
{
	string inputStr = "";
	cout << "Input string: ";
	getline(cin, inputStr);
	
	cout << "Last world length: " << LastWordLength(inputStr) << endl;

	return 0;
}

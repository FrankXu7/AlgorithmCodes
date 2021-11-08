/**************************************************************************************************
 * 【题目描述】
 * 匹配括号对，若存在非括号字符，或括号无法一一按序配对，则匹配失败。
 * 正确匹配：(([][{}]))，非一一配对：({)
 *
 * 【输入】
 * string="(([][{}]))"
 * 【输出】
 * 是否有效括号配对
 *
 * 【解题思路】
 * 考虑到遍历字符串的时候需要判断是否属于括号，且括号类字符有多种，本题中有圆括号、方括号和大括号，故使用
 * 无序map，以括号字符作为key来匹配遍历字符。匹配到key为左括号时，往栈中压入左括号key对应的右括号，期望后
 * 续遍历中遇到该右括号以完成配对；匹配到key为右括号时，若与栈顶的右括号相等，则顺利完成一次匹配，弹出栈
 * 顶字符，期望后续遍历遇到新栈顶右括号；匹配到非括号字符，或遍历完成后栈中还剩余待配对的括号，则匹配失败，
 * 字符串不是有效括号对。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-03-30
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

unordered_map<char, char> brackets = 
{
	{'(', ')'},
	{'[', ']'},
	{'{', '}'},
	{')', 0},
	{']', 0},
	{'}', 0},
};

bool PairBrackets(string& str)
{
	stack<char> desired;

	for (unsigned int idx = 0; idx < str.length(); ++idx)
	{
		// 这里判断时不能直接用[]操作符，否则map中没有操作符指定的key时，会自动添加一个 
		if (brackets.count(str[idx]) != 0)
		{
			if (brackets[str[idx]] != 0)
				desired.push(brackets[str[idx]]);
			else if (!desired.empty() && str[idx] == desired.top())
				desired.pop();
			else
				return false;
		}
		else
			return false;
	}

	return desired.empty();
}

int main()
{
	cout << "Input: ";
	string inputStr = "";
	cin >> inputStr;
	cout << (PairBrackets(inputStr) ? "Pairs Match!" : "Invalid pairs!") << endl;

	return 0;
}

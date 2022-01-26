/**************************************************************************************************
 * 【题目描述】
 *
 *
 * 【输入】
 *
 * 【输出】
 *
 * 【解题思路】
 *
 *
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-01-26
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * @brief 辅助函数，判断一个字符串中的圆括号是否配对
 * @param str
 * @return 返回是否配对的bool值
 */
bool DetermineMatch(string& str)
{
	/**
	 * 左右括号是否配对平衡，每匹配到一个左括号，自加，反之则自减。所以在循环内，balance 的值肯定大于等于
	 * 0，如果出现 balance < 0，即代表首先出现了右括号，或出现了非圆括号字符，所以不可能会配对；而执行完
	 * 循环后，只有当 balace = 0 成立时才表示整个字符串中圆括号配对。
	 */
	int balance = 0;
	for (char ch : str)
	{
		if (ch == '(') ++balance;
		else --balance;

		if (balance < 0) return false;
	}

	return (balance == 0);
}

void Recursion_DFS_1(vector<string>& parentheses, string& curStr, int num)
{
	if (curStr.length() == num) // 深度遍历触底 
	{
		if (DetermineMatch(curStr))
			parentheses.emplace_back(curStr);
		return;
	}

	curStr.push_back('(');
	Recursion_DFS_1(parentheses, curStr, num);
	curStr.pop_back();

	curStr.push_back(')');
	Recursion_DFS_1(parentheses, curStr, num);
	curStr.pop_back();
}
vector<string> GenerateParentheses_1(int num)
{
	vector<string> parentheses;
	string curStr = "";
	
	Recursion_DFS_1(parentheses, curStr, num * 2);
	
	return parentheses;
}

void Recursion_DFS_2(vector<string>& parentheses, string& curStr, int left, int right, int num)
{
	if (curStr.length() == num * 2)
	{
		parentheses.emplace_back(curStr);
		return;
	}

	if (left < num)
	{
		curStr.push_back('(');
		Recursion_DFS_2(parentheses, curStr, left + 1, right, num);
		curStr.pop_back();
	}

	if (right < left)
	{
		curStr.push_back(')');
		Recursion_DFS_2(parentheses, curStr, left, right + 1, num);
		curStr.pop_back();
	}
}
vector<string> GenerateParentheses_2(int num)
{
	vector<string> parentheses;
	string curStr = "";
	int left = 0, right = 0;

	Recursion_DFS_2(parentheses, curStr, left, right, num);

	return parentheses;
}

int main(int argc, char* argv[])
{
	int num = 3;
	cout << "The parenthese number: " << num;

	vector<string> parentheses1 = GenerateParentheses_1(num);
	cout << "\n\n[Solution 1] Generate parentheses:\n";
	for (string& str : parentheses1) cout << str << ", ";

	vector<string> parentheses2 = GenerateParentheses_2(num);
	cout << "\n\n[Solution 2] Generate parentheses:\n";
	for (string& str : parentheses2) cout << str << ", ";

	cout << endl << endl;
	return 0;
}
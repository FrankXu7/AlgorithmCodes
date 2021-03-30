/**
 * 【题目描述】
 * 将给定的罗马数字，范围限定在[1, 3999]，超出定义域或罗马数字组合非法，则返回-1；
 * 
 * 罗马数字只包含下列字符：
 * {
 *		I=1,	V=5,
 *		X=10,	L=50,
 *		C=100,	D=500,
 *		M=1000,
 * }
 * 
 * 通常情况下，罗马数字中小的数字在大的数字右边，但存在以下6中情况例外：
 * {
 *		IV=4,	IX=9,
 *		XL=40,	XC=90,
 *		CD=400,	CM=900,
 * }
 * 
 * 【输入】
 * roman number=VII
 * 【输出】
 * integer=7
 *
 * @author FrankX
 * @date 2021-03-30
 */
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>
#include <iterator>

using namespace std;

map<char, int> numMap = {
	{'I', 1}, {'V', 5},
	{'X', 10}, {'L', 50},
	{'C', 100}, {'D', 500},
	{'M', 1000},
	{'i', 1}, {'v', 5},
	{'x', 10}, {'l', 50},
	{'c', 100}, {'d', 500},
	{'m', 1000},
};

int RomanToInteger(vector<char>& str)
{
	return 0;
}

int main()
{
	vector<char> inputStr;

	cout << "Roman numeral: ";
	char tempChar = '\0';
	while ((tempChar = cin.get()) != '\n')
	{
		inputStr.push_back(tempChar);
	}
	RomanToInteger(inputStr);

	return 0;
}

还未完成

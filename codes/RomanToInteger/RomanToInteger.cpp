/**************************************************************************************************
 * 【题目描述】
 * 将给定的罗马数字，范围限定在[1, 3999]，超出定义域或罗马数字组合非法，则返回-1；
 *
 * 罗马数字只包含下列字符：
 * {
 *		I=1,
 *		V=5,	X=10,
 *		L=50,	C=100,
 *		D=500,	M=1000,
 * }
 *
 * 通常情况下，罗马数字中小的数字在大的数字右边，但存在以下6中情况例外：
 * {
 *		IV=4,	IX=9,
 *		XL=40,	XC=90,
 *		CD=400,	CM=900,
 * }
 *
 * 补充：罗马数字按题意最大只能表示到4999，即 MMMMCMXCIX，从5000开始，字母的书写会在【字母上加一横线】，
 * 打不出来，加在右上方：
 * 5000    V￣
 * 10000   X￣
 * 50000   L￣
 * 100000  C￣
 * 500000  D￣
 * 1000000 M￣
 *
 * 【输入】
 * roman number=VII
 * 【输出】
 * integer=7
 *
 * 【解题思路】
 * 遍历字符串，判断当前字符是否存在于数字映射map中，是的话将对应的值加到结果值。这里需要特别注意的是那六
 * 种特殊情况，特殊是因为一般罗马字母数字大的在数字小的左侧，而这六种情况则相反，数字小的在数字大的左侧，
 * 如：X(10)C(100)，C(100)M(1000)，可以得出一个规律：六种特殊情况的组合，都是“左小右大”的情况，不包含字
 * 母I，最重要的是，组合的值等于数字大的减去数字小的，例如：
 * XC = 90 = C(100) - X(10)
 * CM = 900 = M(1000) - C(100)
 * 所以，当遍历到当前字母时，预先判断下一个字母是否会比当前字母更大，即为特殊情况，且在处理完特殊情况后，
 * 下一个字母相当于消耗掉了，index需要加1，当然，所有的字母都需要存在于数字映射map中。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-18
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

/**
 * 大写字母的ASCII码值比小写字母更小，ASCII码：'a'(97) - 'A'(65) = 32，题中给定的罗马数字的字符串中，将
 * 小写字母都转换为大写字母来处理
 */
unordered_map<char, unsigned int> numMap = {
   {'I', 1},
   {'V', 5},	{'X', 10},
   {'L', 50},	{'C', 100},
   {'D', 500},	{'M', 1000},
};

// 六种特殊情况 
unordered_multimap<char, char> specialCase = {
   {'I', 'V'},{'I', 'X'},
   {'X', 'L'},{'X', 'C'},
   {'C', 'D'},{'C', 'M'},
};

unsigned int RomanToInteger(string str)
{
	unsigned int dataSize = str.size(), resultNum = 0;
	char curCh = '\0', nextCh = '\0';

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		curCh = (str[idx] >= 'a') ? (str[idx] - 32) : (str[idx]);
		if (numMap.find(curCh) == numMap.end()) return 0;

		if (idx + 1 < dataSize)
		{
			// 小写转大写，兼容大小写情况 
			nextCh = (str[idx + 1] >= 'a') ? (str[idx + 1] - 32) : (str[idx + 1]);
			if (numMap.find(nextCh) == numMap.end()) return 0;
		}

		// 下一个字母比当前字母更大，且存在于数字映射map中 
		if (numMap[nextCh] > numMap[curCh])
		{
			// 字母符合“左小右大”的特殊情况有很多种，但只有六种有效 
			if (specialCase.find(curCh) == specialCase.end()) return 0;

			resultNum += (numMap[nextCh] - numMap[curCh]);
			// 跳过已处理的字母 
			++idx;
		}
		else
			resultNum += numMap[curCh];

		nextCh = '\0';
	}

	return (resultNum >= 5000 ? 0 : resultNum);
}

int main()
{
	string inputStr = "VIiI";
	cout << "Input roman numerals (limits number 1 to 4999) : " << inputStr;

	unsigned int resultNum = RomanToInteger(inputStr);
	if (resultNum > 0)
		cout << "\n\nThe Corresponding number: " << resultNum;
	else
		cout << "\n\n[error] Invalid Roman numerals input!";

	cout << endl << endl;
	return 0;
}

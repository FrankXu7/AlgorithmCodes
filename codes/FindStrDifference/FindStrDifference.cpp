/**************************************************************************************************
 * 【题目描述】
 * 给定两个字符串 s 和 t，其中字符串 t 由 字符串 s 随机重排，然后在字符串 t 中随机位置插入一个字符；找出
 * 在字符串 t 中新插入的字符；
 * 
 * 【输入】
 * s="abcde" t="dbafce"
 * 【输出】
 * 返回字符 'f'
 * 
 * 【解题思路】
 * 方法一：
 * 由题可知字符串 t 中会比 s 多一个字符，可以先用一个无序map统计字符串 s 中各字符数量，然后遍历字符串 t 
 * 和 s 中相同的字符，将无序map中对应字符的统计数量减1；当遇到不存在于字符串 s 中的字符，或统计数量为0时，
 * 则当前遍历到的字符即为 t 中新插入的字符；
 * 
 * 方法二：
 * 利用异或位运算性质：
 * （1）两个相同的数字进行异或运算结果为0；
 * （2）异或运算满足交换律和结合律；
 * （3）一个数和0异或后结果不变；
 * 
 * 字符串 t 中除了新插入的那个字符之外，其余字符都和字符串 s 中相同，故可将两个字符串中所有字符都进行异或
 * 运算，相同的字符两两异或为0，最后剩下的值，就是字符串 t 中新插入的字符；
 * 
 * 方法三：
 * 因为字符串 t 中除了新插入的那个字符之外，其余字符都和字符串 s 中相同，故可以分别计算两个字符串各个字符
 * 相加之和，可知字符串 t 的字符之和必大于字符串 s 的字符之和，两和之差，即为字符串 t 中新插入的字符；
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N) 最差的情况是字符串 s 中没有重复字符
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(N) 实际为O(2N)，需要分别遍历两个字符串求各字符串之和
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-10-20
 **************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

char FindStrDifference_1(string& s, string& t)
{
	unordered_map<char, unsigned int> sMap;
	for (auto& ch : s)
		++sMap[ch];

	decltype(sMap)::iterator endItr = sMap.end();
	for (auto& ch : t)
	{
		if (sMap.find(ch) == endItr || sMap[ch] == 0)
			return ch;

		--sMap[ch];
	}

	return '\0';
}

char FindStrDifference_2(string& s, string& t)
{
	unsigned int sLen = s.length();
	unsigned int tLen = t.length();

	unsigned int ch = 0;
	for (unsigned int idx = 0; (idx < sLen || idx < tLen); ++idx)
	{
		if (idx < sLen)
			ch ^= s[idx];
		if (idx < tLen)
			ch ^= t[idx];
	}

	return static_cast<char>(ch);
}

char FindStrDifference_3(string& s, string& t)
{
	unsigned int sSum = 0;
	for (auto& ch : s)
		sSum += ch;

	unsigned int tSum = 0;
	for (auto& ch : t)
		tSum += ch;

	// t由s随机重排而成，且增加了一个字符，所以tSum必大于sSum 
	unsigned int ch = tSum - sSum;

	return static_cast<char>(ch);
}


int main(int argc, char* argv[])
{
	string s = "abcde";
	string t = "dbeafc";

	cout << "String s: " << s
		<< "\nString t: " << t;

	cout << "\n\n[Solution 1] The added character in string t is: " << FindStrDifference_1(s, t);

	cout << "\n\n[Solution 2] The added character in string t is: " << FindStrDifference_2(s, t);

	cout << "\n\n[Solution 3] The added character in string t is: " << FindStrDifference_3(s, t);

	cout << endl << endl;
	return 0;
}
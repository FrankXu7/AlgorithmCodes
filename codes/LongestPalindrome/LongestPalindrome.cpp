/**************************************************************************************************
 * 【题目描述】
 * 给定一个字符串，找到通过这个字符串中字符所构成的最长回文字符串。
 * 
 * 字符区分大小写，每个字符只能使用一次。
 * 
 * 【输入】
 * The given string: "abccccdd"
 * 【输出】
 * The longest palindrome: 7
 * 
 * 【解题思路】
 * 利用贪心算法的思路，将每个字符使用其数量的最大偶数次，保证回文串尽可能的长。字符数量是偶数，显然它的最
 * 大偶数次就是该数值本身，而对于奇数，减1后即为其最大偶数。先用一个无序map统计出各个字符的数量，然后对字
 * 符数量大于1的字符，使用其最大偶数次。而对于只出现一次的字符，因为回文串中，仅出现一次的字符至多只能有
 * 一个，且位于回文串正中间，它也会使得回文串的长度变成奇数，故遍历到字符数量为1时，可通过判断当前的回文
 * 串长度的奇偶性，来判断是否可以添加这个仅出现一次的字符。
 * 
 * 【解题分析】
 * 时间复杂度：O(N) 实际为O(2N)，构造无序map和计算回文串各需遍历一次 
 * 空间复杂度：O(N) 统计各个字符出现的次数，最差的情况是O(N)，即每个字符只出现一次 
 * 
 * @author FrankX
 * @date 2021-11-05
 **************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

unsigned int LongestPalindrome(string& str)
{
	unsigned int palindromeLen = 0;
	 
	// 统计各个字符出现的次数 
	unordered_map<char, unsigned int> chCount;
	for (auto& ch : str)
	{
		++chCount[ch];
	}
	 
	for (auto& element : chCount)
	{
		if (element.second > 1)
		{
			// 将字符使用偶数次，如果是奇数，则减1后为其最大偶数 
			palindromeLen += ((element.second & 1) ? element.second - 1 : element.second);
		}
		else if (element.second & 1)
		{
			// 回文串中至多只会出现一个数量是1的字符，且在回文串的正中间，它会使回文串的长度为奇数 
			++palindromeLen;
		}
	}
	 
	return palindromeLen;
}

int main(int argc, char** argv)
{
	string str = "abccccdd";

	cout << "The given string: " << str;

	cout << "\n\nThe longest palindrome string: " << longestPalindrome(str);

	cout << endl << endl;
	return 0;
}

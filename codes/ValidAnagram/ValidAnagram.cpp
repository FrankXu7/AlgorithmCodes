/**************************************************************************************************
 * 【题目描述】
 * 判断两个给定字符s和t是否为异位词，如果两个字符串中每个字符出现的次数都是一样的，则s和t互为异位词。
 *
 * 【输入】
 * s="abcd"
 * t="bcad"
 * 【输出】
 * true
 *
 * 【解题思路】
 * 方法一：
 * 可以使用一个map来统计字符串s中各个字符的数量，然后再遍历字符串t，每次遍历时t的字符与记录在map中s的字符
 * 相同时，将map统计的对应字符数量自减（即使没有也不影响，自减为负数，表示t中的字符在s中不存在），
 * 如果两个字符串是异位词，那map中各个字符的统计数量是0，只要遇到字符数量不为0，可直接返回false；
 * 
 * 方法二：
 * 按照异位词的定义，如果两个字符串是异位词，那么在排序后两个字符串应该相等。所以可以先对两个字符串来一波排序，
 * 然后比较字符串是否相等，相等表示是异位词，返回true；
 * 
 * 这两个方法需要注意的是，优先判断两个字符长度，长度不同，必然不是异位词；
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(3N)，统计字符串s中的字符数量，比较自减s和t相同的字符数量，检查map中字符统计数量 
 * 空间复杂度：O(N) 最差的情况就是字符串中每个字符唯一，需要O(N)的空间复杂度 
 * 方法二：
 * 时间复杂度：O(NlogN) 这里采用了语言自实现的排序算法，实际为O(logN + N)，排序为O(logN)，比较字符串为O(N) 
 * 空间复杂度：O(logN) 排序所需空间，依赖于语言自实现的排序算法 
 *
 * @author FrankX
 * @date 2021-09-15
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

bool ValidAnagram_1(string& s, string& t)
{
	// 长度不同必然不是异位词 
	if (s.size() != t.size()) return false;

	map<char, int> charMap;

	// 分类并统计字符串 s 的各类字符数量 
	for (string::iterator itr = s.begin(); itr != s.end(); ++itr)
	{
		++charMap[*itr];
	}

	// 将字符串 t 中与 s 相同的字符统计进行相减，最终剩下的就是统计两个字符串不同字符的数量 
	for (string::iterator itr = t.begin(); itr != t.end(); ++itr)
	{
		if (charMap.find(*itr) != charMap.end())
			--charMap[*itr];
	}

	// 如果最总字符map剩下有不为0的字符统计，表示有字符在两个字符串中出现次数不同 
	for (map<char, int>::iterator itr = charMap.begin(); itr != charMap.end(); ++itr)
	{
		if ((*itr).second != 0)
			return false;
	}
	
	return true;
}

bool ValidAnagram_2(string s, string t)
{
	if (s.size() != t.size()) return false;

	sort(s.begin(), s.end());
	sort(t.begin(), t.end());

	return (s == t);
}

int main(int argc, char** argv)
{
	string s = "这是一个字符串";
	string t = "这也是个字符串";

	cout << "The strings:\n" << s << endl << t;

	cout << "\n\n[Solution 1] Is Anagram Strings? " << (ValidAnagram_1(s, t) ? "YES\n" : "NO\n");

	cout << "\n\n[Solution 2] Is Anagram Strings? " << (ValidAnagram_2(s, t) ? "YES\n" : "NO\n");


	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 赎金信，给定一个赎金字符串 ransomStr 和一个杂志字符串 magazineStr，判断赎金字符串 ransomStr 中的字符
 * 是否都能通过杂志字符串 magazineStr 中的字符构成，是则返回true，否则返回false；
 * 
 * 要求杂志字符串中的 magazineStr 字符只能使用一次；
 * 
 * 【输入】
 * ransomStr="abc" magazineStr="dcbcaa"
 * 【输出】
 * true
 *
 * 【解题思路】
 * 将杂志字符串构建为一个无序map，并统计各个字符出现的次数。然后遍历赎金字符串中字符，如果存在于无序map，
 * 并且数量大于零，则数量自减1表示消耗掉一个字符。遇到不存在于无序map的字符，或数量为0表示已经消耗完的字
 * 符，则返回false代表无法匹配。
 * 
 * 【解题分析】
 * 时间复杂度：O(N) 实际为O(2N)，创建无序map和对比字符各自需要一轮遍历
 * 空间复杂度：O(N) 创建无序map所需空降
 *
 * @author FrankX
 * @date 2021-10-19
 **************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool RansomNote(string& ransomStr, string& magazineStr)
{
	unordered_map<char, unsigned int> magazineMap;
	for (auto& ch : magazineStr)
		++magazineMap[ch];

	for (auto& ch : ransomStr)
	{
		if (magazineMap.find(ch) != magazineMap.end() && magazineMap[ch] > 0)
			--magazineMap[ch];
		else
			return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	string ransomStr = "ababcx";
	string magazineStr = "ddcbbaa";

	cout << "Ransom String: " << ransomStr
		<< "\nMagazine String: " << magazineStr;

	cout << "\n\nCan compose ransom note? " 
		<< (RansomNote(ransomStr, magazineStr) ? "TRUE" : "FALSE");


	cout << endl << endl;
	return 0;
}
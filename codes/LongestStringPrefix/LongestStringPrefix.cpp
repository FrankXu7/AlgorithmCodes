/**************************************************************************************************
 * 【题目描述】
 * 找出字符串数组中的最长公共前缀
 *
 * 【输入】
 * str1="abcJHOOEMHRR"
 * str2="abcKOELERMH"
 * str3="abcDELEMRLLHLERLHSE"
 * 【输出】
 * strPre="abc"
 *
 * 【解题思路】
 * 以字符串数组中第一个字符串为基准，遍历余下字符串，
 * 从头开始，同一个下标时，各个字符串对应字符相同，即为公共字符串，直到出现同下标字符不同截止。
 *
 * 【解题分析】
 * 时间复杂度：O(N^2)
 * 空间复杂度：O(N)，可能多个字符串都是相同的字符串，故前缀为整个字符串。
 * 
 * @author FrankX
 * @date 2021-03-30
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

string LongestStringPrefix(vector<string>& strArr)
{
	string strPre = "";
	// 初始化为字符串数组的第一个字符串，减少一次遍历，同时也作为比较基准
	string firstStr = strArr[0];
	vector<string>::iterator itn;

	for (unsigned int m = 0; m < firstStr.length(); ++m)
	{
		for (itn = strArr.begin() + 1; itn != strArr.end(); ++itn)
		{
			// 某个字符串同下标处的字符，和第一个字符串的不同，前缀截止
			if (firstStr[m] != (*itn)[m]) break;
		}

		if (itn == strArr.end())
			strPre += firstStr[m];
		else 
			break;
	}

	return strPre;
}

int main()
{
	vector<string> inputStr;
	string tempStr = "";
	
	do
	{
		getline(cin, tempStr);
		if (tempStr != "") inputStr.push_back(tempStr);
	}
	while (tempStr != "");

	cout << "The longest common string prefix: " << LongestStringPrefix(inputStr) << endl;

	return 0;
}

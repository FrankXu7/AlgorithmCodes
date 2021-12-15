/**************************************************************************************************
 * 【题目描述】
 * 有一个密钥字符串 S ，只包含字母，数字以及 '-'（破折号）。其中， N 个 '-' 将字符串分成了 N+1 组。给你
 * 给你一个数字 K，请你重新格式化字符串，使每个分组恰好包含 K 个字符。特别地，第一个分组包含的字符个数必
 * 须小于等于 K，但至少要包含 1 个字符。两个分组之间需要用 '-'（破折号）隔开，并且将所有的小写字母转换为
 * 大写字母。
 * 
 * 给定非空字符串 S 和数字 K，按照上面描述的规则进行格式化。
 * 
 * 【输入】
 * S = "5F3Z-2e-9-w", K = 4
 * 【输出】
 * 输出："5F3Z-2E9W"
 *
 * 【解题思路】
 * 方法一：
 * 把 S 中除 ‘-’ 字符外的字符统称为有效字符。有效字符数量在不能整除 K 时题意要求放到第一组，所以先要统计
 * 有效字符数量，对 K 整除后即可得出第一组需要的字符数量。然后再次遍历字符串，除第一组特殊处理外，其它组
 * 均可以 K 的长度为一组添加到最终字符串末尾。
 * 
 * 方法二：
 * 因为题意要求只有第一组的字符数量才能不等于 K，故而不得已需要统计有效字符数量，可以反其道而行之，从字符
 * 串末尾开始以 K 的长度为一组添加到最终字符串末尾（最后一组有效字符可能不足 K 个），这样得到字符串是反转
 * 的，但是不需要关心第一组会有几个字符，然后再将最终字符串反转一次即为最终结果。
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(2N)，首轮遍历统计有效字符，再次遍历格式化密钥字符串 
 * 空间复杂度：O(N) 最终结果字符串，如果传入字符可修改的话，可传入引用在字符串原地处理 
 * 方法二：
 * 时间复杂度：O(N) 不需要关系第一组字符数量，一轮遍历即可，但字符串的反转可能会达到O(N)
 * 空间复杂度：O(N) 最终结果字符串，如果传入字符可修改的话，可传入引用在字符串原地处理 
 *
 * @author FrankX
 * @date 2021-12-15
 *************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

string FormatLicense_1(string str, int keyLen)
{
	int charNum = 0;
	for (char& ch : str)
	{
		if (ch != '-')
		{
			++charNum;
		}
	}

	// 确认第一组长度 
	int firstLen = charNum % keyLen;
	// 第一组至少要有1个字符，故整除时需要特殊处理 
	if (firstLen == 0) firstLen = keyLen;

	string resultStr = "";
	int divCount = 0;
	for (char ch : str)
	{
		if (ch == '-') continue;

		if ((divCount >= keyLen) || (firstLen && divCount >= firstLen))
		{
			if (firstLen) firstLen = 0;

			divCount = 0;
			resultStr += '-';
		}

		resultStr += ('a' <= ch && ch <= 'z') ? (ch - 32) : ch;
		++divCount;
	}

	return resultStr;
}

string FormatLicense_2(string str, int keyLen)
{
	string resultStr = "";

	int divCount = 0;
	for (int idx = str.length() - 1; idx >= 0; --idx)
	{
		if (str[idx] == '-') continue;

		if (divCount >= keyLen)
		{
			divCount = 0;
			resultStr += '-';
		}

		resultStr += ('a' <= str[idx] && str[idx] <= 'z') ? (str[idx] - 32) : str[idx];
		++divCount;
	}

	reverse(resultStr.begin(), resultStr.end());
	return resultStr;
}

int main(int argc, char** argv)
{
	string str = "2-5g-3-J";
	int keyLen = 2;
	cout << "The give string: " << str
		<< "\nThe key length: " << keyLen;

	cout << "\n\n[Solution 1] The license after format: " << FormatLicense_1(str, keyLen);

	cout << "\n\n[Solution 2] The license after format: " << FormatLicense_2(str, keyLen);

	cout << endl << endl;
	return 0;
}
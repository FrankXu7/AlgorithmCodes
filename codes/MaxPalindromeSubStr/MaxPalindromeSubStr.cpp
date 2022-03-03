/**************************************************************************************************
 * 【题目描述】
 * 给定一个字符串 str，找到 str 中最长的回文子串。如果不存在长度超过1的回文子串，则认为每一个字符都是一个
 * 回文子串，返回首字符作为结果即可，同理，有多个回文子串时，返回任意一个都是正确答案。设定字符串仅由数字
 * 和大小写英文字母组成。
 * 
 * 【输入】
 * str = "xbaabyhhy"
 * 【输出】
 * 最长回文子串："baab"
 * "yhhy" 也被视为正确答案。
 * 
 * 【解题思路】
 * 方法一：
 * 暴力解法，枚举所有的子串，存储之，然后逐一判断是否为回文串，找出其中最长的回文串。判断回文串可从字符串
 * 的首尾开始往中间遍历，遇到左右下标指向的字符不相等时，即代表不是回文字符串。为了稍稍减少一点空间复杂度，
 * 不存储单个字符的子串，若最后没有找到长度超过1的回文子串，则按题意取首字符作为最长回文子串。
 * 
 * 方法二：
 * 动态规划，对于一个下标区间为 [startIdx, endIdx] 的子串，当 str[startIdx] == str[endIdx]，即子串的首
 * 尾字符相等时，此时若知道更小的子串，如区间 [startIdx + 1, endIdx - 1] 是否为回文串，更大规模的问题由
 * 更小规模的问题解决，可考虑动态规划算法，接下来需要建立状态转移方程。
 * 
 * 可建立一个和字符串等长的二维bool类型数组，假设为 dp[strLen][strLen]，其中 dp[i][j] 表示字符串下标区
 * 间 [i, j] 的子串是否为回文子串，故可得状态转移方程：
 * dp[i - 1][j + 1] = dp[i][j] && str[i - 1] == str[j + 1];
 * 每次确定一组回文子串的下标区间时，都要和已记录的最长回文子串下标区间进行比较，判断是否需要更新记录。需
 * 要特别注意的是，最短的回文子串（即最小的问题规模）有两种情况，单个字符和双字符，可先判断这两种子串的回
 * 文标志作为转移基础。
 * 
 * 方法三：
 * 中心拓展算法，因为回文字符串是左右对称的，所以可以从字符串的中间位置同时往两侧遍历，若在触及边界前发现
 * 对应位置的字符不相等，即可判断为非回文字符串。同理，回文字符串按照奇数个和偶数个字符，分为两种情况，中
 * 心为单个字符和中心为两个相等字符。故大致流程为：
 * （1）以当前字符为中心，向两侧遍历，直到遇到对应下标的字符不相等，即找到了一个回文子串的下标区间；
 * （2）以当前字符加上下一个字符为中心（前提是俩字符相等），向两侧遍历，直到遇到对应下标的字符不相等，即
 *      找到了一个回文子串的下标区间；
 * （3）在每次找到一个回文子串的下标区间时，都要和已记录的最长回文子串下标区间进行比较，判断是否需要更新
 *      记录。
 * 
 * 方法四：
 * Manacher算法（俗称“马拉车”算法）
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N^3) 实际为O([N+(N-1)+(N-2)+...] + N*[N+(N-1)+(N-2)+...])
 * 空间复杂度：O(N^2) 实际为O([N+(N-1)+(N-2)+...])
 * 方法二：
 * 时间复杂度：O(N^2) 实际为O(N + N^2)需要初始化dp数组，并设置最小问题规模的解
 * 空间复杂度：O(N^2) 实际上有一部分空间被浪费了，即子串的起始坐标大于结束坐标，如 dp[3][2] 的值无意义
 * 方法三：
 * 时间复杂度：O(N^2) 最差情况会到 O( N^2 + N*(N-1) )，即所有字符均相等，每次扩散都会到达 str 的边界
 * 空间复杂度：O(1)
 * 方法四：
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2022-01-04
 *************************************************************************************************/
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

string MaxPalindromeSubStr_1(string& str)
{
	auto strLen = str.length();
	unordered_set<string> gather;
	string tempStr = "";

	// 列举出所有长度超过1的子字符串 
	for (unsigned int startIdx = 0; startIdx < strLen; ++startIdx)
	{
		tempStr = str[startIdx];
		for (unsigned int chIdx = startIdx + 1; chIdx < strLen; ++chIdx)
		{
			tempStr += str[chIdx];
			gather.emplace(tempStr);
		}
	}

	// 若不存在长度超过1的回文子串，则字符串任意一个字符都算作回文子串，默认值为首字符 
	string ansStr(1, str[0]);
	unsigned int leftIdx = 0, rightIdx = 0;

	for (decltype(gather)::iterator itr = gather.begin(); itr != gather.end(); ++itr)
	{
		leftIdx = 0, rightIdx = (*itr).length() - 1;

		while (leftIdx < rightIdx)
		{
			if ((*itr)[leftIdx] != (*itr)[rightIdx])
			{
				break;
			}

			++leftIdx;
			--rightIdx;
		}

		if (leftIdx >= rightIdx && (*itr).length() > ansStr.length())
		{
			ansStr = (*itr);
		}
	}

	return ansStr;
}

string MaxPalindromeSubStr_2(string& str)
{
	auto strLen = str.length();

	vector<vector<bool>> dp(strLen, vector<bool>(strLen, false));
	// 标记单个字符和两个相同字符为回文子串，dp[i][j] 表示从下标区间 [i,j] 的子串是否为回文串 
	for (unsigned int idx = 0; idx < strLen; ++idx)
	{
		dp[idx][idx] = true;
		if (idx + 1 < strLen && str[idx] == str[idx + 1]) dp[idx][idx + 1] = true;
	}

	unsigned int startSubIdx = 0, maxSubLen = 0, startIdx = 0, subLen = 0, endIdx = 0;
	for (subLen = 2; subLen <= strLen; ++subLen)
	{
		for (startIdx = 0; startIdx < strLen; ++startIdx)
		{
			endIdx = startIdx + subLen - 1;
			if (endIdx >= strLen) break;

			// 截取的子串，首尾字符不相等，必然不是回文串 
			if (str[startIdx] != str[endIdx])
			{
				dp[startIdx][endIdx] = false;
			}
			else // 状态转移到更小的子串，且更小子串已处理，直接获取是否为回文串的结果 
			{
				/**
				 * startIdx 和 endIdx 指向字符相等，且这两个下标的差值小于3，必然为一个合法的回文子串，
				 * 因为长度等于2的子串在一开始就标记过了，故可以直接确定是否为回文子串
				 */
				if (endIdx - startIdx < 3) dp[startIdx][endIdx] = true;
				else dp[startIdx][endIdx] = dp[startIdx + 1][endIdx - 1];
			}

			if (dp[startIdx][endIdx] && subLen > maxSubLen)
			{
				startSubIdx = startIdx;
				maxSubLen = subLen;
			}
		}
	}

	return str.substr(startSubIdx, maxSubLen);
}

string MaxPalindromeSubStr_3(string& str)
{
	int strLen = str.length(), startSubIdx = 0, endSubIdx = 0, leftIdx = 0, rightIdx = 0;

	auto spreadSide = [&] {
		while (leftIdx >= 0 && rightIdx < strLen && str[leftIdx] == str[rightIdx])
		{
			--leftIdx;
			++rightIdx;
		}

		++leftIdx;
		--rightIdx;
		if (rightIdx - leftIdx > endSubIdx - startSubIdx)
		{
			startSubIdx = leftIdx;
			endSubIdx = rightIdx;
		}
	};
	
	for (int idx = 0; idx < strLen; ++idx)
	{
		// 单字符为中心进行扩散 
		leftIdx = rightIdx = idx;
		spreadSide();

		// 空字符为中心进行扩散，等价于以相等的双字符为中心进行扩散 
		if (idx + 1 < strLen && str[idx] == str[idx + 1])
		{
			leftIdx = idx; 
			rightIdx = idx + 1;

			spreadSide();
		}
	}

	return str.substr(startSubIdx, endSubIdx - startSubIdx + 1);
}

string MaxPalindromeSubStr_4(string& str)
{
	string formatStr = "$#";
	for (char ch : str)
		formatStr += {ch, '#'};

	string ansStr(1, str[0]);

	vector<int> radius(formatStr.length(), 0);

	return ansStr;
}

int main(int argc, char* argv[])
{
	string str = "cbcbccde";
	cout << "The given string: " << str;

	cout << "\n\n[Solution 1] The longest palindrome substring: " << MaxPalindromeSubStr_1(str);

	cout << "\n\n[Solution 2] The longest palindrome substring: " << MaxPalindromeSubStr_2(str);

	cout << "\n\n[Solution 3] The longest palindrome substring: " << MaxPalindromeSubStr_3(str);

	cout << "\n\n[Solution 4] The longest palindrome substring: " << MaxPalindromeSubStr_4(str);
	
	cout << endl << endl;
	return 0;
}
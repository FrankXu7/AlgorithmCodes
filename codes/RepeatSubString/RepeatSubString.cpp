/**************************************************************************************************
 * 【题目描述】
 * 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。
 *
 * 【输入】
 * "abab"
 * 【输出】
 * TRUE 字符串由子字符串 "ab" 重复两次构成
 *
 * 【解题思路】
 * 方法一
 * 暴力枚举，如果一个字符串 str 是由 n 个 subStr 构成，可得出如下结论：
 * （1）str 的长度必然为 subStr 长度的整数倍，并且该整数就是 n；
 * （2）相邻 subStr 长度下标的字符必然会相等，即 str[idx] == str[idx - subStr.length()] 恒成立；
 * （3）既然 str 由 subStr 重复 n 次构成，故 subStr 长度不能超过 str 的一半；
 *
 * 综上所述，可来一次 [1, str.length() / 2] 区间的外层遍历，若 subStr 存在则必然可在该区间内找到，对于每
 * 一轮遍历的下标 subIdx，其含义就是 subStr 的假设长度，故 str.length() 必须能够整除当前下标 subIdx，在
 * 此基础之上，从 subIdx 下标开始内层循环到 str.length() 时会恒满足等式：str[idx] == str[idx - subIdx]
 * 否则当前外层遍历的 subIdx 所代表的 subStr 子字符串的长度必然不符合题意。
 *
 * 方法二
 * 窗口思想，将字符串 str 采取如下操作：将首个字符放置到字符串末尾构成了新字符串，再将新字符串首个字符放
 * 置到字符串末尾。重复此操作，过程中必然会得到一个新字符串会等于 str，注意这里的 str 不一定要是满足题意
 * 的那种字符串。
 *
 * 所以，通过拼接两个字符串构成 (str+str)，掐头去尾，除去首尾字符，如果 str 是满足题意的字符串，则必然是
 * (str+str) 的子字符串，之前的掐头去尾就是为了保证任意字符串进行窗口滑动后必然会回到最初字符串的情况。
 * 
 * 方法三
 * KMP算法，在方法二中，如果匹配到不相等的字符，需要同时将匹配串和模式串的下标都回溯到本轮匹配之前，但模式
 * 串中已有部分匹配相等的字符，在后续的匹配中，这些已经匹配过且知道匹配结果的部分字符，又会重新参与匹配比
 * 较，增加了时间复杂度，而KMP算法就是利用了模式串中这部分已经匹配的信息，将其保存在 nextArr 中，通过增加
 * 一定的空间复杂度，使得字符串匹配的算法能够达到线性时间复杂度。
 * 
 * KMP的核心算子就是就是构建 nextArr 数组，该数组的元素下标和模式串中的下标一一对应，元素的值表示在模式串
 * 该下标之前的元素中，最长相同前后缀的长度。字符串的前缀即包含首个字符但不包含最后一个字符的真子串，后缀
 * 同理，包含最后一个字符但不包含首个字符的真子串。
 * 
 * 在得到了 nextArr 数组之后，即可开始字符串匹配过程，当匹配遇到不相等的字符时，找到上一个匹配相等的字符的
 * 下标，该下标对应的 nextArr 元素值，即为模式串中该下标所在的字符之前，最长相同前后缀长度，该长度值就是模
 * 式串回溯到的下标，而匹配串则可以不用回溯，直接从下一个字符开始和回溯后的模式串继续匹配。
 * 
 * 之所以模式串下标可以不需要回退至0，是因为匹配到不相等的字符时，它前面的字符肯定都是匹配相等的，而找到上
 * 一个匹配字符所记录在 nextArr 中的最长相同前后缀长度，就表明在当前匹配不相等的字符前，那一串匹配相等的字
 * 符中，可以将前缀部分直接移动到后缀部分所在匹配位置，因为都是相等的，所以不需要比较，这样继续匹配时，这
 * 部分长度的字符就不需要再比较计算了，从而降低时间复杂度。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N^2)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N) 实际最大为O(2N-2)，遍历的字符串是 (str+str) 拼接后掐头去尾构成的
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(N) 实际为O(M+N)，构造nextArr数组需要遍历模式串，字符串匹配需要遍历匹配串
 * 空间复杂度：O(N) 模式串记录最长相同前后缀的长度
 *
 * @author FrankX
 * @date 2021-12-01
 *************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool RepeatSubString_1(string str)
{
	unsigned int len = str.length();
	if (len < 2) return false;

	unsigned int halfLen = static_cast<unsigned int>(len / 2);

	bool roundMatch = false;

	// 子字符串至少要1个字符，故从1开始遍历，且重复子字符串至少要重复1次，故子字符串最长为总长的一半 
	for (unsigned int subLen = 1; subLen <= halfLen; ++subLen)
	{
		// 若存在子字符串，则总长必为重复子字符串的整数倍 
		if (len % subLen != 0) continue;

		roundMatch = true;
		for (unsigned int idx = subLen; idx < len; ++idx)
		{
			// 因为 idx >= subIdx，且for循环保证不越界，所以不需要判断下标 idx-subIdx 的合法性 
			if (str[idx] != str[idx - subLen])
			{
				roundMatch = false;
				break;
			}
		}

		if (roundMatch)
			return true;
	}

	return false;
}

bool RepeatSubString_2(string str)
{
	unsigned int strLen = str.length(), strIdx = 0, tempStrIdx = 0;
	if (strLen < 2) return false;

	string tempStr = str.substr(1, strLen - 1) + str.substr(0, strLen - 1);
	unsigned int tempStrLen = tempStr.length();

	while (tempStrIdx < tempStrLen && strIdx < strLen)
	{
		if (tempStr[tempStrIdx] == str[strIdx])
		{
			++tempStrIdx;
			++strIdx;
		}
		else
		{
			/**
			 * 因为判断的是str是否为tempStr的字串，且tempStr由(str+str)掐头去尾后构成，所以这里其实也可
			 * 以不处理tempStrIdx，使其在不匹配的下标基础上继续下一次的匹配。
			 * 
			 * 一般如果判断某个字符串compareStr是否为targetStr的子字符串，则必须在判断不匹配时回溯二者的
			 * 下标，compareStr下标直接置零，targetStr下标按下述代码表达式处理。这么做是为了避免如下情况：
			 * targetStr = "123aaabcd123"
			 * compareStr = "aabcd"
			 * 当匹配到comareStr中的 "aab" 时，发现不匹配，如果不回溯targetStr的下标，那么下次匹配会从该
			 * 字符串中的字符 'b' 的下标开始匹配，从而导致匹配错误。
			 */
			tempStrIdx = tempStrIdx - strIdx + 1;
			strIdx = 0;
		}
	}

	return (strIdx == strLen);
	/**
	 * 该算法等价于：
	 * return (str + str).find(str, 1) != str.length()
	 */
}

bool RepeatSubString_3(string str)
{
	int strLen = static_cast<int>(str.length());
	if (strLen < 2) return false;

	string searchStr = str.substr(1, strLen - 1) + str.substr(0, strLen - 1);
	vector<int> nextArr(strLen, 0);

	// 构造next数组 
	int k = 0;
	for (int idx = 1; idx < strLen; ++idx)
	{
		while (k > 0 && str[k] != str[idx])
		{
			/**
			 * 匹配到不相等的字符时，找到上一个匹配相等字符所在下标记录的模式串在该下标之前的最长相同前后
			 * 缀长度，赋值到 k，等价于将模式串回溯到前后缀真子串中的前缀部分，这样就避免了重复匹配比较前
			 * 后缀中相等的部分
			 */
			k = nextArr[k - 1];
		}

		if (str[k] == str[idx])
		{
			/**
			 * 此时k就是上一个匹配相等字符所在下标记录的模式串在该下标之前的最长相同前后缀长度，此时匹配
			 * 相等，那模式串当前位置之前的最长相同前后缀长度就是在 k 的基础上加1
			 */
			nextArr[idx] = ++k;
		}
	}

	// 字符串匹配 
	int serachIdx = 0;
	for (char ch : searchStr)
	{
		if (ch != str[serachIdx])
		{
			// 三目运算符主要是针对首个字符下标的特殊处理，使得下标不会越界 
			serachIdx = (serachIdx > 0) ? nextArr[serachIdx - 1] : 1;
		}
		else if (++serachIdx >= strLen)
		{
			// 模式串搜索下标越界，匹配完整个模式串，那模式串自然是匹配串的子串了 
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	string str = "ABABDA"; // 001201
	cout << "The given string: " << str;

	cout << "\n\n[Solution 1] Exist repeat substring ? " << (RepeatSubString_1(str) ? "YES" : "NO");

	cout << "\n\n[Solution 2] Exist repeat substring ? " << (RepeatSubString_2(str) ? "YES" : "NO");

	cout << "\n\n[Solution 3] Exist repeat substring ? " << (RepeatSubString_3(str) ? "YES" : "NO");

	cout << endl << endl;
	return 0;
}
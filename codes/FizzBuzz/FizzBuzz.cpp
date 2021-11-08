/**************************************************************************************************
 * 【题目描述】
 * 输出一个Bizz Fuzz序列，给定一个整数 num，找到 [1, num] 中各个整数的Fizz Buzz表示，并将其通过一个下标
 * 从1开始的字符串数组返回。
 * 
 * Fizz Buzz序列有以下特性：
 * （1）如果下标能整除3，则对应字符串为：Fizz；
 * （2）如果下标能整除5，则对应字符串为：Buzz；
 * （3）如果下标能同时整除3和5，则对应字符串为：FizzBuzz；
 * （4）若不满足上述所有条件，则对应字符串即为当前下标值（下标从1开始）；
 * 
 * 【输入】
 * num=15
 * 【输出】
 * FizzBuzz序列：[1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14, FizzBuzz]
 *
 * 【解题思路】
 * 依题意下标从1开始，故先初始化一个长度为 num+1 的字符串容器，使用vector容器，从下标1开始遍历，首先判断
 * 是否能整除3，其次再判断是否能整除5，若其中一项整除成立，则将字符串Fizz或Buzz追加到元素值，最后判断元素
 * 字符串是否为空字符串，即当前下标不能整除3或5，则将下标值作为元素值，追加到字符串中。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-11-08
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> FizzBuzz(unsigned int num)
{
	vector<string> resultStr(num + 1);

	for (unsigned int idx = 1; idx <= num; ++idx)
	{
		if (idx % 3 == 0)
			resultStr[idx] += "Fizz";
		if (idx % 5 == 0)
			resultStr[idx] += "Buzz";

		if (resultStr[idx].empty())
			resultStr[idx] += to_string(idx);
	}

	return resultStr;
}

int main(int argc, char* argv[])
{
	unsigned int inputNum = 15;
	cout << "The given number: " << inputNum;

	cout << "\n\nBizz Fuzz array:\n";
	auto fizzBuzzArr = FizzBuzz(inputNum);
	for (auto& str : fizzBuzzArr)
		if (!str.empty())
			cout << str << ", ";

	cout << endl << endl;
	return 0;
}
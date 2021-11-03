/**************************************************************************************************
 * 【题目描述】
 * 给定一个有符号的整数，将其转换为十六进制数输出，要求：
 * （1）十六进制中的字母必须是小写字母；
 * （2）最终的十六进制数不会有多余的前导0，如果整数本身是0，那最终结果即为0，不算多余的；
 * （3）给定有符号二进制整数是32位；
 * （4）因为负整数是用补码形式存储的，直接将负整数转换为十六进制输出即可；
 * （5）算法不能使用框架或库提供的接口；
 *
 * 【输入】
 * Input number = 100
 * 【输出】
 * 对应的十六进制输出：64
 *
 * 【解题思路】
 * 方法一：
 * 32位的有符号整数，转换为十六进制，因为每4位二进制数可以表示1位十六进制数，所以可以先构建一个无序map来
 * 保存16种情况，用一个数字1通过从低位到高位左移，然后和给定整数做按位&运算，来判断给定整数二进制的某一位
 * 是0还是1，每4位就能组合一个key，通过该key找到map中对应的十六进制字符，因为题意要求不能有前置0，所以只
 * 有字符串有内容，并且当前的十六进制数不是0，才将结果追加到字符串。
 * 
 * 方法二：
 * 对于方法一，既然每4位二进制数必定可以表示1位十六进制数，那何不直接位移4位，然后和0xf进行按位&运算，这
 * 样只需将32位整数分成8组即可，对于每一组来说，和0xf按位&运算的结果即为该位置的十六进制数，如果这个数小
 * 于10，则可直接将其转换为字符追加到字符串末尾（为了保证是追加操作，从高位分组开始遍历），如果这个数字大
 * 于0，通过字符计算转换为十六进制字符即可。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(1) 遍历上界固定为31，最高位作为符号位不参与计算 
 * 空间复杂度：O(1) 需要一个无序map保存4位二进制映射到1位十六进制的情况，是有限且可知的 
 * 方法二：
 * 时间复杂度：O(1) 遍历上界固定为8，32位二进制分成8组 
 * 空间复杂度：O(1) 
 * 
 * @author FrankX
 * @date 2021-11-03
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset> // 算法逻辑不需要，仅用于打印二进制 
using namespace std;

string ConvertToHexadecimal_1(int num)
{
	// 因题意要求最终结果不能有前置0，当目标数字本身是0时直接返回，避免后续作特殊处理 
	if (num == 0) return "0";

	static unordered_map<string, char> numMap{
		{"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
		{"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
		{"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'},
		{"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'},
	};

	string result = ""; 
	// int类型最高位是符号位，不应参与运算，将其初始化到首个key 
	string key = (num > 0) ? "0" : "1";

	// 首位二进制作为符号位，不参与计算 
	for (int idx = 30; idx >= 0; --idx)
	{
		key += ((1 << idx) & num) > 0 ? "1" : "0";
		if (numMap.find(key) != numMap.end())
		{
			// 这个判断主要是因为题意要求最终结果不能有前置0 
			if (result.length() > 0 || key != "0000")
				result += numMap[key];
			key = "";
		}
	}

	return result;
}

string ConvertToHexadecimal_2(int num)
{
	// 因题意要求最终结果不能有前置0，当目标数字本身是0时直接返回，避免后续作特殊处理 
	if (num == 0) return "0";

	string result = "";
	int calcNum = 0;

	for (int groupIdx = 7; groupIdx >= 0; --groupIdx)
	{
		calcNum = (num >> (4 * groupIdx)) & 0xf;

		// 这个判断主要是因为题意要求最终结果不能有前置0 
		if (result.length() > 0 || calcNum > 0)
			result += static_cast<char>(calcNum < 10 ? ('0' + calcNum) : ('a' + calcNum - 10));
	}

	return result;
}


int main(int argc, char** argv)
{
	int inputNum = 100;
	cout << "Input number is: " << inputNum;
	cout << "\nThe hexadecimal calc by library interface is: " << hex << inputNum;
	cout << "\nThe binary with 32 bits: " << bitset<32>(inputNum);

	cout << "\n\n[Solution 1] The hexadecimal is: " << ConvertToHexadecimal_1(inputNum);

	cout << "\n\n[Solution 2] The hexadecimal is: " << ConvertToHexadecimal_2(inputNum);

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 将给定的整数转换为罗马数字并输出，整数取值范围限定区间为：[1, 3999]
 * 
 * 罗马数字只包含下列字符：
 * {
 *		I=1,
 *		V=5,	X=10,
 *		L=50,	C=100,
 *		D=500,	M=1000,
 * }
 *
 * 通常情况下，罗马数字中小的数字在大的数字右边，但存在以下6中情况例外：
 * {
 *		IV=4,	IX=9,
 *		XL=40,	XC=90,
 *		CD=400,	CM=900,
 * }
 * 
 * 补充：按题中所给出的字符，罗马数字其实最大可以表示到4999，即 MMMMCMXCIX，而从5000开始，字母的书写会在
 * 【字母上方加一横线】，输入法打不出来，加在右上方表示：
 * 5000    V￣
 * 10000   X￣
 * 50000   L￣
 * 100000  C￣
 * 500000  D￣
 * 1000000 M￣
 * 
 * 【输入】
 * Integer number = 2022;
 * 【输出】
 * Roman number = "MXXII";
 *
 * 【解题思路】
 * 方法一：
 * 按照题中对罗马字符的解释，可以枚举出所有数字对应的罗马字符，以键值对 {整数，罗马数字字符串} 构造 map，
 * 假设命名为 numMap，同时为了方便计算，构造一个数组按从大到小的顺序存储 numMap 中的所有键。因为容量大小
 * 都是固定的，可以直接硬编码写出。
 * 
 * 接下来，假设给定的整数为 givenNum，利用贪心算法的原理，找到 nums 中满足 givenNum - nums[numIdx] > 0
 * 的最大 numIdx，即罗马数字从左往右应该尽可能的选择更大的符号。如果不满足以上的式子，则 numIdx 自加，找
 * 到下一个满足该式子的下标。
 * 
 * 方法二：
 * 按照方法一中的分析，同样利用贪心算法的原理，但是需要转变一下思路，用更简单的方式实现算法，因为数组nums
 * 是按照从大到小顺序排列的，所以可直接遍历 nums，然后在内层循环中处理每个 nums[numIdx] 值，直到不满足式
 * 子 givenNum - nums[numIdx] > 0，然后下标自加，找到下一个满足该式子的下标。
 * 
 * 方法三：
 * 因为整数的取值区间已经固定为 [1, 3999]，所以也可以直接用枚举的方式，硬编码列出 个十百千 位上的所有情况，
 * 除了千位数只有三种可能性之外，其它位数都有十种可能性。当然，每个位数都有一个空字符串，用以表示 giveNum
 * 不足该位数的情况。比如888不足1000，那千位的罗马字符串即为一个空串。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(1) 因为整数的取值区间为 [1, 3999]，当减去最大罗马字符（M=1000）时，最大3次即可减到百分
 *                 位，个十百分位原理类似，即遍历的次数上限值是已知的，故复杂度可视作常数
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1) 同方法一时间复杂度的原理类同，可视作常数
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-01-20
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<int, string> numMap = {
	{1000, "M"}, {900, "CM"},
	{500, "D"}, {400, "CD"},
	{100, "C"}, {90, "XC"},
	{50, "L"}, {40, "XL"},
	{10, "X"}, {9, "IX"},
	{5, "V"}, {4, "IV"},
	{1, "I"}
};
vector<int> nums = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };

string IntegerToRoman_1(int givenNum)
{
	if (givenNum <= 0 || givenNum >= 4000) return "";

	string roman = "";
	unsigned int numIdx = 0;

	while (givenNum > 0)
	{
		/**
		 * 因循环体内 num 必大于零，能执行到此的 num 最小值是 1，包含在数组 nums 中，故 numIdx 必不会越
		 * 界，所以不用进行下标越界判断
		 */
		while (givenNum - nums[numIdx] < 0) ++numIdx;

		givenNum -= nums[numIdx];
		roman += numMap[nums[numIdx]];
	}

	return roman;
}

string IntegerToRoman_2(int givenNum)
{
	if (givenNum <= 0 || givenNum >= 4000) return "";

	string roman = "";

	for (int& num : nums)
	{
		while (givenNum >= num)
		{
			givenNum -= num;
			roman += numMap[num];
		}

		if (givenNum == 0) break;
	}

	return roman;
}

string IntegerToRoman_3(int givenNum)
{
	if (givenNum <= 0 || givenNum >= 4000) return "";

	// 1000 ~ 4000 的千位数 
	vector<string> thousands = { "", "M", "MM", "MMM", "MMMM" };
	// 100 ~ 900 的百位数 
	vector<string> hundreds = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	// 10 ~ 90 的十位数 
	vector<string> tens = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	// 1 ~ 9 的个位数 
	vector<string> ones = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

	return (thousands[givenNum / 1000] + hundreds[givenNum % 1000 / 100] +
		tens[givenNum % 100 / 10] + ones[givenNum % 10]);
}

int main(int argc, char** argv)
{
	int givenNum = 2022;
	cout << "The given number: " << givenNum;

	string roman1 = IntegerToRoman_1(givenNum);
	if (!roman1.empty()) cout << "\n\n[Solution 1] Convert to roman number: " << roman1;
	else cout << "\n\n[Solution 1] The given is out of range: [1, 3999]";

	string roman2 = IntegerToRoman_2(givenNum);
	if (!roman2.empty()) cout << "\n\n[Solution 2] Convert to roman number: " << roman2;
	else cout << "\n\n[Solution 2] The given is out of range: [1, 3999]";

	string roman3 = IntegerToRoman_3(givenNum);
	if (!roman3.empty()) cout << "\n\n[Solution 3] Convert to roman number: " << roman3;
	else cout << "\n\n[Solution 3] The given is out of range: [1, 3999]";

	cout << endl << endl;
	return 0;
}
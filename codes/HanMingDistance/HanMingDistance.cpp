/**************************************************************************************************
 * 【题目描述】
 * 汉明距离：给定两个整数 num1 和 num2 求它们对应位置上的二进制数不同的个数。
 * 
 * 【输入】
 * num1 = 666
 * num2 = 888
 * 【输出】
 * 666的二进制：0000'0000'0000'0000'0000'001[0]'[100]1'10[1]0
 * 888的二进制：0000'0000'0000'0000'0000'001[1]'[011]1'10[0]0
 * 统计有5个对应位置的二进制数不同
 * 
 * 【解题思路】
 * 方法一：
 * 窗口思想，将数字 1 逐位左移，并分别与 num1 和 num2 按位‘与’运算，如果计算结果不相等，那么就表明当前的
 * 二进制位是不同的，统计之。
 * 
 * 方法二：
 * 也可以换个思路，因为题意求对应位置上的二进制数的不同，可以先将 num1 和 num2 进行‘异或’运算，不相等的二
 * 进制位异或结果为1，然后统计异或结果中的数字1即可。
 * 
 * 将异或结果（假设为 xorSum）和数字1按位‘与’运算，计算结果就是 xorSum 的最后一位，将其加入到统计结果。
 * 
 * 方法三：
 * 将两个数字异或计算后的结果（假设为 xorSum），统计数字1的数量即为最终结果，而方法二中也处理了数字0，可以
 * 采用 Brian Kernighan 算法，其核心算子 N & (N-1)，消除二进制末尾的1，将每次计算的结果赋值回 xorSum，每
 * 次处理都将统计加1，直到 xorSum 结果为0.
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(1) 依据数据类型的实际长度，这里是O(32)，是一个确定值，故复杂度为常数
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1) 依据数据类型的实际长度，这里是O(32)，是一个确定值，故复杂度为常数
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(1) 依据数据类型的实际长度，这里是O(32)，是一个确定值，故复杂度为常数
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-12-09
 *************************************************************************************************/
#include <iostream>
#include <bitset> // 算法逻辑不需要，仅用于打印显示 
using namespace std;

int HanMingDistance_1(int num1, int num2)
{
	int diffCount = 0;
	// 作为移动窗口的数字 
	int lMove = 1;
	for (int idx = 0; idx < 31; ++idx)
	{
		lMove <<= 1;
		// 大致优先级：四则运算 > 比较运算 > 位运算 
		if ((lMove & num1) != (lMove & num2))
			++diffCount;
	}

	return diffCount;
}

int HanMingDistance_2(int num1, int num2)
{
	int diffCount = 0;

	int xorSum = num1 ^ num2;
	while (xorSum) 
	{
		diffCount += xorSum & 1;
		xorSum >>= 1;
	}

	return diffCount;
}

int HanMingDistance_3(int num1, int num2)
{
	int diffCount = 0;

	int xorSum = num1 ^ num2;
	while (xorSum)
	{
		xorSum &= (xorSum - 1);
		++diffCount;
	}

	return diffCount;
}

int main(int argc, char* argv[])
{
	int num1 = 666, num2 = 888;
	cout << "Number 1: " << bitset<32>(num1)
		<< "\nNumber 2: " << bitset<32>(num2);

	cout << "\n\n[Solution 1] The HanMing Distance is: " << HanMingDistance_1(num1, num2);
	cout << "\n\n[Solution 2] The HanMing Distance is: " << HanMingDistance_2(num1, num2);
	cout << "\n\n[Solution 3] The HanMing Distance is: " << HanMingDistance_3(num1, num2);

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 以二进制形式输入一个32位无符号整数，统计这32位中1的个数。
 *
 * 【输入】
 * Binary number: 0000 1111 0000 1111 0000 1111 0000 1111
 * 【输出】
 * Counting bits of one: 16
 *
 * 
 * 【解题思路】
 * 方法一：
 * 直接利用将十进制转换为二进制的算法，统计余数为1的个数，即为二进制数中1的个数。
 * 
 * 方法二：
 * 和方法一几乎等价，其实就是将十进制层面的计算，放到二进制层面来算。通过和1进行按位&运算，可得到目标数字
 * 二进制的最低位，统计这个最低位是1的情况，然后将目标数字右移一位，以移除使用过的最低位。
 * 
 * 方法三：
 * 将1和另一个二进制位进行按位&运算，可以得出另一个二进制是0还是1，所以将1从目标数字二进制的最低位开始依，
 * 次左移并和目标数字进行按位&运算，统计目标数字二进制数中1的个数。
 * 
 * 方法四：
 * Brian Kernighan 算法：表达式 N & (N-1) 是将一个整数N的二进制位最后一个0消除。
 * 
 * 依据Brian Kernighan 算法思想，迭代使用核心算子：N &= (N-1) 可逐步消除整数N中二进制位的1，直至N为0：
 * （1）当目标数字二进制最低位刚好是1的时候，按位&运算之后，结果相当于比目标数字减少1；
 * （2）如果目标数字二进制最低位是0，则需要借位相减，原目标数字和减1后的目标数字，有部分二进制位不同，这
 *      部分不同的二进制位按位&运算的结果为0，这样就避免了统计到目标数字在借位减1时额外出现的数字1；统计
 *      到目标数字减到0为止。
 * 
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(1) 本质上是O(logN)，以2为底，题意固定32位，所以时间复杂度最大为5，是常数时间复杂度
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1) 实际上为32，需要依次判断32位二进制的每一位
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(1) 实际上为32，需要依次判断32位二进制的每一位
 * 空间复杂度：O(1)
 * 方法四：
 * 时间复杂度：O(1) 实际上为O(logN)，以2为底，题意固定32位，所以时间复杂度最大为5，是常数时间复杂度
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-08-17
 **************************************************************************************************/
#include <iostream>
#include <bitset> // 用于日志显示二进制，算法逻辑并不需要 
using namespace std;

unsigned int CountBitsOfOne_1(unsigned int num)
{
	unsigned int bitsCount = 0;

	// 此方法和 CountBitsOfOne_2 几乎是等价的 
	while (num > 0)
	{
		if (num % 2 == 1) ++bitsCount;
		num /= 2;
	}

	return bitsCount;
}

unsigned int CountBitsOfOne_2(unsigned int num)
{
	unsigned int bitsCount = 0;

	// 此方法和 CountBitsOfOne_1 几乎是等价的 
	for (unsigned int idx = 0; idx < 32; ++idx)
	{
		if ((num & 1) == 1) ++bitsCount;
		num >>= 1;
	}

	return bitsCount;
}

unsigned int CountBitsOfOne_3(unsigned int num)
{
	unsigned int bitsCount = 0;

	/**
	 * 二进制相关运算符优先级：
	 * 按位非~ 、左移<< 、右移>> 、按位与& 、按位异或^ 、按位或| 、位操作并赋值，如<<=等
	 */
	for (unsigned int idx = 0; idx < 32; ++idx)
	{
		// 用数字1来左移按位&运算，数值本身不会有额外计算 
		if ((1 << idx & num) >= 1) ++bitsCount;
	}

	return bitsCount;
}

unsigned int CountBitsOfOne_4(unsigned int num)
{
	unsigned int bitsCount = 0;

	while (num > 0)
	{
		num &= (num - 1);
		++bitsCount;
	}

	return bitsCount;
}

int main()
{
	unsigned int num = 0b00001111000011110000111100001111;

	cout << "Unsigned 32 bits binary int:\n" << bitset<32>(num) << endl << endl;

	cout << "[Solution 1] Counting bits of one: " << CountBitsOfOne_1(num) << endl;
	cout << "[Solution 2] Counting bits of one: " << CountBitsOfOne_2(num) << endl;
	cout << "[Solution 3] Counting bits of one: " << CountBitsOfOne_3(num) << endl;
	cout << "[Solution 4] Counting bits of one: " << CountBitsOfOne_4(num) << endl;

	cout << endl;
	return 0;
}
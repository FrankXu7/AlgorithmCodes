/**************************************************************************************************
 * 【题目描述】
 * 将一个32位无符号整数的二进制进行翻转，并输出翻转后的32位无符号整数。
 *
 * 【输入】
 * 一个32位无符号整数：43261596
 * 二进制：0000 0010 1001 0100 0001 1110 1001 1100
 * 【输出】
 * 将输入整数的二进制翻转，得到一个新的32位无符号整数：964176192
 * 二进制：0011 1001 0111 1000 0010 1001 0100 0000
 *
 * 【解题思路】
 * 方法一：
 * 如果能将目标数字的二进制从最低位开始，一个个的取得，并追加到翻转结果中去，就可以实现算法。
 * 将一个数字和1进行按位&运算，就可以得到这个数字二进制最低位的值。
 * 通过二进制转十进制的乘法计算，也容易看出，左移/右移1位，相当于将十进制数字乘以/除以2，
 * 可得大致步骤：
 * （1）循环上限依题意固定为32；
 * （2）将翻转结果左移1位，以追加目标数字二进制的最低位；
 * （3）目标数字和1按位&运算，得到目标数字二进制的最低位，加到翻转结果中；
 * （4）目标数字右移1位，舍弃已经使用过的二进制最低位；
 * （5）重复步骤（2）（3）（4）直到完成循环上限。
 * 
 * 方法二：
 * 可采用分治法，比如题中是32位，以两位为一组分为16组，交换各组，然后再以4位为一组，交换各组；
 * 通过自底向上的方式，依次分而治之，以（ABCDEFGH）展示过程：
 * BA DC FE HG
 * DCBA HGFE
 * HGFEDCBA
 * 
 * 虽然有了思路，但二进制的运算不同于十进制，二进制不是字符串，不能对其进行遍历，所以需要用一种
 * 位运算来达到分治法中的拆分效果。按位或运算，可以达到这种效果，按位或运算可以看成是一种
 * 没有进位的加法运算，通过合适的拆分数字与目标数字进行按位或运算，然后移位，再进行或运算，即可将
 * 分治法中的分组进行交换，大致过程：
 * （1）以两位为一组分成16组，拆分数字为：
 *		0101 0101 0101 0101 0101 0101 0101 0101 (0x55555555)，
 *		先将目标数字右移1位，然后与拆分数字进行或运算，此时相当于把分组内第一个位置的值或运算到了第二位；
 *		再将目标数字直接与拆分数字进行计算，然后左移1位，此时相当于把分组内第二个位置的值或运算到了第一位。
 * （2）按照第（1）步所述，自底向上，以4位为一组分成8组，此时的拆分数字为：
 *		0011 0011 0011 0011 0011 0011 0011 0011 (0x33333333)；
 * （3）继续拆分，以8位为一组分成4组，此时的拆分数字为：
 *		0000 1111 0000 1111 0000 1111 0000 1111（0x0f0f0f0f）
 * （4）最后一次拆分，以16位为一组分成两组，此时的拆分数字为：
 *		0000 0000 ffff ffff 0000 0000 ffff ffff（0x00ff00ff）；
 * 
 * 举例便于快速理解（目标数字为 ABCDEFGH）：
 * （1）拆分数字：01010101
 *		目标数字右移1位：0ABCDEFG，与拆分数字或运算：0A0C0E0G；
 *		目标数字直接与拆分数字或运算：0B0D0F0H，再左移1位：BODOFOHO；
 *		两次计算的结果或运算：BADCFEHG，此结果作为新的目标数字；
 * （2）拆分数字：00110011
 *		目标数字右移2位：00BADCFE，与拆分数字或运算：00BA00FE；
 *		目标数字直接与拆分数字或运算：00DC00HG，再左移2位：DC00HG00；
 *		两次计算的结果或运算：DCBAHGFE，此结果作为新的目标数字；
 * （3）拆分数字：00001111
 *		目标数字右移4位：0000DCBA，与拆分数字或运算：0000DCBA；
 *		目标数字直接与拆分数字或运算：0000HGFE，再左移4位：HGFE0000；
 *		两次计算的结果或运算：HGFEDCBA，此即为最终翻转结果。
 * 
 * 需要注意的是，必须先右移再左移，因为拆分数字都是0在前1在后，若先左移，则按位或运算后，最低位必为1导致结果错误。
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(1) 因为题目指定处理32位的二进制，所以遍历次数是32，为常数时间复杂度
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1) 因为题目指定处理32位的二进制，所以分治法自底向上只需分治4次即可
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-08-16
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

unsigned int ReverseIntBinary_1(unsigned int num)
{
	unsigned int resNum = 0;
	unsigned int bits = 32;

	while ((bits--) > 0)
	{
		// 翻转结果左移1位，相当于二进制最低位增加一位 
		resNum <<= 1;
		// 与1按位&运算，得到目标数字的二进制最低位值 
		resNum += (num & 1);
		// 目标数字的二进制最低位已经使用过了，右移舍弃 
		num >>= 1;
	}

	return resNum;
}

// 两位一组分16组的拆分数字：0101 0101 0101 0101 0101 0101 0101 0101
#define DIV_1 0x55555555
// 4位为组分8组的拆分数字：  0011 0011 0011 0011 0011 0011 0011 0011
#define DIV_2 0x33333333
// 8位一组分4组的拆分数字：  0000 1111 0000 1111 0000 1111 0000 1111
#define DIV_3 0x0f0f0f0f
// 16位一组分两组的拆分数字：0000 0000 1111 1111 0000 0000 1111 1111
#define DIV_4 0x00ff00ff

unsigned int ReverseIntBinary_2(unsigned int num)
{
	/**
	 * 二进制相关运算符优先级：
	 * 按位非~ 、左移<< 、右移>> 、按位与& 、按位异或^ 、按位或| 、位操作并赋值，如<<=等
	 */
	num = (num >> 1 & DIV_1) | ((num & DIV_1) << 1);
	num = (num >> 2 & DIV_2) | ((num & DIV_2) << 2);
	num = (num >> 4 & DIV_3) | ((num & DIV_3) << 4);
	num = (num >> 8 & DIV_4) | ((num & DIV_4) << 8);
	// 最后一步，合并 
	num = (num >> 16) | (num << 16);

	return num;
}

/**
 * @brief 辅助显示函数，将一个数值转换为二进制字符串
 * @param num 需要转换的数值
 * @return 转换为二进制的字符长
 */
string FormatToBinary(unsigned int num)
{
	string str = "";
	int bits = 32;

	while (bits > 0)
	{
		if (num > 0)
		{
			str.insert(str.begin(), 1, 48 + (num % 2));
			num /= 2;
		}
		else
		{
			str.insert(str.begin(), 1, 48);
		}
		
		--bits;
		if (bits >= 4 && bits % 4 == 0)
		{
			str.insert(str.begin(), 1, 32);
		}
	}

	return str;
}

int main()
{
	unsigned int num = 43261596;

	cout << "Before reverse: " << num;
	cout << "\nBinary: " << FormatToBinary(num);

	unsigned int num1 = ReverseIntBinary_1(num);
	cout << "\n\n[Solution 1]";
	cout << "\nAfter reverse: " << num1 
		<< "\nBinary: " << FormatToBinary(num1);

	unsigned int num2 = ReverseIntBinary_2(num);
	cout << "\n\n[Solution 2]";
	cout << "\nAfter reverse: " << num2
		<< "\nBinary: " << FormatToBinary(num2);

	cout << endl;
	return 0;
}
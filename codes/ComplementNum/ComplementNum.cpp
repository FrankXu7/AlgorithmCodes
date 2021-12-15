/**************************************************************************************************
 * 【题目描述】
 * 对整数的二进制表示取反（0 变 1 ，1 变 0）后，再转换为十进制表示，可以得到这个整数的补数。
 * 
 * 特别注意：不处理前导零，比如32位整数，二进制为101，对应补数的二进制为010，前导零不做处理。
 * 
 * 【输入】
 * 十进制数5，对应二进制数为101
 * 【输出】
 * 十进制数2，对应二进制数为010
 *
 * 【解题思路】
 * 异或运算，想将一个二进制数（假设为 NUM）取反，可以用只由 1 组成的二进制数和 NUM 进行异或运算，即得到其
 * 取反结果，故此处需要一个和 NUM 具有相同位数（不包含前导零）的完全由 1 组成的二进制数，所以需要找出 NUM 
 * 的二进制数最高位的 1，方法为将数字 1 逐步左移的结果，与 NUM 进行大小比较，从而确定 NUM 的二进制数中最
 * 高位数字 1 的下标（假设为 maxBitIdx）。然后将数字 1 左移 (maxBitIdx + 1) 后减去1，即可得到一个完全由1
 * 构成的和NUM具有相同位数（不包含前导零）的二进制数，将其与 NUM 进行异或运算即可得到最终结果。
 * 
 * 这里需要特别注意的是，如果 maxBitIdx 等于30，则不能直接将1左移 (maxBitIdx + 1)，因为这样左移后会触及
 * 符号位，从而导致 NUM 变号，故需要对 maxBitIdx=30 的情况做特殊处理。
 * 
 * 【解题分析】
 * 时间复杂度：O(logN) 遍历找到最高位的1，实际上数据类型确定了，最大遍历次数作为复杂度也可以看作是常数
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-12-13
 *************************************************************************************************/
#include <iostream>
#include <bitset> // 算法并不需要，仅用于打印 
using namespace std;

int ComplementNum(int num)
{
	int maxBitIdx = 0;
	for (int idx = 0; idx < 31; ++idx)
	{
		// 大致优先级：四则运算 > 位移运算 > 比较运算 > 位运算
		if (num >= (1 << idx))
		{
			maxBitIdx = idx;
		}
		else
		{
			break;
		}
	}

	// 0x7fff'ffff 二进制数为 01111111'11111111'11111111'11111111'11111111'11111111'11111111'11111111
	int maskNum = (maxBitIdx == 30) ? 0x7fffffff : (1 << (maxBitIdx + 1)) - 1;
	return (num ^ maskNum);
}

int main(int argc, int** argv)
{
	int num = 123456;
	cout << "The given number: " << num 
		<< "\nIts binary number: " << bitset<32>(num);

	int resNum = ComplementNum(num);
	cout << "\n\nThe Complement number: " << resNum
		<< "\nIts binary number: " << bitset<32>(resNum);

	cout << endl << endl;
	return 0;
}
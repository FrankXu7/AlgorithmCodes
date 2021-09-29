/**************************************************************************************************
 * 【题目描述】
 * 判断一个整数是否为 4 的幂次方，如果是，则返回true，否则返回false；
 *
 * 【输入】
 * Input number = 128
 * 【输出】
 * false
 *
 * 【解题思路】
 * 方法一：
 * 最先想到的就是对4递归整除，如果给定整数能整除4，则将整数赋值为整除4后的值，迭代操作下去，如果给定整数
 * 是4的幂，那最终会除到1，否则就不是4的幂了。
 *
 * 方法二：
 * 采用窗口算法，构造一个4的幂。对于4的幂的二进制数中，只会在最高位存在一个数字1，所以可以从1开始，每次
 * 左移两位，相当于乘上4，等价于给幂次加1，然后将这个构造的数和给定整数进行按位&运算。如果给定的数是4的幂，
 * 那么按位&运算后结果不变，否则给定整数的二进制数中，除了与构造的二进制数对应位置的数字1不变之外，其余位置
 * 的二进制位都会因为和0进行按位&运算而变成0，运算结果不等于原给定整数。
 * 
 * 方法三：
 * 和方法二中的窗口算法思想类似，因为数据类型的二进制位是有限的，比如算法中采用 long long int 最长是64个
 * 二进制位，在这个条件下，4的幂中数字1只可能出现在从低位算第一位开始的偶数位中，即，如果给定整数是4的幂，
 * 那么它的二进制数中，数字1只会的所有情况只会是：
 * 01010101 01010101 01010101 01010101 01010101 01010101 01010101 01010101
 * 所以，可以构造一个奇数位都是1的二进制数，如果给定整数是4的幂，那么与这个构造的二进制数按位&运算结果必为0，
 * 否则就不是4的幂了，该构造的二进制数可以写成：
 * 10101010 10101010 10101010 10101010 10101010 10101010 10101010 10101010
 * 写成十六进制即为：0xAAAA'AAAA'AAAA'AAAA
 * 
 * 需要特别注意的是，构造的数本质上是一个遮罩，如果一个不是4的幂能透过这个遮罩，容易被误判，比如数字5，二进制
 * 是101，但它不是4的幂。因为4本身就是2的2次幂，且4的幂也必然是2的幂，所以可以先判断是否为2的幂，然后再用
 * 构造的遮罩数过滤。
 * 
 * 方法四：
 * 4的幂表示为：4^N，等价于 (3+1)^N，对该表达式进行二项式展开（二项式展开有公式），展开后，最后一项是1，前
 * N-1项中，至少包含一个因子3，所以最终展开结果可写成如下形式：3(展开结果排除最后一项提取公因式3) + 1，可以
 * 看出如果给定整数是4的幂，那么将其对3取模，结果必为1，同样需要注意的是，有些非4的幂对3取模结果也是1，
 * 比如：22%3 = 1，所以和方法三相同，也要先确定是2的幂，再对3取模余1，才是4的幂。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1) 算法采用64位整数，每次左移2，最多需要移动32次，可认为是常数复杂度
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 * 方法四：
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-09-29
 **************************************************************************************************/
#include <iostream>
using namespace std;

bool PowerOfFour_1(long long int num)
{
	while (num > 1)
	{
		if (num % 4 == 0)
			num /= 4; // num >> 2;
		else
			return false;
	}

	return (num == 1);
}

bool PowerOfFour_2(long long int num)
{
	long long int windowNum = 1;

	for (long long int idx = 0; idx < 32; ++idx)
	{
		if ((windowNum & num) == num)
			return true;

		windowNum <<= 2;
	}

	return false;
}

bool PowerOfFour_3(long long int num)
{
	/**
	 * 运算符大致优先级：四则运算 > 移位 > 比较 > 按位运算
	 *
	 * 判断是否为2的幂有三种方式；
	 * (num & -num) == num;
	 * (num & num - 1) == 0;
	 * ((1 << 30) % num == 0);
	 */
	return ((num & -num) == num) && ((num & 0xAAAA'AAAA'AAAA'AAAA) == 0);
}

bool PowerOfFour_4(long long int num)
{
	/**
	 * 运算符大致优先级：四则运算 > 移位 > 比较 > 按位运算
	 * 
	 * 判断是否为2的幂有三种方式；
	 * (num & -num) == num;
	 * (num & num - 1) == 0;
	 * ((1 << 30) % num == 0);
	 */
	return ((num & num - 1) == 0) && (num % 3 == 1);
}

int main(int argc, char* argv[])
{
	long long int inputNum = 5; // 1099'511'627'776;
	cout << "Input number is: " << inputNum;

	cout << "\n\n[Solution 1] Is power of four? " << (PowerOfFour_1(inputNum) ? "YES" : "NO");

	cout << "\n\n[Solution 2] Is power of four? " << (PowerOfFour_2(inputNum) ? "YES" : "NO");

	cout << "\n\n[Solution 3] Is power of four? " << (PowerOfFour_3(inputNum) ? "YES" : "NO");

	cout << "\n\n[Solution 4] Is power of four? " << (PowerOfFour_4(inputNum) ? "YES" : "NO");

	cout << endl << endl;
	return 0;
}
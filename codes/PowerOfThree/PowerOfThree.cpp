/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数，判断是否为3的幂。
 * 
 * 【输入】
 * Input number = 81 = 3^4
 * 【输出】
 * true
 *
 * 【解题思路】
 * 方法一：
 * 将给定的整数不断对3递归取余，如果整数是3的幂，那最终所除结果会是1，否则整数就不是3的幂。
 * 
 * 方法二：
 * 因为一个数按照3倍来线性增长，速率是比较快的，而数据类型是有上限的，算法中采用 unsigned int 数据类型，
 * 其最大值为 4294967295，由此可知3的幂的最大值为：3^20 = 3486784401，如果整数是3的幂，其必然可以写成
 * 多个3相乘的形式，也必然是3^20的约数。所以可以通过判断整数是否为 unsigned int 中最大的3的幂的约数，
 * 来判断给定整数是否为3的幂。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(logN) 实际为以3为底N的对数，这个值即为除3的次数
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-27
 **************************************************************************************************/
#include <iostream>
using namespace std;

bool PowerOfThree_1(unsigned int num)
{
	while (num > 0 && num % 3 == 0)
	{
		num /= 3;
	}

	return (num == 1);
}

bool PowerOfThree_2(unsigned int num)
{
	const static unsigned int MaxPowerOfThree = 3486784401; // 3^20

	return (3486784401 % num == 0);
}

int main(int argc, char** argv)
{
	unsigned int inputNum = 99;

	cout << "Input number is: " << inputNum;

	cout << "\n\n[Solution 1] Is power of three: " << (PowerOfThree_1(inputNum) ? "YES" : "NO");
	cout << "\n\n[Solution 2] Is power of three: " << (PowerOfThree_2(inputNum) ? "YES" : "NO");

	cout << endl << UINT_MAX;

	cout << endl << endl;
	return 0;
}
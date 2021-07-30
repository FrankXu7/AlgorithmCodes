/**************************************************************************************************
 * 【题目描述】
 * 计算一个数字阶乘后，末尾有几个零。
 * 要求时间复杂度低于O(N)
 *
 * 【输入】
 * 20! = 2,432,902,008,176,640,000
 *		18,446,744,073,709,551,615    unsigned long long int 的最大值
 * 
 * 
 * 【输出】
 * Zero number tail count: 4
 *
 * 【解题思路】
 * 任意数字的乘积，最终都能转化成0-9单个数字的乘积，而对0-9单个数字来说，两个单个数字相乘，
 * 结果中尾数要存在0，则必然存在2*5的情况，比如8*5=4*2*5=40，对于阶乘的定义来说，
 * 数字2自然是不会缺少的，比如16就能分解为4个2的乘积，而数字5相对来说少很多，所以，
 * 针对能够产生0的必然组合2*5来说，找到阶乘中所有5的个数，即为最终阶乘结果尾数中0的个数。
 * 
 * 对于任意的连续5个数字，必定有至少1个2*5的组合会为最终结果贡献一个尾数0，可以将需要阶乘的数除以5，
 * 将数字按5分成N份，每一份至少都有一个2*5组合，所以有N个0尾数。如果N是一个大于等于5的数字，则要继续
 * 递归的除以5，并累加所除的结果。因为，对小于10以内的数字来说，连续5个数字只有1个2*5的组合，
 * 但是对于十位数，百位数以上的数字，任意连续5个数字，可能有多个2*5的组合，比如[21-25]这5个数字，
 * 22*25已经贡献了一组2*5，即11*2*5*5，但还剩一个5，所以[21-25]贡献了两组2*5，综上，大致过程为：
 * （1）阶乘数字除5取整，值即为尾数0的个数；
 * （2）如果上一个步骤除的结果大于等于5，则继续递归除以5，并累加所有除得的结果，即为总的尾数0的个数。
 *
 * 【解题分析】
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-07-29
 **************************************************************************************************/
#include <iostream>
using namespace std;

unsigned long long int FactorialZeroTailNum(unsigned long long int num)
{
	unsigned long long int zeroTails = 0;
	while (num >= 5)
	{
		zeroTails += static_cast<unsigned long long int>((num /= 5));
	}

	return zeroTails;
}

int main()
{
	unsigned long long int num = 21;
	// ULLONG_MAX 定义类型的最大值 
	if (num > 20) num = 20;

	// 用于显示实际的阶乘结果 
	unsigned long long int factorial = 1;
	unsigned long long int _num = num;
	while (_num > 0) factorial *= (_num--);

	cout << num << "! = " << factorial
		<< "\nZero number tail count: " << FactorialZeroTailNum(num) 
		<< endl << endl;

	cout << endl << ULLONG_MAX << endl;

	return 0;
}
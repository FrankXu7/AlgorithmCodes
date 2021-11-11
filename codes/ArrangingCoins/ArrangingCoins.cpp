/**************************************************************************************************
 * 【题目描述】
 * 你总共有 n 枚硬币，并计划将它们按阶梯状排列。对于一个由 k 行组成的阶梯，其第 i 行必须正好有 i 枚硬币。
 * 阶梯的最后一行可能是不完整的。给你一个数字 n ，计算并返回可形成完整阶梯行的总行数。
 * 
 * 【输入】
 * coins=8
 * 【输出】
 * 可形成的完整行：3
 * 第一行：1
 * 第二行：2
 * 第三行：3
 * 第四行：2
 *
 * 【解题思路】
 * 方法一：
 * 第 k 行会消耗 k 个硬币，所以可以从第一行开始进行循环，循环的条件就是硬币数量要大于当前的行数，再对行数
 * 自加 1，然后硬币减去行数得到剩余硬币，当剩余硬币小于等于自加后的行数时，肯定达不到下一行要求的硬币数量
 * 了，退出循环。
 * 
 * 方法二：
 * 按照题意，各个完整的阶梯行构成一个 d=1 的等差数列，它的通项公式和求和公式为：
 * （1）通项公式：an = a1 + (n-1)d = n 
 * （2）求和公式：Sn = n(a1+an) / 2 = n(n+1) / 2
 * 故前 k 行的的硬币数量为：coins = k(k+1) / 2，还可以推导出，如果有 n 个硬币，那至少可以构成一行（即第
 * 一行，n必然要是大于等于1的），至多可以构成n行（即n=1时），所以对于 n 个硬币所能构成的完整阶梯行，必然
 * 在 [1,n] 的区间内。
 * 
 * 故可以用二分法查找，在 [1,n] 中找到满足求和公式：coins = k*(k+1) / 2 中 k 的值，几位所求行数。
 * 
 * 方法三：
 * 根据方法二硬币数量和行数的求和等式：coins = k(k+1) / 2，这其中只有 k 是未知量，可以构成一个一元二次
 * 方程，即：k^2 + k - 2coins = 0，可知：
 * （1）判别式 △ = b^2 - 4ac = 8coins + 1
 * （2）根式：k = ( -b ± √△ ) / 2，这里显然只需要其正根
 * 所以，可形成的完整阶梯行 k = ( -1 + √(8coins + 1) ) / 2，需要注意数字类型的上下转换，不要丢失了数据。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 * 方法三：
 * 复杂度分析：sqrt、log 这样的接口，通过调用相应的CPU指令来获取结果，函数本身不进行数值运算，故实际复杂
 *             度取决于CPU支持的指令集，不深入研究。若要实现 sqrt，有二分法，牛顿迭代法等。可参考当前代
 *             码参考分支的实现：AlgorithmCodes/codes/PerfectSquare/PerfectSquare.cpp
 *
 * @author FrankX
 * @date 2021-11-11
 **************************************************************************************************/
#include <iostream>
using namespace std;

int ArrangingCoins_1(int coins)
{
	int rows = 0;

	while (coins > rows)
	{
		++rows;
		coins -= rows;
	}

	return rows;;
}

int ArrangingCoins_2(int coins)
{
	int left = 1, right = coins, mid = 0;

	while (left < right)
	{
		/**
		 * 括号内之所以要加上1，是保证 mid 的值不会出现恒定不变的情况，当 right - left 的差值小于2的时候，
		 * (right - left + 1) / 2恒等于0（此时的情况必然为：right = left - 1），这样 mid 就会恒定不变，
		 * 从而导致进入死循环。
		 */
		mid = left + (right - left + 1) / 2;

		if (static_cast<long long int>(mid * (mid + 1)) <= static_cast<long long int>(2 * coins))
		{
			// mid 不加1是因为分支判断包含相等的情况，不能将之排除 
			left = mid;
		}
		else
		{
			right = mid - 1;
		}
	}

	return left;
}

int ArrangingCoins_3(int coins)
{
	// 方程的判别式：b^2 - 4ac
	double b2_minus_4ac = sqrt(static_cast<long long int>(8 * coins + 1));
	// 方程的正根：( -b + √(b^2 - 4ac) ) / 2
	int positiveRoot = static_cast<int>((-1 + b2_minus_4ac) / 2);

	return positiveRoot;
}

int main(int argc, char* argv[])
{
	int coins = 8;
	cout << "Coins number is: " << coins;

	cout << "\n\n[Solution 1] The complete row count: " << ArrangingCoins_1(coins);

	cout << "\n\n[Solution 2] The complete row count: " << ArrangingCoins_2(coins);

	cout << "\n\n[Solution 3] The complete row count: " << ArrangingCoins_3(coins);

	cout << endl << endl;
	return 0;
}
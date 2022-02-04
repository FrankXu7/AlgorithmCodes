/**************************************************************************************************
 * 【题目描述】
 * 定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。返回被除数
 * dividend 除以除数 divisor 得到的商，并且省略小数部分。
 *
 * 【输入】
 * dividend = 10; divisor = 3;
 * 【输出】
 * quotient = 3; 商值取整
 *
 * 【解题思路】
 * 32位整数的除法可能会导致计算结果溢出，然后还有一些容易导致出错的边界情况，先行排除之：
 * （1）当被除数 dividend == INT_MIN 时：
 *      ① 如果除数 divisor == 1，则商为 INT_MIN;
 *      ② 如果除数 divisor == -1，则商为 2^31，而 INT_MAX == 2^31 - 1，产生了溢出，故直接返回最大正值
 * （2）当除数 divisor == INT_MIN 时，因为 INT_MIN 拥有32位有符号整数的最大绝对值，如果被除数与之不等，
 *      那商必为小于1的小数，可省略之，直接返回0，反之则返回1；
 * （3）显然，除数 divisor 也不能为零，否则返回0作为结果；
 *
 * 在具体的算法中，为了不考虑被除数和除数的符号问题，统一将它们同号，这里同号为正号。
 *
 * 方法一：
 * 暴力法，除法本质上是将被除数按除数分成多份，此分成的份数即为除法的商，故可以循环用被除数减去除数，每减
 * 去一次，商自加，直到被除数小于除数为止，返回最后自加累计到的商，即为相除结果。
 *
 *
 * 方法二：
 * 在暴力法中，如果被除数或除数的值非常之大，就会有很高的时间复杂度，可针对此方法进行优化。在循环中，每次
 * 减去除数太慢，可以增加减去的步长，使得被除数以更快的速度逼近除数。这里需要两层循环，最外层保证被除数在
 * 小于除数时跳出。然后，在每次执行内层循环前，将减去的步长初始化为除数，同时初始化移位的位数，即翻倍的倍
 * 数，因为题意要求不能使用乘法，故通过左移1位来翻倍，内层循环中被除数每次减去的是逐渐翻倍后的除数，而后
 * 商加上移位的位数，这里特别注意的是内层循环的跳出条件是被除数小于当前翻倍操作后的除数。跳出内层循环不代
 * 表找到了商，也可能是因为翻倍的除数太大，导致跳出循环，所以，执行之前所说的初始化步长和位移数后，继续进
 * 行内层循环。
 *
 *
 * 方法三：
 * 因为会将被除数和除数都取正值，且已经排除了商等于零的情况，故此时的商一定在区间 [1, INT_MAX] 内，可以
 * 通过二分法查找，将每次的中间值 mid 作为商，然后用快速乘算法判断这个商是否会小于等于被除数除以除数的值。
 * 如果是，不代表此时的商是最终结果，可能有更大的 mid 值满足条件，故将 mid+1 作为新的二分查找的左边界，反
 * 之，如果不是，就表示此时的商太大了，需要缩小搜索范围，将 mid-1 作为新的二分查找的有边界。
 *
 * 快速乘算法原理：计算机中加法比乘法会快很多，而且对于乘法来说更容易导致溢出。快速乘算法通过将乘法转换为
 * 加法，使得计算速率更快，且快速乘算法中的移位操作也不会溢出。它的本质就是将乘数转换为一个2的N次幂的多项
 * 式，比如数字11等价于(2^0+2^1+2^3)，其实就是二进制转十进制的公式，从而将式子 NUM*11 等价的转换为另一个
 * 式子：NUM * (2^0+2^1+2^3)，具体步骤：
 * （1）循环中，每次将乘数和数字1按位‘与’运算的结果不等于零，即代表其所在二进制位置的数字是 1，需要将乘积
 *      加上被乘数，此被乘数可能是经过累加后的；处理完乘数的最低位后，需要将其右移1位，以排除掉最低位；
 * （2）每次循环都要将被乘数翻倍，相当于左移1位，这里等价于自加了2的次幂；
 *
 *
 * 方法四：
 * 在方法三中，每次二分查找到的 mid 都需要时间复杂度 O(logN) 来执行快速乘算法，以判断 mid 是否满足条件，
 * 可以用一种 “类二分法” 的思想来优化，将 dividend >= quotient*divisor 中的商 quotient 转换为 2^i 的多
 * 项式之和，其实就是二进制转十进制的公式，故可得不等式：dividend >= [ 2^i + 2^(i+1) + ...]*divisor，其
 * 中的 i 的最大值满足 divisor*2^i <= dividend。
 * 
 * “类二分法” 的主体思想就是找到幂次 i 累计过程中所有满足不等式 divisor*2^i <= dividend 时的 divisor 的
 * 值，然后存储在一个数组中，然后逆序遍历该数组，数组元素满足 divisor*2^i <= dividend 时，将被除数减去当
 * 前的 divisor*2^i，被除数 dividend 会逐渐减小，与此同时，商 quotient 需要加上 2^i，本质上，相当于公式
 * dividend >= [ 2^i + 2^(i+1) + ...]*divisor 不等式左右两侧同时除去了一个 divisor*2^i，所以商肯定对应
 * 要加上 2^i，直到结束循环，所得商即为整除结果。
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 此处的N可视为 INT_MAX，即最差的情况为求 INT_MAX / 1 的商
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(log^2 N) 需要 logN 来查找商值，对每个商值，需要 logN 的快速乘判断：商 * 除数 <= 被除数
 * 空间复杂度：O(1)
 * 方法四：
 * 时间复杂度：O(logN) 实际上为 O(2logN)，统计出满足 divisor*2^i <= dividend 时的 divisor*2^i 的值需要
 *                     O(logN)，而后计算商也需要 O(logN)
 * 空间复杂度：O(logN) 用以存储 divisor*2^i 的数量
 *
 * @author FrankX
 * @date 2021-02-01
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief 辅助函数，处理相除溢出和非法相除的分支
 * @param dividend 被除数引用
 * @param divisor 除数引用
 * @param sign 被除数和除数的符号值引用，因为会进行同号处理，需要保存符号
 * @param quotient 商产生溢出或触及边界情况时，在返回true的同时保存最终返回结果
 * @return 返回bool值，标记商是否有产生溢出或触及边界
 */
inline bool DivJudge(int& dividend, int& divisor, int& sign, int& quotient)
{
	// 分支处理除法溢出问题，比如 -2^31 / -1 = 2^31 产生溢出，INT32最大值为 2^31 - 1 
	if (dividend == INT_MIN)
	{
		if (divisor == 1)
		{
			quotient = INT_MIN;
			return true;
		}
		else if (divisor == -1)
		{
			// 负数溢出，返回最大正值 
			quotient = INT_MAX;
			return true;
		}
	}

	// 除数为最大负值意味着拥有最大绝对值，如果被除数与之不等，相除结果必为零 
	if (divisor == INT_MIN)
	{
		quotient = (dividend == INT_MIN ? 1 : 0);
		return true;
	}
	else if (divisor == 0) // 除数不能为零 
	{
		quotient = 0;
		return true;
	}

	// 同号处理，都取正值 
	if (dividend < 0)
	{
		dividend = -dividend;
		sign = -sign;
	}
	if (divisor < 0)
	{
		divisor = -divisor;
		sign = -sign;
	}

	// 取正值的情况下，被除数小于除数，整除的结果必然为零 
	if (dividend < divisor)
	{
		quotient = 0;
		return true;
	}

	return false;
}

int TwoIntegerDivision_1(int dividend, int divisor)
{
	int quotient = 0;
	int sign = 1;

	if (DivJudge(dividend, divisor, sign, quotient))
		return quotient;

	while (dividend >= divisor)
	{
		dividend -= divisor;
		++quotient;
	}

	return (sign > 0 ? quotient : -quotient);
}

int TwoIntegerDivision_2(int dividend, int divisor)
{
	int quotient = 0;
	int sign = 1;

	if (DivJudge(dividend, divisor, sign, quotient))
		return quotient;

	int moveCount = 1; // 统计移位的位数 
	int divStep = divisor; // 保存经过移位后，被除数需要减去的值 
	while (dividend >= divisor)
	{
		moveCount = 1;
		divStep = divisor;
		while (dividend >= divStep)
		{
			dividend -= divStep;
			quotient += moveCount;

			// 防一手左移溢出 
			if (moveCount << 1 < 0 || divStep << 1 < 0)
				break;

			moveCount <<= 1;
			divStep <<= 1;
		}
	}

	return (sign > 0 ? quotient : -quotient);
}

int TwoIntegerDivision_3(int dividend, int divisor)
{
	int quotient = 0;
	int sign = 1;

	if (DivJudge(dividend, divisor, sign, quotient))
		return quotient;

	/**
	 * 每次传入的被乘数 multiplicand，即作为 dividend/divisor 的整除结果，判断这个整除结果是否满足关系
	 * 式：dividend >= multiplicand*multiplier，其中 multiplicand*multiplier 等价于 quotient*divisor
	 */
	auto FastMulti = [&dividend](int multiplicand, int multiplier) -> bool {
		int addResult = 0;

		while (multiplicand)
		{
			if (multiplicand & 1)
			{
				/**
				 * 如果累加结果满足关系式：addResult+multiplier > dividend，即如果接下来的一次累加会导
				 * 致不满足 dividend >= multiplicand*multiplier，返回标识。这里用 dividend-multiplier
				 * 的形式是为了防止 addResult+multiplier 溢出
				 */
				if (addResult > dividend - multiplier)
					return false;

				addResult += multiplier;
			}

			/**
			 * 此处必须排除 multiplicand == 1 的分支，因为，当满足该分支时，multiplier 已取得满足关系式
			 * dividend >= multiplicand*multiplier 的最大值，否则在此之前就会从 (return false;) 语句结
			 * 束函数，所以此时若不排除此分支的话，必然会因为满足了(multiplier > dividend - multiplier)
			 * 从而导致函数错误的从 (return false;) 语句结束
			 */
			if (multiplicand != 1)
			{
				// 和之前 return false 的分支判断同理，multiplier 会累加到 addResult 中 
				if (multiplier > dividend - multiplier)
					return false;
				else
					multiplier <<= 1;
			}

			multiplicand >>= 1;
		}

		return true;
	};

	int left = 1, right = INT_MAX, mid = 0;
	while (left <= right)
	{
		/**
		 * 将 dividend/divisor = quotient 转换为 dividend = quotient*divisor，然后用快速乘算法实现乘
		 * 法，因为被除数和除数都取了正值，并且取整，所以实际等式为：dividend >= quotient*divisor，找到
		 * 满足该等式的最大 quotient，即为 dividend/divisor 的整除结果，而每次计算所得的 mid 的值，就是
		 * 当前的整除结果，使用快速乘算法判断其正确性，并找到最大的正确整除值
		 */
		mid = left + ((right - left) >> 1);
		if (FastMulti(mid, divisor))
		{
			quotient = mid;
			if (quotient == INT_MAX)
				break;
			left = mid + 1;
		}
		else
			right = mid - 1;
	}

	return (sign > 0 ? quotient : -quotient);
}

int TwoIntegerDivision_4(int dividend, int divisor)
{
	int quotient = 0;
	int sign = 1;

	if (DivJudge(dividend, divisor, sign, quotient))
		return quotient;

	// 逐一存储 divisor*2^i，直到某个 divisor*2^i > dividend 为止 
	vector<int> divisorArr = {divisor};
	while (divisorArr.back() <= dividend - divisorArr.back())
	{
		divisorArr.emplace_back(divisorArr.back() << 1);
	}

	/**
	 * 逆序遍历减去之前所得数组，将被除数 dividend 逐一减去 divisor*2^i <= dividend 时的 divisor*2^i，
	 * 在减去 divisor*2^i 的同时，商也要加上对应的次幂 2^i 
	 */
	for (int idx = divisorArr.size() - 1; idx >= 0; --idx)
	{
		if (divisorArr[idx] <= dividend)
		{
			quotient += (1 << idx);
			dividend -= divisorArr[idx];
		}
	}

	return (sign > 0 ? quotient : - quotient);
}

int main(int argc, char** argv)
{
	int dividend = 100, divisor = 2;
	cout << "Calculate " << dividend << " / " << divisor
		<< " = " << static_cast<double>(dividend) / divisor;

	cout << "\n\n[Solution 1] Calculate result: " << TwoIntegerDivision_1(dividend, divisor);

	cout << "\n\n[Solution 2] Calculate result: " << TwoIntegerDivision_2(dividend, divisor);

	cout << "\n\n[Solution 3] Calculate result: " << TwoIntegerDivision_3(dividend, divisor);

	cout << "\n\n[Solution 4] Calculate result: " << TwoIntegerDivision_4(dividend, divisor);

	cout << endl << endl;
	return 0;
}
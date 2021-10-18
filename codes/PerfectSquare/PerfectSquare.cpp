/**************************************************************************************************
 * 【题目描述】
 * 给定一个正整数，判断是否为完全平方数，是则返回true，否则返回false，不能使用内置库函数，如 sqrt 等。
 * 完全平方数：即一个正整数N，存在一个小于N的正整数n，使得 n*n=N
 * 
 * 【输入】
 * Input number: 66
 * 【输出】
 * FALSE
 * 
 * 【解题思路】
 * 方法一：
 * 依据两个乘数相同，可知总共就只有10种情况：0*0, 1*1, ... 8*8, 9*9，分析结果可知，个位数必然是
 * {0,1,4,5,6,9}，故可将给定正整数NUM对10取余，若个位数为 {2,3,7,8}，则必然不是完全平方数。然后依次
 * 遍历小于等于NUM/2的自然数，判断它们的平方是否等于给定的正整数NUM，这里需要注意，如果NUM是0或1，它们的
 * 完全平方数就是它们自己，可先排除之。NUM的数值越大，那么确定最终结果的值，和NUM/2的差值也就越大，
 * 所以，随着NUM的增大，遍历次数的增长小于NUM的增长速率。
 * 
 * 方法二：
 * 进一步优化方法一，在一个序列中（这里是一组自然数序列）找到给定的数，应该首先考虑二分法。
 * 在区间 [2, NUM/2] 中，除了0和1的平方根是它们自身外，存在完全平方根的最小的数是4，它的完全平方根是4/2，
 * 在此之后的数的完全平方根必然大于NUM/2；
 * 
 * 方法三：
 * 牛顿迭代法：给定正整数NUM如果存在完全平方根 x，则必有 x^2 = NUM，所以将求完全平方根转换为求
 * f(x) = x^2 - NUM = 0 的根。
 * 过程为先任意取一点作为根，这里取 NUM/2，过 x = NUM/2 做曲线 x^2 的切线，求得交于X轴的切点，将该切点
 * 的X轴坐标作为下一条切线的切点，重复此过程，切线逐渐向满足 x^2 - NUM = 0 的根逼近，当逼近到等式成立，
 * 则找到了NUM的完全平方根，如果有 x^2 < NUM，则表明NUM的完全平方根不存在。
 * 
 * 依据 f(x) = x^2 - NUM = 0 推导的牛顿迭代公式：x = (x + NUM/2) / 2，将x迭代带入此公式求出满足等式的根。
 * 详细公式推导，参考泰勒公式的前置理论，罗尔定理中的费马引理。
 * 
 * 牛顿迭代推导公式随笔地址：
 * https://zhuanlan.zhihu.com/p/421954743
 * 
 * 方法四：
 * 总结规律，若已知某个数N存在平方根，则其平方根为 N^2，显然它下一个存在完全平方根的数为 (N+1)^2，
 * 所以，对于两两相邻的存在完全平方根的数而言，它们存在如下关系：(N+1)^2 - N^2 = 2N+1，
 * 即从0开始，接下来的一个存在完全平方根的数是从0开始逐渐加上对应奇数序列中的一个奇数，例如：
 * 0*0=0  +1
 * 1*1=1  +3
 * 2*2=4  +5
 * 3*3=9  +7
 * 4*4=16 +9
 * ...    ...
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N/2) 随着N越大，遍历到N/2的可能性就越小
 * 空间复杂度：O(1) 需要一个无序set存储不可能存在的个位数，确认为4个
 * 方法二：
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 * 方法四：
 * 时间复杂度：O(sqrt(N))
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-10-15
 **************************************************************************************************/
#include <iostream>
#include <unordered_set>
using namespace std;

/** 0-9的平方根的结果的个位数不存在{2,3,7,8}，用一个无序set保存以便判断存在性 */
const unordered_set<unsigned int> InvalidSingles{ 2,3,7,8 };

bool PerfectSquare_1(unsigned int num)
{
	if (num < 2) return true;
	
	if (InvalidSingles.find(num % 10) != InvalidSingles.end()) return false;

	// 随着num逐渐增大，calcSquare最终确认值和maxCycle的差值也会越大 
	unsigned int maxCycle = static_cast<unsigned int>(num / 2);
	unsigned int calcSquare = 0;
	for (unsigned int n = 2; n <= maxCycle; ++n)
	{
		calcSquare = n * n;
		if (calcSquare == num)
		{
			return true;
		}
		else if (calcSquare > num)
		{
			return false;
		}
	}

	return false;
}

bool PerfectSquare_2(unsigned int num)
{
	if (num < 2) return true;

	if (InvalidSingles.find(num) != InvalidSingles.end()) return false;

	unsigned int leftNum = 2, rightNum = num / 2, midNum = 0, squareNum = 0;

	while (leftNum <= rightNum)
	{
		midNum = leftNum + (rightNum - leftNum) / 2;
		squareNum = midNum * midNum;

		if (squareNum > num)
			rightNum = midNum - 1;
		else if (squareNum < num)
			leftNum = midNum + 1;
		else
			return true;
	}

	return false;
}

bool PerfectSquare_3(unsigned int num)
{
	if (num < 2) return true;

	if (InvalidSingles.find(num) != InvalidSingles.end()) return false;

	unsigned int squareNum = num / 2;
	while (squareNum * squareNum > num)
	{
		squareNum = (squareNum + num / squareNum) / 2;
	}

	return (squareNum * squareNum == num);
}

bool PerfectSquare_4(unsigned int num)
{
	if (num < 2) return true;

	if (InvalidSingles.find(num) != InvalidSingles.end()) return false;

	unsigned int tempNum = num, oddNum = 1;

	while (tempNum >= oddNum)
	{
		tempNum -= oddNum;
		oddNum += 2;
	}

	return (tempNum == 0);
}

int main(int argc, char* argv[])
{
	unsigned int inputNum = 100;
	cout << "Input unsigned integer number: " << inputNum
		<< "\nCalc square by library function: " << sqrt(inputNum);

	cout << "\n\n[Solution 1] Is a valid perfect square number: "
		<< (PerfectSquare_1(inputNum) ? "TRUE" : "FALSE");

	cout << "\n\n[Solution 2] Is a valid perfect square number: "
		<< (PerfectSquare_2(inputNum) ? "TRUE" : "FALSE");

	cout << "\n\n[Solution 3] Is a valid perfect square number: "
		<< (PerfectSquare_3(inputNum) ? "TRUE" : "FALSE");

	cout << "\n\n[Solution 4] Is a valid perfect square number: "
		<< (PerfectSquare_4(inputNum) ? "TRUE" : "FALSE");

	cout << endl << endl;
	return 0;
}
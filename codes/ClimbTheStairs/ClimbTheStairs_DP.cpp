/**************************************************************************************************
 * 【题目描述】
 * “爬楼梯”，每次只能跨一阶或两阶，爬到第 n 阶有几种方法。
 *
 * 【输入】
 * inputN=15
 * 【输出】
 * routeCount=987
 *
 * 【解题思路】
 * 这个问题的解，依赖于问题的规模，即 n 值越大，爬到第 n 阶的方法越多，且没有一个显式的表达式定义解；
 * 可利用动态规划算法求解，该问题中，爬到第 n 阶，则上一步必定为 n-1 或 n-2 阶，因为每次只能跨一阶或两阶；
 * 故可以得到一个状态转移方程：f(n) = f(n-1) + f(n-2)，这其实就是一个斐波那契数列。
 * 需要特别注意的是，爬楼方法数量随着 n 值会增长的越来越快，需要注意变量边界问题。
 * 算法的时间复杂度为O(n)，空间复杂度依据不同的需求会有所不同：
 * （1）需要每一步的爬楼方法数，则需要数组来记录，空间复杂度为 O(n)，
 * （2）只需要给定 n 的爬楼方法数，则只需要记录每次爬楼的前两步的爬楼方法数即可，空间复杂度为O(1)；
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)，这里空间复杂度更高是因为存储了每一步的方法数量，是否需要存储依据实际情况。
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)，这里只存储当前步和前两步的方法数量，因为题意只要求给定n阶的爬楼方法数。
 * 
 * @author FrankX
 * @date 2021-04-15
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

unsigned int ClimbTheStairs_1(const unsigned int& n)
{
	if (n <= 2) return n;
	else if (n >= 47) return 0; // n>=47 时，解会越出 unsigned int 边界 

	vector<unsigned int> midN = { 1, 2 };

	for (unsigned int idx = 2; idx < n; ++idx)
	{
		midN.push_back(midN[idx - 1] + midN[idx - 2]);
	}

	return midN[n - 1];
}

unsigned int ClimbTheStairs_2(const unsigned int& n)
{
	if (n <= 2) return n;
	else if (n >= 47) return 0; // n>=47 时，解会越出 unsigned int 边界 

	unsigned int oneStepBack = 1; // 第 n-1 步的解 
	unsigned int twoStepBack = 2; // 第 n-2 步的解 
	unsigned int curStep = 0; // 第 n 步的解 

	for (unsigned int idx = 2; idx < n; ++idx)
	{
		curStep = oneStepBack + twoStepBack;
		oneStepBack = twoStepBack;
		twoStepBack = curStep;
	}

	return curStep;
}

int main()
{
	unsigned int inputN = 0;
	cout << "Input N: " ;
	cin >> inputN;

	cout << ClimbTheStairs_1(inputN) << endl;
	cout << ClimbTheStairs_2(inputN) << endl;

	return 0;
}

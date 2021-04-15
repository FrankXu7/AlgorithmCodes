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
 * 该问题中，爬到第 n 阶，则上一步必定为 n-1 或 n-2 阶，因为每次只能跨一阶或两阶；
 * 这其实就是一个斐波那契数列，利用递归求解；
 * 需要特别注意的是，爬楼方法数量随着 n 值会增长的越来越快，需要注意变量边界问题。
 * 
 * 算法的时间复杂度为O(2^n)，且递归调用会占用很多栈空间，最好还是用动态规划算法求解。
 *
 * @author FrankX
 * @date 2021-04-15
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

long long int counts = 0;

unsigned int ClimbTheStairs(const unsigned int& n)
{
	if (n <= 2) return n;
	else if (n >= 47) return 0; // n>=47 时，解会越出 unsigned int 边界 
	else
	{
		++counts;
		return (ClimbTheStairs(n - 1) + ClimbTheStairs(n - 2));
	}
}

int main()
{
	unsigned int inputN = 0;
	cout << "Input N: " ;
	cin >> inputN;

	chrono::system_clock::time_point start = chrono::system_clock::now();
	cout << ClimbTheStairs(inputN) << endl;

	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() << endl;
	cout << "Count: " << counts << endl;

	return 0;
}

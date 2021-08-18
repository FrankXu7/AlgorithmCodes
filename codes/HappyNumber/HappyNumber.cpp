/**************************************************************************************************
 * 【题目描述】
 * 判断一个无符号整数是否为快乐数。
 * 对于一个无符号整数n，将n的各位的平方根之和，赋值给n，得到一个新的无符号整数，重复这个过程，
 * 最终平方和要么为1，要么会在一组数之间永远循环。平方和最终为1时，最初的整数n即为快乐数。
 *
 * 【输入】
 * Input Number: 19
 * 【输出】
 * Is Happy Number: YES
 * 1*1 + 9*9 = 82
 * 8*8 + 2*2 = 68
 * 6*6 + 8*8 = 100
 * 1*1 + 0*0 + 0*0 = 1
 *
 * 【解题思路】
 * 首先明确一点，任意一个无符号整数，其各位上的平方之和，以及递归计算下去的平方之和，
 * 都一定是小于等于原整数的位数都取9时的平方和：
 * 比如一个三位数 666，它的各位的平方和是108，继续求平方和是65，后面继续求的话，要么是快乐数平方和为1，
 * 要么在一组数之间循环，但它们都一定小于等于 999 各位的平方之和 243；
 * 
 * 方法一：
 * 针对思路所述的性质，可以将每次求得的各位上的平方之和，存在一个数据集合中，如果下一次求得的平方和
 * 存在于数据集合，则代表进入了一组数的循环，标识原整数不是快乐数，否则平方和会遇到等于1的情况。
 * 因为平方和要么等于1是快乐数，要么进入一组循环，所以即使原整数数值很大，平方和的数据集合也不会有
 * 数据量巨大的问题，比如 UINT_MAX = 4294967295，其平方和数据集合大小仅为17；
 * 
 * 方法二：
 * 在数学上，不快乐数有如下性质：不快乐数的计算最终都会进入到
 * 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 的循环中。
 * 所以针对方法一，可以将数据集合固定为 { 4, 16, 37, 58, 89, 145, 42, 20 } ，如果是不快乐数，则一定会
 * 有平方和的结果在这个数据集合中，否则就是快乐数。
 * 
 * 方法三：
 * 利用不快乐数会在一组数中循环的特性，使用快慢指针法，如果是快乐数，则快指针会先计算到1，如果是不快乐数，
 * 则快慢指针终将相遇。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(logN) 每次计算平方和的代价是O(logN)，而进一步递归计算复杂度是O(log(logN))...
 * 空间复杂度：O(logN)
 * 方法二：
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1) 硬编码的数据集合是固定的，利用里快乐数的数学特性
 * 方法三：
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-08-18
 **************************************************************************************************/
#include <iostream>
#include <unordered_set>
using namespace std;

/**
 * @brief 辅助函数，计算一个无符号整数的平方和
 * @param num 待计算的无符号整数
 * @return 返回其各位上的平方和
 */
unsigned int GetSquareSum(unsigned int num)
{
	unsigned int sum = 0;
	while (num > 0)
	{
		sum += static_cast<unsigned int>(pow(num % 10, 2));
		num /= 10;
	}
	
	return sum;
}

bool HappyNumber_1(unsigned int num)
{
	// 收集所有平方和结果 
	unordered_set<unsigned int> gather;

	num = GetSquareSum(num);
	while (num != 1 && gather.find(num) == gather.end())
	{
		gather.insert(num);
		num = GetSquareSum(num);
	}

	return (num == 1);
}

bool HappyNumber_2(unsigned int num)
{
	// 不快乐数最后都会进入到这个数据集合的循环中 
	const unordered_set<unsigned int> gather{ 4, 16, 37, 58, 89, 145, 42, 20 };

	GetSquareSum(num);
	while (num != 1 && gather.find(num) == gather.end())
		num = GetSquareSum(num);

	return (num == 1);
}

bool HappyNumber_3(unsigned int num)
{
	unsigned int slowNum = num;
	unsigned int fastNum = GetSquareSum(num);

	while (fastNum != 1 && fastNum != slowNum)
	{
		slowNum = GetSquareSum(slowNum);
		fastNum = GetSquareSum(GetSquareSum(fastNum));
	}

	return (fastNum == 1);
}

int main()
{
	unsigned int num = UINT_MAX;
	cout << "Input Number: " << num;

	cout << "\n[Solution 1] Is Happy Number: " 
		<< (HappyNumber_1(num) ? "YES\n" : "NO\n");

	cout << "\n[Solution 2] Is Happy Number: "
		<< (HappyNumber_2(num) ? "YES\n" : "NO\n");

	cout << "\n[Solution 3] Is Happy Number: "
		<< (HappyNumber_3(num) ? "YES\n" : "NO\n");

	cout << endl;
	return 0;
}
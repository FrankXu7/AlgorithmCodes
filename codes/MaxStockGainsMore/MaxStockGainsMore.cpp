/**************************************************************************************************
 * 【题目描述】
 * 给定一个股票价格数组，它的第idx个元素表示第idx天股票的价格。
 * 选择其中某一天买入股票，并且在未来某一个不是买入天的日子卖出，
 * 可进行多次交易，需要卖出手上股票才能买入，可在同一天卖出后再买入。
 *
 * 如果买入后卖出必亏，即价格数组为一个降序数组，表示无利润，返回0.
 *
 * 【输入】
 * prices=[7,1,5,3,6,4]
 *
 * 【输出】
 * maxGains= (prices[2]-prices[1]) + (prices[4]-prices[3]) = 4 + 3 = 7
 *
 * 【解题思路】
 * 记录一个买入的价格，初始化为第一天的价格，只要遍历到的价格减去记录的买入价格为正，则卖出股票。
 * 即，只要有收益，就交易。
 * 一次交易完成后，继续下一次收益为正的交易，统计所有交易之和，即为最大收益。大致步骤：
 * （1）记录买入价格，遍历到的价格减去记录的买入价格为正，则卖出，交易完成；
 * （2）将（1）中卖出的价格记录为新的买入价格，继续遍历，只要收益为正即卖出，知道遍历完成。
 * 
 * 【解题分析】
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-08
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int MaxStockGainsMore(vector<int>& prices)
{
	if (prices.empty()) return 0;

	unsigned int dataSize = prices.size();
	// 本次交易出售的时间下标 
	unsigned int sellIdx = 0;
	// 买入时的价格，为当前天之前的最低价格
	int minPrice = prices[0];
	// 各次交易收益之和，即为总收益，记录其中的最大值 
	int maxGains = 0;

	for (unsigned int idx = sellIdx; idx < dataSize; ++idx)
	{
		if (prices[idx] < minPrice)
		{
			minPrice = prices[idx];
		}
		else if (prices[idx] - minPrice > 0)
		{
			// 只要收益为正，就卖出 
			maxGains += prices[idx] - minPrice;

			// 本次交易完成，最低价重置为当前遍历到的价格 
			minPrice = prices[idx];
		}
	}

	return maxGains;
}

int main()
{
	vector<int> prices = { 2,10,9,12 };
	cout << "Stock prices:\n";
	for (vector<int>::iterator itr = prices.begin(); itr != prices.end(); ++itr)
		cout << *itr << ", ";
	cout << endl;

	cout << "\nAfter multiple deals, max gains: " << MaxStockGainsMore(prices) << endl;

	return 0;
}
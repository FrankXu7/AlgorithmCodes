/**************************************************************************************************
 * 【题目描述】
 * 给定一个股票价格数组，它的第idx个元素表示第idx天股票的价格。选择其中某一天买入股票，并且在未来某一个不
 * 是买入天的日子卖出，可进行多次交易，需要卖出手上股票才能买入，可在同一天卖出后再买入。
 *
 * 如果买入后卖出必亏，即价格数组为一个降序数组，表示无利润，返回0。
 *
 * 【输入】
 * prices=[7,1,5,3,6,4]
 *
 * 【输出】
 * maxGains= (prices[2]-prices[1]) + (prices[4]-prices[3]) = 4 + 3 = 7
 *
 * 【解题思路】
 * 从贪心角度考虑：有收益，就交易。贪心，即只从局部考虑，找到局部最优解，汇总起来，即可看作全局的最优解。
 * 
 * 大致步骤：
 * （1）假设在第i-1天买入，然后在第i天卖出，如果收益大于零，则交易（局部最优）。
 * （2）遍历整个价格数组，相当于按遍历顺序从头到尾两两元素作为局部，考虑它们的最优解，即局部最大收益（收
 *      益为正）。统计所有局部最大收益，即可认为是全局的最大收益。
 * 
 * 需要特别注意的是，贪心算法只是计算最大利润，并不是实际交易过程。
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-09
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int MaxStockGainsMore(vector<int> &prices)
{
	if (prices.empty())
		return 0;

	unsigned int dataSize = prices.size();
	int maxGains = 0;

	for (unsigned int idx = 1; idx < dataSize; ++idx)
	{
		// 只要收益为正，就交易
		if (prices[idx] - prices[idx - 1] > 0)
		{
			maxGains += prices[idx] - prices[idx - 1];

			cout << "\nBuy prices[" << idx - 1 << "]=" << prices[idx - 1]
				 << "    Sell prices[" << idx << "]=" << prices[idx];
		}
	}

	return maxGains;
}

int main()
{
	vector<int> prices = {7, 1, 5, 3, 6, 4};
	cout << "Stock prices:\n";
	for (vector<int>::iterator itr = prices.begin(); itr != prices.end(); ++itr)
		cout << *itr << ", ";
	cout << endl;

	cout << "\nAfter multiple deals, max gains: " << MaxStockGainsMore(prices) << endl;

	return 0;
}
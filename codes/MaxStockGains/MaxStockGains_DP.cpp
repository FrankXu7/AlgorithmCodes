/**************************************************************************************************
 * 【题目描述】
 * 给定一个股票价格数组，它的第idx个元素表示第idx天股票的价格。
 * 选择其中第idx天买入股票，并且在未来某一个不是买入天的日子卖出，
 * 只能进行一次买入卖出，设计算法计算可获得的最大利润。
 * 如果买入后卖出必亏，即价格数组为一个降序数组，表示无利润，返回0.
 *
 * 【输入】
 * prices=[7,9,4,3,8,2,1,4,9]
 *
 * 【输出】
 * maxGains=prices[8]-prices[7]=9-1=8
 *
 * 【解题思路】
 * 计算第idx天卖出获得的最大收益，肯定希望之前买入的是最低价，所以需要记录第idx天之前的最低买入价；
 * 同时，第idx天之前的最大收益，并不代表是总的最大收益，也需要记录第idx天之前的最大收益便于后续遍历比较。
 * 利用动态规划思想：第idx天的最大收益 = Max( 记录的最大收益，第idx天售出价格-记录的最低买入价格 )
 * 具体实现步骤：
 * （1）最低买入价格初始化为首天价格，后续遍历小于记录的最低买入价，则更新记录的最低买入价格；
 * （2）当前出售收益，若大于记录的最大收益，则更新记录的最大收益；
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-04
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int MaxStockGains_DP(const vector<int> &prices)
{
	if (prices.size() == 0)
		return 0;

	int maxGains = 0;
	int minPrice = prices[0];
	unsigned int dataSize = prices.size();

	// 仅仅用于打印购买和售出的下标
	unsigned int buyIdx = 0, sellIdx = 0;

	for (unsigned int idx = 0; idx < dataSize; ++idx)
	{
		if (prices[idx] < minPrice)
		{
			minPrice = prices[idx];
			buyIdx = idx;
		}
		// 这里需要注意一定要else if，因为买入和售出不能是同一天
		else if (prices[idx] - minPrice > maxGains)
		{
			maxGains = prices[idx] - minPrice;
			sellIdx = idx;
		}
	}

	// 显示买入和卖出的信息，卖出的时间肯定晚于买入的时间
	if (sellIdx > buyIdx)
	{
		cout << "\n\nBuy prices[" << buyIdx << "]=" << prices[buyIdx]
			 << "\nSell prices[" << sellIdx << "]=" << prices[sellIdx] << endl;
	}

	return maxGains;
}

int main()
{
	vector<int> prices = {7, 6, 4, 3, 1, 2, 1, 4, 4, 9};
	cout << "Stock prices:\n";
	for (const int &num : prices)
		cout << num << ", ";

	cout << "\nMax Gains: " << MaxStockGains_DP(prices) << endl;

	return 0;
}

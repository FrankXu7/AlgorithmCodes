/**************************************************************************************************
 * 【题目描述】
 * 给定一个股票价格数组，它的第idx个元素表示第idx天股票的价格。选择其中某一天买入股票，并且在未来某一个不
 * 是买入天的日子卖出，只能进行一次买入卖出，设计算法计算可获得的最大利润。如果买入后卖出必亏，即价格数组
 * 为一个降序数组，表示无利润，返回0.
 *
 * 【输入】
 * prices=[7,9,4,3,8,2,1,4,9]
 *
 * 【输出】
 * maxGains=prices[8]-prices[7]=9-1=8
 *
 * 【解题思路】
 * 能最直观想到的就是简单粗暴的双重遍历。遍历价格数组，并依次与当前遍历数据后面的价格计算利润，找到最大利
 * 润。
 * 
 * 【解题分析】
 * 时间复杂度：O(N^2)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-06-04
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int MaxStockGains(const vector<int> &prices)
{
	if (prices.size() == 0)
		return 0;

	int maxGains = 0;
	unsigned int dataSize = prices.size();

	// 用于打印买入和卖出的下标，与算法本身无关
	unsigned int saveBuyIdx = 0, saveSellIdx = 0;

	for (unsigned int buyIdx = 0; buyIdx < dataSize; ++buyIdx)
	{
		for (unsigned int sellIdx = buyIdx + 1; sellIdx < dataSize; ++sellIdx)
		{
			if (prices[sellIdx] - prices[buyIdx] > maxGains)
			{
				maxGains = prices[sellIdx] - prices[buyIdx];

				saveBuyIdx = buyIdx;
				saveSellIdx = sellIdx;
			}
		}
	}

	// 显示买入和卖出的信息，卖出的时间肯定晚于买入的时间
	if (saveSellIdx > saveBuyIdx)
	{
		cout << "\n\nBuy prices[" << saveBuyIdx << "]=" << prices[saveBuyIdx]
			 << "\nSell prices[" << saveSellIdx << "]=" << prices[saveSellIdx] << endl;
	}

	return maxGains;
}

int main()
{
	vector<int> prices = {7, 6, 4, 3, 1, 2, 1, 4, 4, 4};
	cout << "Stock prices:\n";
	for (const int &num : prices)
		cout << num << ", ";

	cout << "\nMax Gains: " << MaxStockGains(prices) << endl;

	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 
 *
 * 【输入】
 * 
 *
 * 【输出】
 * 
 *
 * 【解题思路】
 * 
 *
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int MaxStockGains(const vector<int>& prices)
{
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
	vector<int> prices = { 7,6,4,3,1,2,1,4,4,4 };
	cout << "Stock prices:\n";
	for (const int& num : prices) cout << num << ", ";

	cout << "\nMax Gains: " << MaxStockGains(prices) << endl;

	return 0;
}

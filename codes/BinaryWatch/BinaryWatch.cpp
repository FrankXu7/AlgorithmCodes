/**************************************************************************************************
 * 【题目描述】
 * 二进制手表如下定义：有10个LED灯，前4个表示小时数，后6个表示分钟数，并分别对应数字如下：
 * 小时（0-11）：8	4	2	1
 * 分钟（0-59）：36	16	8	4	2	1
 * 当对应的LED灯亮起，则表示当前数字有效，如小时数中8对应的灯亮起，分钟数中36对应的灯亮起，其余灯都不亮，
 * 则对应的时间为 8:36
 * 
 * 给定一个数字，表示亮起的LED灯的数量，返回所有可能的时间点，其中分钟数小于零时，返回的格式前要加一个‘0’，
 * 而小时数不用，例如 6:08
 * 
 * 【输入】
 * LED ligths on = 1
 * 【输出】
 * Possibility times = [0:01, 0:02, 0:04, 0:08, 0:16 0:32, 1:00, 2:00, 4:00, 8:00]
 *
 * 【解题思路】
 * 方法一：
 * 由题意可知，前4位代表小时数，最大值为11，即为 1011，后6位代表分钟数，最大值为59，即为 111011，故时间
 * 数值上的最大值（11:59）为 1011 1110111，由此可知给定的数若其二进制中有超过8个数字1，则为非法数值，排
 * 除之。
 * 
 * 在此基础上，可利用一个两层循环，外层遍历所有的小时数 [0, 11]，内层遍历所有的分钟数 [0, 59]，当遍历确
 * 定一个小时和分钟数时，判断这两个数字二进制数中数字1的个数之和是否为给定的亮灯数量，是则将其推入最终数
 * 组反汇之。
 * 
 * 方法二：
 * 根据方法一的分析，先将给定数字二进制数中数字1的数量超过8个的排除。按照题意，其实可以将所有的可能性枚举
 * 出来，可以避免每次都对所有的可能性进行一一比较，建立两个无序map，分别用于小时数和分钟数，key用以标记对
 * 应的小时或分钟的数值二进制中有几个数字一，value则存储对应的所有可能性结果。
 * 
 * 然后按照小时数二进制中数字1的个数从[0, 3]遍历（当然这里肯定也要小于等于给定的亮灯数量），既然小时数占
 * 用的数字1个数确定，那分钟数占用的数字1的个数也得以确认。分别去查找之前得出的无序map中是否存在对应结果，
 * 若存在，则利用双层遍历得出它们所有的组合序列，返回之。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(1) 外层和内层遍历上界分别是小时数12和分钟数60，故复杂度是常数 
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(1) 和方法一同理，遍历的上界是有穷的，故复杂度也是常数 
 * 空间复杂度：0(1) 用了常数数量的空间来存储占用不同二进制数字1的小时和分钟数所对应的可能性 
 *
 * @author FrankX
 * @date 2021-10-28
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

/**
 * @brief 辅助函数，统计一个数字二进制表示中数字1的个数，
 * 利用核心算子 N & (N-1) 逐步消除二进制数中最后一个1，
 * 统计消除至0时的计算次数即为二进制数中1的个数
 * @param calcNum 需要计算的数字
 * @return 返回二进制数中1的个数
 */
unsigned int CalcBits(unsigned int calcNum)
{
	unsigned bitsCount = 0;
	while (calcNum > 0)
	{
		calcNum &= (calcNum - 1);
		++bitsCount;
	}

	return bitsCount;
}

vector<string> BinaryWatch_1(unsigned int bitsNum)
{
	vector<string> times;
	// 按照题意，不可能同时亮8个LED灯 
	if (bitsNum > 8) return times;

	for (unsigned int hours = 0; hours < 12; ++hours)
	{
		for (unsigned int minutes = 0; minutes < 60; ++minutes)
		{
			if (CalcBits(hours) + CalcBits(minutes) == bitsNum)
			{
				times.emplace_back(to_string(hours) +
					(minutes < 10 ? ":0" : ":") + to_string(minutes));
			}
		}
	}

	return times;
}

vector<string> BinaryWatch_2(unsigned int bitsNum)
{
	vector<string> times;
	// 按照题意，不可能同时亮8个LED灯 
	if (bitsNum > 8) return times;

	// 枚举小时数和分钟数的可能性 
	static unordered_map<unsigned int, vector<string>> HoursMap;
	if (HoursMap.empty())
	{
		for (unsigned int hours = 0; hours < 12; ++hours)
		{
			HoursMap[CalcBits(hours)].emplace_back(to_string(hours));
		}
	}
	static unordered_map<unsigned int, vector<string>> MinutesMap;
	if (MinutesMap.empty())
	{
		for (unsigned int minutes = 0; minutes < 60; ++minutes)
		{
			MinutesMap[CalcBits(minutes)].emplace_back((minutes < 10 ? "0" : "") + to_string(minutes));
		}
	}

	// 小时数二进制中数字1不超过3个，且比如要小于给定的亮灯数量 
	for (unsigned int hoursBits = 0; (hoursBits <= 3 && hoursBits <= bitsNum); ++hoursBits)
	{
		unsigned int minutesBits = bitsNum - hoursBits;
		if (HoursMap.find(hoursBits) == HoursMap.end() ||
			MinutesMap.find(minutesBits) == MinutesMap.end())
			continue;

		for (auto& hour : HoursMap[hoursBits])
			for (auto& minute : MinutesMap[minutesBits])
				times.emplace_back(hour + ":" + minute);
	}

	return times;
}


int main(int argc, char** argv)
{
	unsigned int bitsNum = 2;
	cout << "Bits number: " << bitsNum;

	cout << "\n\n[Solution 1] Possibility watch times: \n";
	auto times1 = BinaryWatch_1(bitsNum);
	for (unsigned int idx = 0; idx < times1.size(); ++idx)
	{
		cout << times1[idx] << "\t";
		if ((idx + 1) % 10 == 0) cout << endl;
	}

	cout << "\n\n[Solution 2] Possibility watch times: \n";
	auto times2 = BinaryWatch_2(bitsNum);
	for (unsigned int idx = 0; idx < times2.size(); ++idx)
	{
		cout << times2[idx] << "\t";
		if ((idx + 1) % 10 == 0) cout << endl;
	}

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 定义 Nim游戏 规则：
 * （1）有且仅有一堆石头；
 * （2）轮流从石头堆里移走[1,3]块石头，自己作为先手；
 * （3）轮到某个玩家能一次性拿走剩余全部石头时，则该玩家获胜；
 * 
 * 【输入】
 * Stone Number = 7
 * 【输出】
 * true 自己先手拿3个，必胜
 *
 * 【解题思路】
 * 方法一：
 * 每一轮移走石头后，显然剩余的石头数量会比之前更少，可以从只有一个石头的情况开始，统计当石头数量为N时，
 * 先手拿走M块石头时，必胜。则会产生一个key-value，即N-M的映射关系，当统计到给定数量时，即可知给定的石头
 * 数量是否存在自己先手移动必胜的情况。
 * 
 * 方法二：
 * 博弈论，采用数学归纳法：
 * （1）石头数量小于等于3块时，先手必胜；
 * （2）石头数量是4块时，先手必败，因为无论先手拿走[1,3]块，剩余的石头数量在下一轮都能被对手全部拿完；
 * （3）石头数量在[5,7]块时，先手总有办法使得下一轮对手面对剩余4块石头的情况，对手会必败；
 * （4）石头数量为8块时，无论先手拿几块，对手总有办法使得后面某一轮自己会面对石头剩余4块的情况；
 * 利用数学归纳法可知：自己先手的话，如果剩余石头数量不是4的整数倍，则总有办法使得最终某一轮让对手面临只
 * 剩余4块石头的情况，自己必胜。
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际会比N稍大，因为每轮需要针对最大可移动数量进行处理，题设为最大可移动3块 
 * 空间复杂度：O(N) 实际情况key-value键值对肯定是少于给定的石头数量的 
 * 方法二：
 * 时间复杂度：O(1)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-24
 **************************************************************************************************/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool NimGame_1(unsigned int num)
{
	// 每轮最多可移动3块石头，自己先手，剩余数量小于等于3，则必胜 
 	if (num <= 3) return true;

	// 必胜策略映射：key-剩余石头数量，value-先手时必胜的移动数量；若不存在，则先手必败 
	unordered_map<unsigned int, unsigned int> winMap = { {1,1},{2,2},{3,3} };

	// 当前剩余石头数量 
	unsigned int curNum = 4;

	while (curNum <= num)
	{
		// 依题意每轮最多可移动3块 
		for (unsigned int moveNum = 1; moveNum <= 3; ++moveNum)
		{
			// 在自己移动了moveNum后，对手找不到必胜的移动策略，保存自己的必胜移动方案 
			if (winMap.find(curNum - moveNum) == winMap.end())
			{
				winMap.insert(make_pair(curNum, curNum - moveNum));
				break;
			}
		}

		++curNum;
	}

	return (winMap.find(num) != winMap.end());
}

bool NimGame_2(unsigned int num)
{
	if (num <= 3) 
		return true;

	return (num % 4 != 0);
}

int main(int argc, char* argv[])
{
	unsigned int inputNum = 7;
	cout << "The stone's number: " << inputNum;

	cout << "\n\n[Solution 1] Can I win if I move first? " << (NimGame_1(inputNum) ? "YES" : "NO");
	cout << "\n\n[Solution 2] Can I win if I move first? " << (NimGame_2(inputNum) ? "YES" : "NO");

	cout << endl << endl;
	return 0;
}
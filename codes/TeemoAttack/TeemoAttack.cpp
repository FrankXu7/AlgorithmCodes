/**************************************************************************************************
 * 【题目描述】
 * 在《英雄联盟》的世界中，有一个叫 “提莫” 的英雄。他的攻击可以让敌方英雄艾希（寒冰射手）进入中毒状态。当
 * 提莫攻击艾希，艾希的中毒状态正好持续 duration 秒。正式地讲，提莫在 t 发起发起攻击意味着艾希在时间区间
 * [t, t + duration - 1] 处于中毒状态。如果提莫在中毒影响结束前再次攻击，中毒状态计时器将会 [重置]，在新
 * 的攻击之后，中毒影响将会在 duration 秒后结束。给你一个 非递减 的整数数组 timeSeries ，下标 idx 的元素
 * 表示提莫在 timeSeries[idx] 秒时对艾希发起攻击，以及一个表示中毒持续时间的整数 duration 。
 * 
 * 需要求得 艾希处于中毒状态的总秒数。
 * 
 * 【输入】
 * timeSeries = [6, 8, 14];
 * duration = 5
 * 【输出】
 * totalTime = 12;
 * 分析：
 * （1）第6秒发起攻击，攻击持续到第10秒结束，累计中毒时间5秒；
 * （2）第8秒发起攻击，上一轮攻击还未结束，再次攻击则时间重置，故攻击持续到第12秒结束，累计中毒时间7秒；
 * （3）第14秒发起攻击，上一轮攻击已经结束，故攻击从第14秒开始，持续到第18秒结束，累计中毒时间12秒；
 * 
 * 【解题思路】
 * 方法一：
 * 首先，需要保存一个攻击持续到的时间戳 timeStamp，该时间戳和攻击是否有重叠无关，其值等于本次攻击发起的时
 * 间，加上中毒持续时间。假设发起攻击的时间为 time，如果满足 time <= timeStamp，即代表两次攻击有重叠，可
 * 以先计算攻击没有重叠时，攻击持续到的时间戳 time + duration，将之减去已保存的上一轮攻击持续到的时间戳，
 * 故有 (time + duration) - timeStamp，计算结果即为消除掉攻击重叠的时间后，本次攻击较上次多出来的中毒持
 * 续时间，统计之。
 * 
 * 方法二：
 * 计算总的中毒时间，关键在于考虑攻击重叠的情况，依题意攻击重叠时，时间会重置（可认为重叠发生时，上轮攻击
 * 可视作无效）。可以先计算假设没有任何重叠发生时的总的中毒时间，即攻击序列数组长度乘上中毒持续时间即可，
 * 然后再来处理攻击重叠的部分，核心思想就是找到重叠部分的重叠时间，用之前已计算出的总时间减去之。若两次攻
 * 击发起的时间间隔会小于中毒持续时间，即 timeSeries[idx + 1] - timeSeries[idx] < duration，表示攻击发
 * 生重叠，需要注意的是该差值表示攻击的间隔时间，而不是重叠的时间，用 duration 减之即为两次攻击的重叠时间，
 * 而后将总时间减去两次攻击的重叠时间即可。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-12-17
 *************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int TeemoAttack_1(vector<int>& timeArr, int duration)
{
	int totalTime = 0;
	int timeStamp = 0;

	for (int& time : timeArr)
	{
		if (time <= timeStamp)
		{
			/**
			 * 本次攻击和上次有重叠，先计算出假设没有重叠时，中毒应该持续到的时间戳 time + duration，然
			 * 后减去上一次的时间戳，该差值即为消除重叠部分后，本次攻击较上次多出来的中毒持续时间 
			 */
			totalTime += time + duration - timeStamp;
		}
		else
		{
			// 没有重叠，累计中毒时间直接加上攻击的持续时间即可 
			totalTime += duration;
		}

		// 每次中毒持续到的时间戳，都是发起攻击时的时间加上中毒持续时间，和是否重叠无关 
		timeStamp = time + duration;
	}

	return (timeArr.size() > 0 ? totalTime : 0);
}

int TeemoAttack_2(vector<int>& timeArr, int duration)
{
	// 先计算出攻击序列总共持续的中毒时间，如果两次攻击有重叠，则会重复的时间统计 
	unsigned int arrSize = timeArr.size();
	int totalTime = arrSize * duration;

	// 消除有攻击重叠时的重复时间统计 
	for (unsigned int idx = 0; idx < arrSize - 1; ++idx)
	{
		// 两轮攻击时间间隔小于中毒持续时间，即为攻击重叠 
		if (timeArr[idx + 1] - timeArr[idx] < duration)
		{
			// 中毒持续时间减去两轮攻击的时间间隔，即为攻击重叠的时间 
			totalTime -= duration - (timeArr[idx + 1] - timeArr[idx]);
		}
	}

	return totalTime;
}

int main(int argc, char** argv)
{
	vector<int> timeArr{ 6,10,19 };
	int duration = 5;

	cout << "Attack time array:\n";
	for (int& time : timeArr)
		cout << time << ", ";
	cout << "\nAttack duration time: " << duration;

	cout << "\n\n[Solution 1] Total attack duration time: " << TeemoAttack_1(timeArr, duration);

	cout << "\n\n[Solution 2] Total attack duration time: " << TeemoAttack_2(timeArr, duration);

	cout << endl << endl;
	return 0;
}
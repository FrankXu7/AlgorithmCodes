/**************************************************************************************************
 * 【题目描述】
 * 给定一个含有n个元素的数组，找到其中的多数元素，所谓多数元素即出现次数 大于n/2 的元素。
 * 这里题设数组必定非空，且一定存在多数元素。
 *
 * 【输入】
 * InputArr = [6, 3, 6, 6, 3, 6, 2, 6, 1, 6]
 *
 * 【输出】
 * MajorityElement = 6
 *
 * 【解题思路】
 * 最先直接想到的方法，是牺牲空间复杂度来统计各个元素的出现次数。用一个map来记录元素出现次数，map的键
 * 为元素值，值为该元素出现的次数，同时用一个临时变量记录遍历到当前为止的出现元素最多的值。
 * 需要注意的是，算法逻辑本身是找到出现次数最多的元素，并没有验证多出元素的出现次数是大于n/2的，
 * 因为题设中假定非空数组一定存在多数元素。
 *
 * 【解题分析】
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 *
 * @author FrankX
 * @date 2021-07-08
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <map>
using namespace std;

/** 算法函数依据题意，假设所给数组非空，且一定存在一个出现 n/2 次以上的元素  */
template<typename T>
const T MajorityElement_1(vector<T>& dataArr)
{
	// 此处只统计了出现最多的元素，但按照题意，给定数组中，出现最多的元素，出现次数一定大于 n/2 
	T majorityNum = 0;
	map<T, unsigned int> countMap;

	for (typename vector<T>::iterator itr = dataArr.begin(); itr != dataArr.end(); ++itr)
	{
		// map在使用成员访问操作符时，如果没有这个key，会默认创建一个 
		++countMap[*itr];
		if (countMap[*itr] > countMap[majorityNum])
		{
			majorityNum = *itr;
		}
	}

	return majorityNum;
}

int main()
{
	vector<int> dataArr = { 6, 3, 6, 6, 3, 6, 2, 6, 1, 6 };
	cout << "Array:\n";
	for (vector<int>::iterator itr = dataArr.begin(); itr != dataArr.end(); ++itr)
		cout << *itr << ", ";
	
	cout << "\nThe majority element is: " << MajorityElement_1(dataArr) << endl;

	return 0;
}
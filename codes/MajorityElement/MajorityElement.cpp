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
 * 方法一：
 * 最先直接想到的方法，是牺牲空间复杂度来统计各个元素的出现次数。用一个map来记录元素出现次数，map的键
 * 为元素值，值为该元素出现的次数，同时用一个临时变量记录遍历到当前为止的出现元素最多的值。
 * 需要注意的是，算法逻辑本身是找到出现次数最多的元素，并没有验证多出元素的出现次数是大于n/2的，
 * 因为题设中假定非空数组一定存在多数元素。
 * 
 * 方法二：
 * 考虑到多数元素的个数大于n/2，若一个数组是已经排序好的，那么这个在下标 n/2 位置的元素，一定是多数元素。
 * 对没有排序好的元素，可自实现一个简单的排序算法，这里直接用语言提供的 std::sort 接口。
 * 
 * 方法三：
 * 利用摩尔投票法，将两两相邻的一对不相等的数据剔除，因为多数元素个数大于 n/2，所以最终剩余的投票数量大于0的元素，
 * 就是多数元素，如果最终没有元素的投票数量大于0，表示不存在个数超过 n/2 的元素。大致过程；
 * （1）默认从第一个元素开始，选为被投票对象，默认投1票；
 * （2）第二个元素和第一个元素相同，投票数量+1，否则投票数量-1，继续下一次循环；
 * （3）当前被投票元素投票数量减为0时，剔除，换下一次循环的元素作为投票对象；
 * （4）因题设多数元素必存在，所以最后的元素一定是多数元素，且投票数量会大于0；
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 * 方法二：
 * 时间复杂度：O(nlogn) std::sort的时间复杂度；如果是已经排序好的数组，时间复杂度是O(1)
 * 空间复杂度：O(1) std::sort的空间复杂度；
 * 方法三：
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 * 
 * 
 * @author FrankX
 * @date 2021-07-08
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <map>
#include <forward_list>
#include <list>
#include <algorithm>
using namespace std;

/** 算法函数依据题意，假设所给数组非空，且一定存在一个出现 n/2 次以上的元素  */
template<typename T>
const T MajorityElement_1(list<T>& dataList)
{
	// 此处只统计了出现最多的元素，但按照题意，给定数组中，出现最多的元素，出现次数一定大于 n/2 
	T majorityNum = 0;
	map<T, unsigned int> countMap;

	for (typename list<T>::iterator itr = dataList.begin(); itr != dataList.end(); ++itr)
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

template<typename T>
const T MajorityElement_2(vector<T>& dataArr)
{
	// 直接用内置排序算法
	sort(dataArr.begin(), dataArr.end());
	return dataArr[static_cast<unsigned int>(dataArr.size() / 2)];
}

template<typename T>
const T MajorityElement_3(forward_list<T>& dataList)
{
	typename forward_list<T>::iterator itr = dataList.begin();
	pair<T, int> voteNum = make_pair(*(itr++), 1);

	for (; itr != dataList.end(); ++itr)
	{
		if (voteNum.second == 0)
		{
			voteNum.first = *itr;
			voteNum.second = 1;
			continue;
		}

		(voteNum.first == *itr) ? ++voteNum.second : --voteNum.second;
	}

	return voteNum.first;
}

int main()
{
	list<int> dataList = { 6, 3, 6, 6, 3, 6, 2, 6, 1, 6 };
	cout << "Array:\n";
	for (list<int>::iterator itr = dataList.begin(); itr != dataList.end(); ++itr)
		cout << *itr << ", ";
	cout << "\n[Solution 1] The majority element is: " << MajorityElement_1(dataList) << endl;

	vector<int> dataArr = { 6, 3, 6, 6, 3, 6, 2, 6, 1, 6 };
	cout << "Array:\n";
	for (vector<int>::iterator itr = dataArr.begin(); itr != dataArr.end(); ++itr)
		cout << *itr << ", ";
	cout << "\n[Solution 2] The majority element is: " << MajorityElement_2(dataArr) << endl;

	forward_list<int> dataSingleList = { 6, 3, 6, 6, 3, 6, 2, 6, 1, 6 };
	cout << "\nArray:\n";
	for (forward_list<int>::iterator itr = dataSingleList.begin(); itr != dataSingleList.end(); ++itr)
		cout << *itr << ", ";
	cout << "\n[Solution 3] The majority element is: " << MajorityElement_3(dataSingleList) << endl;
	 
	return 0;
}
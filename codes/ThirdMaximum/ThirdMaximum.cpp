/**************************************************************************************************
 * 【题目描述】
 * 给定一个非空的整数数组，找到该数组中第三大的数，如果不存在就直接返回数组中最大的数。相同的数排名自然也
 * 是相同的，所以第三大数不存在的话，可能是数组元素不足3个，也可能是数组排名的数量不足3个。
 * 
 * 【输入】
 * Input array=[2, 2, 3, 1]
 * 【输出】
 * The third maxmium number=1
 *
 * 【解题思路】
 * 方式一：
 * 要在数组里找最值，先排个序，然后先将最大值记录下来，再记录一个变更次数，初始为1（因为初始变更为最大值），
 * 这个变更次数一是为了保证找到的数是第三大的，二是为了排除掉同一大小级别的数字有多个的情况，当变更次数达
 * 到三次时，就标识找到了第三大的数了。如果没找到，因为默认值即为非空数组最大值，故返回最大值，符合题意。
 * 
 * 方式二：
 * 排序毕竟要一定的时间复杂度，为了减少排序，可将前三大数字放入一个不重复键的set集合中。依次遍历数组元素，
 * 并将遍历元素放入set集合，set集合采用红黑树实现，可自排序，当set集合内元素超过3个时，将首元素（也即最小
 * 元素）移除，使得set集合始终保持至多3个元素，又因为是不可重复键的，所以集合内不会有相同大小级别元素，遍
 * 历完成后，set中第三个元素即为第三大元素，依题意该元素若不存在则返回首个元素，即数组最大元素。
 * 
 * 方式三：
 * 可以定义三个变量 first, second, third，分别存储前三大的数字，需要初始化为当前类型的最小值。然后开始遍
 * 历元素，遍历到的元素命名为 num，则会存在以下三种情况：
 * ① num > first;
 * ② first > num > second;
 * ③ second > num > third;
 * 之所以没有等于的情况，是为了排除掉相同大小级别的数字存在多个的情况，当满足某一条件时，则放弃掉变量third
 * 的值，比如，满足条件 ① 时，则：
 * third = second;
 * second = first;
 * first = num;
 * 
 * 最终，如果third的值不是当前类型的最小值，返回值，否则返回first；
 * 
 * 【解题分析】
 * 方式一：
 * 时间复杂度：O(NlogN) 实际上还要加上N，因为排序后还需要O(N)来遍历元素 
 * 空间复杂度：O(1)
 * 方式二：
 * 时间复杂度：O(N) 因为集合至多只有3个元素，虽然红黑树自排序复杂度为O(logN)，但这里可以认为是常数 
 * 空间复杂度：O(1)
 * 方式三：
 * 时间复杂度：O(N)
 * 空间复杂度：0(1)
 *
 * @author FrankX
 * @date 2021-11-09
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/** 为避免排序对其它算法造成影响，故数组按值传入 */
int ThirdMaximum_1(vector<int> arr)
{
	sort(arr.begin(), arr.end(),
		[](const int& a, const int& b) -> bool {return a > b; }
	);

	// 初始为有序数组中的最大数 
	int thirdMax = *(arr.begin());
	// 被操作次数，如果操作了三次，则表示找到了第三大的数 
	unsigned int opCount = 1;

	for (vector<int>::iterator itr = arr.begin() + 1; itr != arr.end(); ++itr)
	{
		if (*itr < thirdMax)
		{
			thirdMax = *itr;

			if (++opCount == 3)
			{
				return thirdMax;
			}
		}
	}

	return thirdMax;
}

int ThirdMaximum_2(vector<int>& arr)
{
	set<int> top3;

	for (auto& num : arr)
	{
		top3.insert(num);

		if (top3.size() > 3)
		{
			top3.erase(top3.begin());
		}
	}

	// 如果第三大的数不存在，则直接返回第一大的数（题意要求数组非空） 
	return top3.size() == 3 ? *(top3.begin()) : *(top3.rbegin());
}

int ThirdMaximum_3(vector<int>& arr)
{
	// 必须初始化为该类型的最小值 
	int first = -INT_MAX, second = -INT_MAX, third = -INT_MAX;

	for (auto& num : arr)
	{
		if (num > first)
		{
			third = second;
			second = first;
			first = num;
		}
		else if (first > num && num > second)
		{
			third = second;
			second = num;
		}
		else if (second > num && num > third)
		{
			third = num;
		}
	}

	// 如果第三大的数不存在，则直接返回第一大的数（题意要求数组非空） 
	return (third == -INT_MAX ? first : third);
}

int main(int argc, char** argv)
{
	vector<int> arr = { -4,-2,-2,1,2,1,2,2,3,1 };
	cout << "The given array:\n";
	for (auto& num : arr)
		cout << num << ", ";

	cout << "\n\n[Solution 1] The third maximum number is: " << ThirdMaximum_1(arr);

	cout << "\n\n[Solution 2] The third maximum number is: " << ThirdMaximum_2(arr);

	cout << "\n\n[Solution 3] The third maximum number is: " << ThirdMaximum_3(arr);

	cout << endl << endl;
	return 0;
}
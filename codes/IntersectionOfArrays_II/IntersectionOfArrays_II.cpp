/**************************************************************************************************
 * 【题目描述】
 * 给定两个数组，求它们的交集元素，并将所有交集元素存入另一个数组返回，结果数组不要求有序。
 *
 * 【输入】
 * Array1 = [1,2,2,3,6,6];
 * Array2 = [5,2,2,3,6];
 * 【输出】
 * Intersection elements = [2,2,3,6];
 *
 * 【解题思路】
 * 方法一：
 * 因为最终的交集数组元素不要求唯一，所以只要是交集，就可以推入交集数组。所以采用一个无序map统计较短数组
 * 中各个元素的数量，然后遍历较长数组，当遇到相同元素时，将交集元素推入最终数组，同时无序map对应值自减。
 *
 * 方法二：
 * 双指针法，如果两个数组是有序的情况下，可同时遍历俩数组：
 * （1）当两个下标指向的元素不同时，将更小的值所对应的下标自加；
 * （2）当两个下标指向元素相同时，则推入最终数组，然后俩下标都自加。
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(M + N)，创建无序map与元素比较分别需要一次遍历
 * 空间复杂度：O(N) N为长度更短的数组的元素数量
 * 方法二：
 * 时间复杂度：O(NlogN) 取决于两个数组排序的时间复杂度，实际为O(MlogM + NlogN)
 * 空间复杂度：O(logN) 取决于两个数组排序的空间复杂度，实际为O(logM + logN)
 *
 * @author FrankX
 * @date 2021-10-13
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<int> IntersectionOfArrays_II_1(vector<int>& vec1, vector<int>& vec2)
{
	// 区分大小数组，需要注意比较运算符应该包含所有可能性 
	vector<int>& bigVec = vec1.size() >= vec2.size() ? vec1 : vec2;
	vector<int>& smallVec = vec1.size() < vec2.size() ? vec1 : vec2;

	// 将更小的数组中元素放入map并统计数量 
	unordered_map<int, unsigned int> smallMap;
	for (auto& num : smallVec)
	{
		// 使用[]操作符访问map时，若键不存在，则会自动插入一个 
		++smallMap[num];
	}

	vector<int> resultVec;
	for (auto& num : bigVec)
	{
		if (smallMap.find(num) != smallMap.end() && smallMap[num] > 0)
		{
			resultVec.emplace_back(num);
			--smallMap[num];
		}
	}

	return resultVec;
}

vector<int> IntersectionOfArrays_II_2(vector<int>& vec1, vector<int>& vec2)
{
	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	vector<int> resultVec;
	unsigned int idx1 = 0, idx2 = 0;
	auto size1 = vec1.size();
	auto size2 = vec2.size();

	while (idx1 < size1 && idx2 < size2)
	{
		if (vec1[idx1] < vec2[idx2])
		{
			++idx1;
		}
		else if (vec1[idx1] > vec2[idx2])
		{
			++idx2;
		}
		else
		{
			resultVec.emplace_back(vec1[idx1]);
			++idx1;
			++idx2;
		}
	}

	return resultVec;
}



int main(int argc, char** argv)
{
	vector<int> vec1{ 1,2,2,6,6,3, };
	vector<int> vec2{ 5,3,6,2,2,7 };

	cout << "Array 1 elements:\n";
	for (auto& num : vec1) cout << num << ", ";
	cout << "\n\nArray 2 elements:\n";
	for (auto& num : vec2) cout << num << ", ";

	vector<int> resultVec1 = IntersectionOfArrays_II_1(vec1, vec2);
	cout << "\n\n[Solution 1] Intersection elements of two arrays:\n";
	for (auto& num : resultVec1) cout << num << ", ";

	vector<int> resultVec2 = IntersectionOfArrays_II_2(vec1, vec2);
	cout << "\n\n[Solution 2] Intersection elements of two arrays:\n";
	for (auto& num : resultVec2) cout << num << ", ";

	cout << endl << endl;
	return 0;
}
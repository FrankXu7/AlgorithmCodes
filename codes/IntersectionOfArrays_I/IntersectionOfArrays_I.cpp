/**************************************************************************************************
 * 【题目描述】
 * 给定两个数组，求它们的交集元素，并将交集元素存入另一个数组返回，结果数组不要求有序，但要求元素唯一。
 *
 * 【输入】
 * Array1 = [3,1,5,4,2,3,5];
 * Array2 = [3,2,6,7,3,8,9,0,10];
 * 【输出】
 * Intersection elements = [2,3];
 *
 * 【解题思路】
 * 方法一：
 * 最先想到的就是遍历一个数组元素，并判断其在另一个数组的存在性，不过这样会导致较高的时间复杂度，可以牺牲
 * 一定的空间复杂度降低之。将俩数组中长度较短的数组元素存入一个无序的set集合，然后对长度较长的数组进行遍
 * 历，判断元素在set集合中的存在性。因为题意要求最终数组元素唯一，所以还需要一个辅助的无序set集合存储最终
 * 结果，在将相交元素推入最终数组前，先判断一下辅助的set集合内是否存在该元素，存在则表示之前已经存储过了，
 * 不要重复存储。
 * 
 * 方法二：
 * 双指针法，如果两个数组是有序的情况下，可同时遍历俩数组：
 * （1）当两个下标指向的元素不同时，将更小的值所对应的下标自加；
 * （2）当两个下标指向元素相同时，则推入最终数组，然后俩下标都自加，这里要注意，推入之前，需要判断最终数
 *      组末尾元素是否和即将要推入的元素相同，若相同为保证元素唯一则不推入。因为俩数组已经有序，所以如果
 *      存在多个相同的相交元素，则它们一定是相邻的，故可以判断最终数组末尾元素是否和即将推入元素相同来保
 *      证唯一性。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N) 实际为O(M + N)，创建集合与元素比较分别需要一次遍历 
 * 空间复杂度：O(N) 实际为O(2N)，N为长度更短的数组的元素数量，只有完全相交且元素唯一的情况下，才会到O(2N)
 * 方法二：
 * 时间复杂度：O(NlogN) 取决于两个数组排序的时间复杂度，实际为O(MlogM + NlogN)
 * 空间复杂度：O(logN) 取决于两个数组排序的空间复杂度，实际为O(logM + logN) 
 * 
 * @author FrankX
 * @date 2021-10-09
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<int> IntersectionOfArrays_I_1(vector<int>& vec1, vector<int>& vec2)
{
	// 区分大小数组，需要注意比较运算符应该包含所有可能性 
	vector<int>& bigVec = vec1.size() >= vec2.size() ? vec1 : vec2;
	vector<int>& smallVec = vec1.size() < vec2.size() ? vec1 : vec2;

	unordered_set<int> smallSet;
	for (auto& element : smallVec)
		smallSet.insert(element);

	vector<int> resultVec;
	// 使用一个set集合保证最终数组元素唯一，set集合查找元素存在性拥有常数时间复杂度 
	unordered_set<int> resultSet;

	for (auto& element : bigVec)
	{
		if (smallSet.find(element) != smallSet.end() &&
			resultSet.find(element) == resultSet.end())
		{
			resultSet.insert(element);
			resultVec.emplace_back(element);
		}
	}

	return resultVec;
}

vector<int> IntersectionOfArrays_I_2(vector<int>& vec1, vector<int>& vec2)
{
	sort(vec1.begin(), vec1.end());
	sort(vec2.begin(), vec2.end());

	vector<int> resultVec;

	unsigned idx1 = 0, idx2 = 0;
	auto size1 = vec1.size();
	auto size2 = vec2.size();
	while (idx1 < size1 && idx2 < size2)
	{
		if (vec1[idx1] < vec2[idx2])
		{
			++idx1;
			continue;
		}
		else if (vec1[idx1] > vec2[idx2])
		{
			++idx2;
			continue;
		}
		else if (resultVec.empty() || resultVec.back() != vec1[idx1])
		{
			resultVec.emplace_back(vec1[idx1]);
		}
		++idx1;
		++idx2;
	}

	return resultVec;
}

int main(int argc, char* argv[])
{
	vector<int> vec1{ 3,1,5,4,2,3,5,66,77 };
	vector<int> vec2{ 3,2,6,7,3,8,9,0,10 };

	cout << "Array 1 elements:\n";
	for (auto& element : vec1) cout << element << ", ";
	cout << "\n\nArray 2 elements:\n";
	for (auto& element : vec2) cout << element << ", ";

	vector<int> resultVec1 = IntersectionOfArrays_I_1(vec1, vec2);
	cout << "\n\n[Solution 1] Intersection elements of two arrays:\n";
	for (auto& element : resultVec1) cout << element << ", ";

	vector<int> resultVec2 = IntersectionOfArrays_I_2(vec1, vec2);
	cout << "\n\n[Solution 2] Intersection elements of two arrays:\n";
	for (auto& element : resultVec2) cout << element << ", ";

	cout << endl << endl;
	return 0;
}
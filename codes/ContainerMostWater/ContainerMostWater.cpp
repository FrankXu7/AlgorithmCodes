/**************************************************************************************************
 * 【题目描述】
 * 原题的意思按个人理解，表述为：给定一个数组 heights，元素表示 Y 轴坐标，对应下标表示 X 轴下标，求得X*Y
 * 的最大值。
 * 
 * 【输入】
 * heights=[1,8,6,2,5,4,8,3,7];
 * 【输出】
 * 最大值为：(heights[8] - heights[1]) * min( heights[1] - heights[5] ) = (8 - 1) * min(7, 8) = 49 
 *
 * 【解题思路】
 * 按题意，想找出尽可能大的乘积，那高度要尽可能大，两个高度值之间的距离尽可能远。可使用双指针法，计算左右
 * 指针的距离，并乘上指针对应的元素的最小值，将计算结果与保存的最大值比较。然后，左右指针往中间移动，但每
 * 次移动都会导致指针距离缩短，所以应该更倾向于先移动指向的高度更小的指针，这样指针距离虽然缩短了，但是它
 * 们指向的高度的最小值也相应的增大了，即增加了高度的下限值。
 * 
 * 
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2022-01-19
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

unsigned int ContainerMostWater(vector<unsigned int>& heights)
{
	if (heights.size() <= 1) return 0;

	unsigned int leftIdx = 0, rightIdx = heights.size() - 1,
		calcContainer = 0, maxContainer = 0;

	while (leftIdx < rightIdx)
	{
		calcContainer = (rightIdx - leftIdx) * min(heights[leftIdx], heights[rightIdx]);
		if (calcContainer > maxContainer)
			maxContainer = calcContainer;

		// 优先移动高度值更小的，这样在缩短指针直接距离的同时，高度的下限也增加了 
		if (heights[leftIdx] <= heights[rightIdx])
			++leftIdx;
		else
			--rightIdx;
	}

	return maxContainer;
}

int main(int argc, char* argv[])
{
	vector<unsigned int> heights{ 1,8,6,2,5,4,8,3,7 };
	cout << "The give height array:\n";
	for (auto& num : heights) cout << num << ", ";

	cout << "\n\nThe Container with the most water: " << ContainerMostWater(heights);

	cout << endl << endl;
	return 0;
}
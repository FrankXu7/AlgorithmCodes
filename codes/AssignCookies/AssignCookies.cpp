/**************************************************************************************************
 * 【题目描述】
 * 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。对每个孩子 i，都
 * 有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 
 * s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的
 * 孩子，并输出这个最大数值。
 *
 * 【输入】
 * g = [1,2,3], s = [1,1]
 * 【输出】
 * 1，只能满足1个孩子
 *
 * 【解题思路】
 * 首先梳理孩子的胃口值数组和饼干尺寸数组，即先对两个数组排个序。然后利用贪心算法的思路：优先使用尺寸最大
 * 的饼干，满足胃口最大的孩子，如果能满足则用下一块尺寸最大的饼干继续分配，当遇到不能满足的孩子时，因为胃
 * 口值已经排序，故尝试满足前一位胃口更小的孩子，假设当前这块尺寸最大的饼干连一个孩子都不能满足，显然在它
 * 之前尺寸比它更小的饼干也不需要再看了，算法截止。
 * 
 * 
 * 【解题分析】
 * 时间复杂度：O(MlogM + NlogN) 这两个值是两个数组的排序复杂度，实际还要加上一轮遍历值 Min(O(M), O(N)) 
 * 空间复杂度：O(logM + logN) 即为排序所需空间复杂度
 * 
 * @author FrankX
 * @date 2021-11-23
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int AssignCookies(vector<int>& needs, vector<int>& cookies)
{
	sort(needs.begin(), needs.end());
	sort(cookies.begin(), cookies.end());
	
	int needsSize = needs.size(), cookiesSize = cookies.size();
	int satisfyNum = 0;
	
	int cookieIdx = cookiesSize - 1;
	for (int idx = needsSize - 1; idx >= 0 && cookieIdx >= 0; --idx)
	{
		if (cookies[cookieIdx] >= needs[idx])
		{
			--cookieIdx;
			++satisfyNum;
		}
	}
	
	return satisfyNum;
}

int main(int argc, char* argv[])
{
	vector<int> needs{1,5,6,7,8};
	vector<int> cookies{7,9};

	cout << "Needs:\n";
	for (auto& num : needs) cout << num << ", ";
	cout << "\nCookies:\n";
	for (auto& num : cookies) cout << num << ", ";

	cout << "\n\nMaxmium satisfy number: " << AssignCookies(needs, cookies);

	cout << endl << endl;
	return 0;
}
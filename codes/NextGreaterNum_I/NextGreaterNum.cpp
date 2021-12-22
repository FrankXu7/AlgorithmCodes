/**************************************************************************************************
 * 【题目描述】
 * 给定两个数组 nums1 和 nums2，数组元素唯一，且元素值均为大于等于零的整数，需要找出 nums1 中的某个元素
 * （假设为 x）在 nums2 中对应位置的右侧位置的第一个比 x 更大的元素，即被称为 nums1 中元素 x 的下一个更
 * 大元素。找出 nums1 中所有元素的下一个更大元素，并存入数组返回。
 *
 * 【输入】
 * nums1 = [4,1,2];
 * nums2 = [1,3,4,2];
 * 【输出】
 * 返回数组：[-1,3,-1]
 * 分析：
 * nums1[0] == nums2[2] == 4，可知 nums2[2] 右侧不存在比它更大的元素，下一个更大元素为-1；
 * nums1[1] == nums2[0] == 1，可知 nums2[0] 右侧首个比它更大的元素为 nums2[1]，即下一个更大元素为3；
 * nums1[2] == nums2[3] == 2，可知 nums2[3] 右侧已经没有元素了，下一个更大元素为-1；
 *
 * 【解题思路】
 * 方法一：
 * 暴力破解，遍历 nums1，找到 nums2 中对应相等的元素（假设为 x），从 nums2 中的元素 x 开始向右遍历，找到
 * 首个大于 x 的元素，推入返回数组即可。
 * 
 * 方法二：
 * 单调栈，即栈内元素是单调递增或递减的，适用于求数组中下一个更大元素的问题，按照栈先入后出的顺序，从数组
 * 末尾向头部遍历并入栈，出栈时就是从头部向尾部遍历的顺序了。首先处理 nums2，从尾部开始遍历 nums2 元素，
 * 假设当前遍历的元素为 x，出栈所有小于等于 x 的栈内元素（因为栈内元素是单调的，循环判断栈顶即可），之后，
 * 若栈内还有剩余元素，则栈顶必为 x 右侧下一个更大元素，反之更大元素设置为-1，这些信息可以通过一个无序map
 * 来保存。然后，将元素 x 入栈，因为 x 可能是下一次遍历（即前一个元素）的下一个更大元素，故需要参与之后的
 * 运算，且此处是唯一的入栈操作。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(MN) 其中M和N为两个数组的长度，复杂度可认为是平方阶
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(M+N) 在单调栈的算子中，每个元素至多会出入栈一次，故复杂度是线性关系
 * 空间复杂度：O(N) 即返回数组所需空间，同 nums1 大小，实际上单调栈也需要额外空间，但只是临时用，并不存储
 *
 * @author FrankX
 * @date 2021-12-21
 *************************************************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

vector<int> NextGreaterNum_1(vector<int>& nums1, vector<int>& nums2)
{
	vector<int> greaterNums;
	bool bMatch = false;
	int curGtNum = -1;

	for (int& num : nums1)
	{
		for (int& gtNum : nums2)
		{
			if (num == gtNum)
				bMatch = true;

			if (bMatch && gtNum > num)
			{
				curGtNum = gtNum;
				break;
			}
		}

		greaterNums.emplace_back(curGtNum);
		curGtNum = -1;
		bMatch = false;
	}

	return greaterNums;
}

vector<int> NextGreaterNum_2(vector<int>& nums1, vector<int>& nums2)
{
	vector<int> greaterNums;
	unordered_map<int, int> nums2Max;
	stack<int> stk;

	for (vector<int>::reverse_iterator itr = nums2.rbegin(); itr != nums2.rend(); ++itr)
	{
		while (!stk.empty() && stk.top() <= *itr)
		{
			stk.pop();
		}

		nums2Max[*itr] = stk.empty() ? -1 : stk.top();
		// 当前元素有可能是下一个遍历元素右侧的首个更大值，必须入栈用于之后的运算 
		stk.emplace(*itr);
	}

	for (int& num : nums1)
	{
		greaterNums.emplace_back(nums2Max.find(num) != nums2Max.end() ? nums2Max[num] : -1);
	}

	return greaterNums;
}

int main(int argc, char** aragv)
{
	vector<int> nums1{ 4,1,2 };
	vector<int> nums2{ 1,3,4,2 };

	cout << "The given numbers array 1:\n";
	for (int& num : nums1) cout << num << ", ";
	cout << "\nThe given numbers array 2:\n";
	for (int& num : nums2) cout << num << ", ";

	cout << "\n\n[Solution 1] The next greater numbers array: \n";
	auto greaterNums1 = NextGreaterNum_1(nums1, nums2);
	for (int& num : greaterNums1) cout << num << ", ";

	cout << "\n\n[Solution 2] The next greater numbers array: \n";
	auto greaterNums2 = NextGreaterNum_2(nums1, nums2);
	for (int& num : greaterNums2) cout << num << ", ";

	cout << endl << endl;
	return 0;
}
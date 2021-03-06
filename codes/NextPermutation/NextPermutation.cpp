/**************************************************************************************************
 * 【题目描述】
 * 整数数组的一个 “排列” 就是将其所有成员以序列或线性顺序排列。例如 arr = [1,2,3]，以下这些都可以视作arr
 * 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1]；而整数数组的 “下一个排列” 是指其整数的下一个字典序更大的
 * 排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在
 * 这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列，
 * 即为其元素按升序排列。
 * 
 * 例如，arr = [1,2,3] 的下一个排列是 [1,3,2]；
 * 类似地，arr = [2,3,1] 的下一个排列是 [3,1,2]；
 * 而 arr = [3,2,1] 的下一个排列是 [1,2,3]，因为 [3,2,1] 不存在一个字典序更大的排列。
 * 
 * 给你一个整数数组 nums ，找出 nums 的下一个排列。必须原地修改，只允许使用额外常数空间。
 *
 * 【输入】
 * nums=[4,5,2,6,3,1];
 * 【输出】
 * nums=[4,5,3,1,2,6];
 *
 * 【解题思路】
 * 依题意，数组的后续更大排列必然是数组中某两个元素发生交换后产生的，并且是左侧较小元素和右侧较大元素会发
 * 生交换，但此时得到的排列不一定是原排列紧接着的下一个更大排列，故在交换后，需要从交换前的左侧较小元素开
 * 始到数组末尾的子区间，进行一个升序排列，此时得到的就是原排列紧接着的下一个更大排列了。具体步骤：
 * （1）从数组尾部开始，找到首个小于其下一个元素的元素，即表示至少交换这两个元素，会得到比当前更大的序列；
 *      本质上是从后往前找到首个降序子区间的首元素的前一个元素（假设其下标为 minIdxFromEnd），该元素导致
 *      了从尾部开始往前的降序被改变。
 * （2）然后再次从尾部开始往前扫描，找到首个大于 nums[minIdxFromEnd] 的元素，因为 nums[minIdxFromEnd] 的
 *      后续元素是有序的，所以找首个即可。最终交换的就是这两个元素。
 * （3）交换完成后，从下标 minIdxFromEnd 开始到数组尾部，进行一次升序排序，此步骤保证了在交换完成后所得的
 *      更大的排列，是原排列紧接着的下一个更大的排列。
 * 
 * 【解题分析】
 * 时间复杂度：O(N) 实际为 O(2N)，找左侧较小元素和右侧较大元素各自需要遍历扫描一次
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2022-03-03
 *************************************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void NextPermutation(vector<int>& nums)
{
	/**
	 * 从数组尾部开始，找到首个小于其下一个元素的元素，即表示至少交换这两个元素，会得到比当前更大的序列；
	 * 本质上是从后往前找到首个降序子区间的首元素的前一个元素，该元素导致了从尾部开始往前的降序被改变
	 */
	int minIdxFromEnd = nums.size() - 2;
	while (minIdxFromEnd >= 0 && nums[minIdxFromEnd] >= nums[minIdxFromEnd + 1])
		--minIdxFromEnd;

	if (minIdxFromEnd >= 0)
	{
		int idx = nums.size() - 1;
		while (idx >= 0 && nums[minIdxFromEnd] >= nums[idx])
			--idx;

		swap(nums[minIdxFromEnd], nums[idx]);
	}

	// 特别注意，必须先计算好偏移的下标，否则当 minIdxFromEnd 小于零的时候，迭代器加上负数是非法操作 
	sort(nums.begin() + (minIdxFromEnd + 1), nums.end());
}

int main(int argc, char** argv)
{
	vector<int> nums = { 1,2,3,9,6,11,15,17 };

	cout << "The given array:\n";
	for (int& num : nums) cout << num << ", ";

	NextPermutation(nums);
	cout << "\n\nNext greater permutation array:\n";
	for (int& num : nums) cout << num << ", ";

	cout << endl << endl;
	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 假设一个产品经理，目前正在带领一个团队开发新产品，但不幸的是，产品没有通过质量检测。
 * 优于每个版本都是基于之前的版本开发的，所以从某一个错误的版本之后的所有本吧，都认为是错误的。
 * 
 * 假设有 N 个版本，[1, N]，需要找出导致后续所有版本出错的第一个错误的版本。
 * 
 * 可通过一个 bool IsBadVersion(versionNum) 接口来判断版本号 versionNum 是否在测试中出错，
 * 应该尽可能减少算法API的调用。
 *
 * 【输入】
 * Version N = 5 （从版本4开始是错误版本）
 * 【输出】
 * First Bad Version = 4
 *
 * 【解题思路】
 * 本题可以理解为，在 [1, N] 中，前半部分的版本的测试结果都是正确的，后半部分版本的测试结果都是错误的，
 * 要找到首个错误版本。且假定已经有一个接口 bool IsBadVersion(versionNum) 来判断指定的版本号是否在
 * 测试中出错。
 * 可以使用二分法查找，以减少核心算子执行次数，最开始从数组首尾元素开始，作为边界，计算中间元素，
 * 判断中间元素是否在测试中出错，如果是，则表明首个出错版本在中间元素左侧，反之亦然，然后缩紧计算边界，
 * 重新计算中间元素，直到边界重合，即找到首个测试出错的版本。
 *
 * 【解题分析】
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-22
 **************************************************************************************************/
#include <iostream>
using namespace std;

/**
 * @brief 辅助函数，用以判断当前传入的版本号，是否在测试中错误，为了接近实际业务需求，这里假定版本号大于等于某个
 * 局部常量值，即为错误版本号，其实这个值也是首个错误版本号，但实际业务中对外部是未知的，只是用于模拟。
 * @param versionNum 当前判断的版本号 
 * @return 是否在测试中出错 
 */
bool IsBadVersion(unsigned int versionNum)
{
	return (versionNum >= 4);
}

unsigned int FirstBadVersion(unsigned int maxVersionNum)
{
	unsigned int left = 1;
	unsigned int right = maxVersionNum;
	unsigned int mid = 0;

	while (left < right)
	{
		/**
		 * 求取两数中值时，最好不要使用 (left + right) / 2，因为当left和right
		 * 都大于其类型上限值的一半时，(left + right) 计算结果越界，导致最终结果错误。
		 * 两数中值肯定会大于等于更小的那个数，因为两数中值本质上是平均了两个数的值，
		 * 显然中值必然大于等于更小的那个数，小于等于更大的那个数。
		 * 
		 * 这里假设left更小，所以left和right的中值即为它们的差值除2；
		 * 
		 * 在数学上，可利用 (min + max) / 2，在展开括号后加上 min/2 再减去 min/2，
		 * 可得表达式：min + (max - min) / 2
		 */
		mid = left + (right - left) / 2;

		if (IsBadVersion(mid))
			right = mid; // mid本身就是错误版本，所以不需要加1 
		else
			left = mid + 1;
	}

	// 此时有 left == right，返回哪个都一样 
	return left;
}

int main(int argc, char** argv)
{
	unsigned int maxVersionNum = 6;
	cout << "Max Version Number: " << maxVersionNum;

	cout << "\n\nFirst bad version is: " << FirstBadVersion(maxVersionNum);
	
	cout << endl << endl;
	return 0;
}
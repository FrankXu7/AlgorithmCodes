/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数N，求[0, N]之间每个数的二进制位中数字1的个数，返回一个长度为 N+1 的数组，记录统计的值。
 *
 * 【输入】
 * Input number = 7
 * 【输出】
 * Count Bits Array = [0, 1, 1, 2, 1, 2, 2, 3]
 *
 * 【解题思路】
 * 方法一：
 * 对于一个二进制数来说，如果是奇数，那最低位的数字肯定是1，若是偶数则为0，所以，可以对整数进行迭代对2取余，
 * 取余结果非0即1，统计其中数字1的数量，在对2取余后，最低位已经处理过了，通过除2排除之，直至将整数除至0.
 * 
 * 方法二：
 * 除了可以通过对2取余判断二进制最低位之外，还可以将一个整数和数字1按位&运算，如果最低位是1，则运算结果是1，
 * 否则就是0，统计其中结果是1的次数，和方法一类似，最低位处理完后，通过向右移位操作来排除最低位，直至整数为0.
 * 
 * 方法三：
 * 窗口算法，将数字1，每次左移1位，因为数字1不论左移多少位，整个二进制数中都只包含有一个数字1，
 * 将其与整数按位&运算，所得结果为1，则表示整数对应的二进制位也是数字1，左移是有上限的，对于 int 类型来说，
 * 最多只有32位，所以最多只需要左移32次即可。
 * 
 * 方法四:
 * Brian Kernighan 算法：表达式 N & (N-1) 是将一个整数N的二进制位最后一个0消除。
 * 依据该算法思想，使用 N & (N-1) 作为核心算子，将每次计算结果赋值回整数N，这样每次计算后都能将整数的
 * 二进制数中最低位的数字1消除，直至整数为0.
 * 
 * 方法五：
 * 采用动态规划思想，观察连续自然数二进制规律，可知：一个二进制数N，右移1位，等价于除2，相当于移除了
 * 二进制数N的最低位，此时 N>>1 中数字1的个数，即为二进制数N中数字1的个数，加上被移除的最低位中数字1的个数，
 * 可以看出，二进制数N的数字1的个数，依赖于 (N>>1) 的二进制数中数字1的个数，更大问题的解决方案依赖于
 * 更小问题，答案依赖于问题的规模，可以用动态规划算法求解。
 * 因为 N>>1 的值肯定小于N，而 N>>1 在这之前就已经计算并保存到数组中了，可以直接获取，此时还需要知道
 * 在 N>>1 后排除掉的二进制最低位是1还是0，可以通过对 (N & 1) 来判断奇数与否来确定二进制最低位，
 * 奇数的二进制最低位是1，偶数是0，综上，可建立动态规划算法的状态转移方程：
 * countArr[N] = countArr[N >> 1] + (N & 1);
 * 其中，countArr[N >> 1] 即为 N 在排除二进制最低位后数字1的个数，由之前保存的结果求得，
 * 而 (N & 1) 即为被排除掉的最低位，如果是1，则统计之，否则为0对结果也不会有影响。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(NlogN) 
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(NlogN) 
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(N) 实际上是O(N + M)，M为当前数据类型二进制最大位数，可认为是一个常量值 
 * 空间复杂度：O(1) 
 * 方法四：
 * 时间复杂度：O(NlogN) 
 * 空间复杂度：O(1)
 * 方法五：
 * 时间复杂度：O(N) 
 * 空间复杂度：O(1) 算法本身要求返回数组，所以除了数组本身外，拥有常数的空间复杂度 
 *
 * @author FrankX
 * @date 2021-09-28
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <bitset> // 用于打印二进制数，仅用于测试，算法逻辑不使用 
using namespace std;

vector<int> CountingBits_1(int num)
{
	vector<int> countArr;
	int _num = 0, tempNum = 0, bitsNum = 0;

	while (_num <= num)
	{
		tempNum = _num;
		bitsNum = 0;

		while (tempNum > 0)
		{
			if (tempNum % 2 == 1) ++bitsNum;
			tempNum /= 2;
		}
		countArr.emplace_back(bitsNum);

		++_num;
	}

	return countArr;
}

vector<int> CountingBits_2(int num)
{
	vector<int> countArr;
	int _num = 0, tempNum = 0, bitsNum = 0;

	while (_num <= num)
	{
		tempNum = _num;
		bitsNum = 0;

		while (tempNum > 0)
		{
			if ((tempNum & 1)== 1) ++bitsNum;
			tempNum >>= 1;
		}
		countArr.emplace_back(bitsNum);

		++_num;
	}

	return countArr;
}

vector<int> CountingBits_3(int num)
{
	vector<int> countArr;
	int _num = 0, tempNum = 0, bitsNum = 0;

	while (_num <= num)
	{
		tempNum = _num;
		bitsNum = 0;

		for (int idx = 0; idx < 32; ++idx)
		{
			// 运算符大致优先级：四则运算 > 移位 > 比较 > 按位运算 
			if ((1 << idx & tempNum) >= 1) ++bitsNum;
		}
		countArr.emplace_back(bitsNum);

		++_num;
	}

	return countArr;
}

vector<int> CountingBits_4(int num)
{
	vector<int> countArr;
	int _num = 0, tempNum = 0, bitsNum = 0;

	while (_num <= num)
	{
		tempNum = _num;
		bitsNum = 0;
		
		while (tempNum > 0)
		{
			tempNum &= tempNum - 1;
			++bitsNum;
		}
		countArr.emplace_back(bitsNum);

		++_num;
	}

	return countArr;
}

vector<int> CountingBits_5(int num)
{
	vector<int> countArr(num + 1);
	int tempNum = 0, bitsNum = 0;

	for (int idx = 1; idx <= num; ++idx)
	{
		countArr[idx] = countArr[idx >> 1] + (idx & 1);
	}

	return countArr;
}

int main(int argc, char** argv)
{
	int inputNum = 10;
	cout << "Input number: " << inputNum;
	cout << "\nBinary bits: \n";
	for (int idx = 0; idx <= inputNum; ++idx)
		cout << bitset<4>(idx) << ", ";

	auto arr1 = CountingBits_1(inputNum);
	cout << "\n\n[Solution 1] Counting binary bits array:\n";
	for (auto& num : arr1) cout << num << ", ";

	auto arr2 = CountingBits_2(inputNum);
	cout << "\n\n[Solution 2] Counting binary bits array:\n";
	for (auto& num : arr2) cout << num << ", ";

	auto arr3 = CountingBits_3(inputNum);
	cout << "\n\n[Solution 3] Counting binary bits array:\n";
	for (auto& num : arr3) cout << num << ", ";

	auto arr4 = CountingBits_4(inputNum);
	cout << "\n\n[Solution 4] Counting binary bits array:\n";
	for (auto& num : arr4) cout << num << ", ";

	auto arr5 = CountingBits_5(inputNum);
	cout << "\n\n[Solution 5] Counting binary bits array:\n";
	for (auto& num : arr5) cout << num << ", ";

	cout << endl << endl;
	return 0;
}
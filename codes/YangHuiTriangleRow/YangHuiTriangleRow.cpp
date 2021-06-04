/**************************************************************************************************
 * 【题目描述】
 * 给定一个整数n属于[0, 33]，返回从0开始算起的第n行杨辉三角形。
 * 在数学上，杨辉三角形（也叫帕斯卡三角形）具有如下性质：
 * （1）每行数字左右对称，且从中间开始往两边逐渐减小到1，首尾都是1；
 * （2）从0开始算的第n行满足d=1的等差数列，前n行有 n(n + 1) / 2 个元素；
 * （3）从0开始算第n行有 n + 1 个元素；
 * （4）某个元素必为上一行左右两个元素之和，上一行元素不存在当作0处理，
 *		即row行column列元素为row-1行column-1列和column列元素之和；
 * （5）很有趣的一点：(a + b)^n 的二项展开式系数，即为从0开始算的第n行各元素；
 *
 * 【输入】
 * inputRow=5（行数从0开始算起）
 *
 * 【输出】
 * 1 5 10 10 5 1
 *
 * 【解题思路】
 * 考虑上述第四点性质，可得等式：Data[row][column] = Data[row][column-1] + Data[row-1][column];
 * 更大规模的问题可由有限的更小规模问题得出答案，类似动态规划的思想，大致过程：
 * （1）初始化每行元素，每行元素的个数是已知的；
 * （2）每行的首尾元素可直接赋值为1；
 * （3）遍历每行除首尾的元素，其值为上一行对应下标和前一个小标所在元素之和，
 *		这里因为步骤（2）已经给首尾元素赋值，所以遍历范围为[1, column-1]，这样可以避免边界的判断问题；
 * 
 * 【解题分析】
 * 时间复杂度：O(N^2)
 * 空间复杂度：O(N)，这里的N包含当前行生成的数据，和上一行生成的数据之和，N会随着问题规模，
 *			  即要求的行数的增大而增加。
 * 
 * @author FrankX
 * @date 2021-06-03
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

void PrintVector(vector<int>& vecData);

void YangHuiTriangleRow(unsigned int rowNum)
{
	rowNum = (rowNum > 33) ? 33 : rowNum;

	vector<int> lastRow = { 1 };
	vector<int> curRow;

	// 第0行已经在lastRow初始化过了，直接从第1行开始 
	for (unsigned int row = 1; row <= rowNum; ++row)
	{
		curRow.resize(row + 1);
		curRow[0] = curRow[row] = 1;

		for (unsigned int idx = 1; idx < row; ++idx)
			curRow[idx] = lastRow[idx - 1] + lastRow[idx];
		lastRow.swap(curRow);
	}

	PrintVector(lastRow);
}

/**
 * @brief 打印容器元素，这里其实就是某一行杨辉三角的数据
 * @param vecData 容器数据
 */
void PrintVector(vector<int>& vecData)
{
	cout << "\nPrint the NO." << vecData.size() - 1 << " row (Starting with 0 row) :\n";
	for (vector<int>::iterator itr = vecData.begin(); itr != vecData.end(); ++itr)
		cout << *itr << ", ";
	cout << endl;
}

int main()
{
	unsigned int inputRow = 0;
	cout << "Input the target row between [0, 33]: ";
	cin >> inputRow;

	YangHuiTriangleRow(inputRow);

	return 0;
}

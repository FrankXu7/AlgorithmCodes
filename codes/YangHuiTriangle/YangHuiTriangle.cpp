/**************************************************************************************************
 * 【题目描述】
 * 在数学上，杨辉三角形（也叫帕斯卡三角形）具有如下性质：
 * （1）每行数字左右对称，且从中间开始往两边逐渐减小到1，首尾都是1；
 * （2）从0开始算的第n行满足d=1的等差数列，前n行有 n(n + 1) / 2 个元素；
 * （3）从0开始算第n行有 n + 1 个元素；
 * （4）某个元素必为上一行左右两个元素之和，上一行元素不存在当作0处理，
 *		即row行column列元素为row-1行column-1列和column列元素之和；
 * （5）很有趣的一点：(a + b)^n 的二项展开式系数，即为从0开始算的第n行各元素；
 * 
 * 【输入】
 * inputRow=6
 *
 * 【输出】
 * 1
 * 1 1
 * 1 2 1
 * 1 3 3 1
 * 1 4 6 4 1
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
 * 空间复杂度：O(N^2)
 * 
 * @author FrankX
 * @date 2021-06-01
 **************************************************************************************************/


#include <iostream>
#include <vector>
using namespace std;

void PrintTriangle(vector<vector<int>>& triangle);

void YangHuiTriangle(int numRows)
{
	// 手测int类型最大行数为34
	numRows = (numRows < 1) ? (1) : (numRows > 34 ? 34 : numRows);

	vector<vector<int>> triangle(numRows);

	for (int row = 0; row < numRows; ++row)
	{
		triangle[row].resize(row + 1);
		triangle[row][0] = triangle[row][row] = 1;
		for (int idx = 1; idx < row; ++idx)
		{
			triangle[row][idx] = 
				triangle[row - 1][idx - 1] + triangle[row - 1][idx];
		}
	}

	PrintTriangle(triangle);

	triangle.resize(0);
}

/**
 * @brief 打印杨辉三角形
 * @param triange 为一个双层vector
 */
void PrintTriangle(vector<vector<int>>& triangle)
{
	cout << "\nPrint " << triangle.size() << " rows of YangHui Triangle: \n";
	for (vector<vector<int>>::iterator row = triangle.begin(); row != triangle.end(); ++row)
	{
		for (vector<int>::iterator idx = row->begin(); idx != row->end(); ++idx)
		{
			cout << *idx << ", ";
		}
		cout << endl;
	}
}

int main()
{
	int inputRow = 0;
	cout << "Input rows between [1, 34]: ";
	cin >> inputRow;

	YangHuiTriangle(inputRow);

	return 0;
}

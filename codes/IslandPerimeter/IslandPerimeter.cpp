/**************************************************************************************************
 * 【题目描述】
 * 给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地，grid[i][j] = 0 表示水域。网
 * 格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，
 * 一个或多个表示陆地的格子相连组成的岛屿）。岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。
 * 格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。
 * 
 * 【输入】
 * 网格数据：[ [0,1,0,0], [1,1,1,0], [0,1,0,0], [1,1,0,0] ]
 * 构造的岛屿形状为：
 * 0   1   0   0
 * 1   1   1   0
 * 0   1   0   0
 * 1   1   0   0
 * 【输出】
 * 岛屿面积为：16
 * 
 * 【解题思路】
 * 方法一：
 * 逐一遍历网格，当遇到陆地时，通过下标判断该陆地网格的上下左右位置是否为作为岛屿的边界，比如上方网格是陆
 * 地，自然不会贡献周长，若是海水，则周长加1，需要注意的是，在网格底图边界的网格，其下标的操作可能会越界，
 * 这种情况自然也会贡献周长。
 * 
 * 方法二：
 * 对网格采用DFS遍历，这种方式和方式一在核心算子上比较类似，但不同的是，可以拓展处理网格底图中有多个岛屿时，
 * 统计各个岛屿的周长，而方法一虽然也能统计，但只能统计所有岛屿的总周长，是无法判断有几个岛屿以及它们的周
 * 长。不过题设只有一个岛屿，所以在递归处理的上层，首次遍历到网格而后执行递归调用时，可直接将递归结果返回
 * 即可。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(MN) 每个网格会遍历一次，MN为网格地图长宽的乘积
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(MN) 每个网格会遍历一次，MN为网格地图长宽的乘积
 * 空间复杂度：O(MN) 递归时栈空间开销，最差情况下为O(MN)
 *
 * @author FrankX
 * @date 2021-12-10
 *************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int IslandPerimeter_1(vector<vector<int>>& grids)
{
	unsigned int rowNum = grids.size();
	unsigned int curColNum = 0;

	int perimeter = 0;

	for (unsigned int rowIdx = 0; rowIdx < rowNum; ++rowIdx)
	{
		curColNum = grids[rowIdx].size();

		for (unsigned int colIdx = 0; colIdx < curColNum; ++colIdx)
		{
			if (grids[rowIdx][colIdx] == 0) continue;

			/**
			 * 排除边界情况，主要是简化分支判断条件，满足任意一个条件都需要增加周长，可以同时满足多个，即
			 * 网格存在多条边是边界
			 */
			perimeter += static_cast<int>(rowIdx == 0) + static_cast<int>(rowIdx + 1 >= rowNum) +
				static_cast<int>(colIdx == 0) + static_cast<int>(colIdx + 1 >= curColNum);

			// 检查上下方
			if (rowIdx - 1 < rowNum && grids[rowIdx - 1][colIdx] == 0)
			{
				++perimeter;
			}
			if (rowIdx + 1 < rowNum && grids[rowIdx + 1][colIdx] == 0)
			{
				++perimeter;
			}

			// 检查左右两侧 
			if (colIdx - 1 < curColNum && grids[rowIdx][colIdx - 1] == 0)
			{
				++perimeter;
			}
			if (colIdx + 1 < curColNum && grids[rowIdx][colIdx + 1] == 0)
			{
				++perimeter;
			}
		}
	}

	return perimeter;
}

/**
 * @brief 辅助函数，DFS遍历递归调用，对传入的格子，递归其上下左右的格子
 * @param grids 网格引用
 * @param rowIdx 行坐标
 * @param colIdx 列坐标
 */
int DFS_Recursion(vector<vector<int>>& grids, int rowIdx, int colIdx)
{
	// 遇到越界的格子 
	if (rowIdx < 0 || rowIdx >= static_cast<int>(grids.size()) ||
		colIdx < 0 || colIdx >= static_cast<int>(grids[rowIdx].size()))
	{
		return 1;
	}

	// 遇到海水的格子 
	if (grids[rowIdx][colIdx] == 0)
	{
		return 1;
	}

	// 遇到已经被标记为处理过的格子 
	if (grids[rowIdx][colIdx] == -1)
	{
		return 0;
	}

	// 标记当前的遇到的格子已处理 
	grids[rowIdx][colIdx] = -1;

	// 递归遍历上下左右的格子 
	return DFS_Recursion(grids, rowIdx - 1, colIdx) + DFS_Recursion(grids, rowIdx + 1, colIdx) +
		DFS_Recursion(grids, rowIdx, colIdx - 1) + DFS_Recursion(grids, rowIdx, colIdx + 1);
}

int IslandPerimeter_2(vector<vector<int>>& grids)
{
	int rowNum = grids.size();
	int curColNum = 0;

	for (int rowIdx = 0; rowIdx < rowNum; ++rowNum)
	{
		curColNum = grids[rowIdx].size();

		for (int colIdx = 0; colIdx < curColNum; ++colIdx)
		{
			// 因为题设只有一个岛屿，所以遇到第一个网格是陆地即代表找到了该岛屿，直接返回递归的结果即可
			if (grids[rowIdx][colIdx] == 1)
				return DFS_Recursion(grids, rowIdx, colIdx);
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	vector<vector<int>> grids{ {0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0} };
	cout << "The grids:\n";
	for (auto& row : grids)
	{
		for (auto& num : row)
			cout << num << "\t";
		cout << endl;
	}

	cout << "\n\n[Solutino 1] The grids island perimeter is: " << IslandPerimeter_1(grids);
	cout << "\n\n[Solutino 2] The grids island perimeter is: " << IslandPerimeter_2(grids);

	cout << endl << endl;
	return 0;
}
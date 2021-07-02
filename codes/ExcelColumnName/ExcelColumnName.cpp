/**************************************************************************************************
 * 【题目描述】
 *
 *
 * 【输入】
 *
 * 【输出】
 *
 *
 * 【解题思路】
 *
 *
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

string ExcelColumnName(unsigned int&& colNum)
{
	string colName = "";

	while (colNum > 0)
	{
		--colNum;
		colName.insert(colName.begin(), ((colNum % 26) + 'A'));
		colNum /= 26;
	}

	return colName;
}

int main()
{
	cout << "Excel column name: " << ExcelColumnName(676) << endl;
	return 0;
}

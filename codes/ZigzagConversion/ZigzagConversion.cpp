/**************************************************************************************************
 * 【题目描述】
 * 将一个给定字符串 str 根据给定的行数 rowNum ，按照从上往下、从左到右进行 Z 字形排列。比如输入字符串为：
 * "PAYPALISHIRING" 行数为 3 时，排列如下：
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * 然后，从左往右逐行读取，得到一个新字符串，作为最终结果，示例中返回的字符串为："PAHNAPLSIIGYIR"；
 * 
 * 【输入】
 * str = "PAYPALISHIRING"; rowNum = 4;
 * 【输出】
 * 返回字符串："PINALSIGYAHRPI"
 * 其 Z 字形的排列为：
 * P     I     N
 * A   L S   I G
 * Y A   H R
 * P     I
 * 
 * 【解题思路】
 * 方法一：
 * 按照题意，并不需要打印出这个 Z 字形的排列，所以很直观的会想到逐列处理，用一个字符串数组存储之，以题中
 * 的字符串为例，若 rowNum = 4，则实际在字符串数组中的排列为：
 * P   I   N
 * A L S I G
 * Y A H R
 * P   I
 * 
 * 观察可知，行列从1开始算起，奇数列的每一行都有字符，且赋值顺序为从上往下，偶数列首尾行没有字符，且赋值
 * 顺序为从下往上。得到一个字符串数组，按列存储字符，而后通过逐行扫描该字符串数组，取得每一列字符串当前行
 * 的字符加入到返回字符串中。这里需要注意的是，在偶数列中，除了首尾行没有字符外，中间部分也可能因为字符串
 * 字符数量不够而导致没有字符，分支判断时需要额外处理。
 * 
 * 方法二：
 * 从方法一的时间和空间复杂度，以及算法的逻辑复杂性来看，基本可以不考虑。题意说字符串是按照从上往下、从左
 * 到右进行 Z 字形排列。所以可以从第一行第一列开始，逐行从上往下将扫描的字符添加到按行存储的字符串数组中。
 * 当到达行的边界，则更改方向（改变方向的同时，因为已经处理过一列了，所以改变方向后即从下一列开始处理），
 * 从下往上将扫描的字符添加到按行存储的字符串数组中去。
 * 
 * 方法三：
 * 可以将 Z 字形看作是多个 “对勾” 形的重复，如：
 * P     I     N
 * A   L S   I G
 * Y A   H R
 * P     I
 * 按照 “对勾” 来拆分，然后将只有一个的列合并为一列，合并后首尾字符比为空，故每个部分可分为两列，第一列每
 * 一行都有字符，称为主列，首尾字符为空的第二列则称为次级列，如下所示：
 * P                    I                    N
 * A L                  S I                  G
 * Y A                  H R
 * P                    I
 * 
 * 可以找到如下规律：
 * （1）主列的字符下标间隔为：(2*rowNum - 2)
 * （2）除开首尾行，中间部分的行会包含有次级列字符，对这些行从左往右扫描，每一行的首个次级列字符的下标和
 *      行下标（rowIdx）有关，就是主列字符下标间隔减去行下标：(2*rowNum-2) - rowIdx，在次基础上，后续的
 *      次级字符下标间隔都是(2*rowNum-2) - rowIdx；
 * 
 * 此方法本质上为逐行扫描，通过找到的规律计算每一行的字符下标。具体实现就是外层循环遍历每一行，内层循环以
 * (2*rowNum - 2) 的间隔遍历当前行的字符，对于非首尾行，处理完一个字符后，
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N^2) 实际为O(N + N^2)，首先需要遍历一遍字符串以便按列构造字符串数组，其次还需要逐行扫描
 *            构造最终的字符串，当给定行数和字符串长度接近时，可认为构造最终字符串需要 O^2 的复杂度
 * 空间复杂度：O(N^2) 同理，当给定行数和字符串长度接近时，可认为构造最终字符串需要 O^2 的复杂度
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 方法三：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2022-01-11
 *************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string ZigzagConversion_1(string& str, unsigned int rowNum)
{
	if (str.length() <= rowNum)
		return str;

	string ansStr = "", temp = "";
	unsigned int idx = 0, curRow = 1, curCol = 1, strLen = str.length();
	// 存储每一列的字符串，字符数量不会超过给定的行数 
	vector<string> columns;

	while (idx < str.length())
	{
		// 访问奇数列，每行都有字符，从上往下逐行赋值 
		if ((curCol & 1) == 1)
		{
			curRow = 1;
			while (curRow <= rowNum && idx < strLen)
			{
				temp += str[idx++];
				++curRow;
			}
			columns.emplace_back(temp);
		}
		else // 访问偶数列，首尾行没有字符，从下往上逐行赋值 
		{
			curRow = rowNum;
			while (curRow > 0)
			{
				// 每一列的首尾行和不能填满字符的行，用空格字符填充，不会被添加到返回的字符串 
				if ((curRow == rowNum || curRow == 1) || (idx + curRow - 2 >= strLen))
					temp += ' ';
				else if (idx + curRow - 2 < strLen) // 偶数列字符数量为行的数量减2，反过来赋值 
					temp += str[idx + curRow - 2];

				--curRow;
			}
			columns.emplace_back(temp);
			// 跳过已经赋值的下标段 
			idx += (rowNum - 2);
		}

		temp = "";
		++curCol;
	}

	// 逐行扫描，取每一列字符串当前行的字符加入到返回字符串中 
	for (idx = 0; idx < rowNum; ++idx)
	{
		for (string& s : columns)
		{
			if (idx < s.length() && s[idx] != ' ')
				ansStr += s[idx];
		}
	}

	return ansStr;
}

string ZigzagConversion_2(string& str, unsigned int rowNum)
{
	if (str.length() <= rowNum)
		return str;

	vector<string> rows(rowNum, "");
	unsigned int rowIdx = 0;
	bool bDown = false;

	for (char ch : str)
	{
		rows[rowIdx] += ch;
		if (rowIdx == 0 || rowIdx == rowNum - 1) bDown = !bDown;
		rowIdx += bDown ? 1 : -1;
	}

	string ansStr = "";
	for (string& s : rows)
		ansStr += s;

	return ansStr;
}

string ZigzagConversion_3(string& str, unsigned int rowNum)
{
	string ansStr = "";
	unsigned int repeatNum = 2 * rowNum - 2, strLen = str.length(), maxRowIdx = rowNum - 1;

	for (unsigned int rowIdx = 0; rowIdx < rowNum; ++rowIdx)
	{
		for (unsigned int idx = 0; (rowIdx + idx) < strLen; idx += repeatNum)
		{
			// 主列字符 
			ansStr += str[rowIdx + idx];
			// 非首尾行，为当前行扫描下标 idx 加上次级列字符的下标间隔 (repeatNum - rowIdx) 
			if (rowIdx != 0 && rowIdx != maxRowIdx && idx + repeatNum - rowIdx < strLen)
				ansStr += str[idx + repeatNum - rowIdx];
		}
	}

	return ansStr;
}

int main(int argc, char* argv[])
{
	string str = "PAYPALISHIRING";
	unsigned int rowNum = 13;
	cout << "The given string: " << str 
		<< "\nConvert row number: " << rowNum;

	cout << "\n\n[Solution 1] Convert string: " << ZigzagConversion_1(str, rowNum);

	cout << "\n\n[Solution 2] Convert string: " << ZigzagConversion_2(str, rowNum);

	cout << "\n\n[Solution 3] Convert string: " << ZigzagConversion_3(str, rowNum);

	cout << endl << endl;
	return 0;
}
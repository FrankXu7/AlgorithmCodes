/**************************************************************************************************
 * 【题目描述】
 * 给定一个Excel表格列的名称，返回其相应序号。
 * Excel表格列以A开始作为第1列，到第Z列时，下一列进1位，使用两个字符“AA”，本质上是不包含0的26进制规则。
 *
 * 【输入】
 * Excel 列名称: ZY
 *
 * 【输出】
 * 对应的列序号：701
 *
 * 【解题思路】
 * 最先想到的是按照进制转换的规则，直接求解：按照从低位到高位的的规则，将每一位数字的权值作为进制数字26的幂，
 * 然后每一位数字乘以进制26的对应权值的幂，然后求和。但进一步观察会发现，Excel列序号，不包含数字0，
 * 即没有0这个概念。而一般所说的进制转换计算，即普通的对应进制的四则计算，肯定是包含0这个概念的，
 * 所以为了保证列名是从1开始，即最小列名是‘A’，则需要在当前字符减去字符‘A’后再加上1，
 * 而在代码实现上，拆出这部分一样的逻辑，所以看起来是减1
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-07-05
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

const unsigned int ExcelColumnNumber(const string &colName)
{
	int colNum = 0;

	unsigned int nameLen = colName.size();
	char curCh = '\0';
	unsigned int weightCalc = 0;
	/**
	 * 因为Excel表格列序号从1开始，所以需要保证最小的序号'A'的值为1，
	 * 这里虽然是减1，但用当前遍历字符减去此变量后，相当于在减去‘A’后加1 
	 */
	char start = 'A' - 1;

	for (unsigned int idx = 0; idx < nameLen; ++idx)
	{
		// 等价于 colName[idx] - 'A' + 1，这里+1保证了Excel列名最小从字符‘A’开始
		curCh = (colName[idx] - start);
		weightCalc = static_cast<unsigned int>(pow(26, (nameLen - idx - 1)));
		colNum += (curCh * weightCalc);
	}

	return colNum;
}

int main()
{
	string colName = "ZY";
	cout << colName << " Conversion to column number: " << ExcelColumnNumber(colName) << endl;
	return 0;
}

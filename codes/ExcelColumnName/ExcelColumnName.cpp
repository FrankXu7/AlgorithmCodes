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
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-07-05
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

const unsigned int ExcelColumnName(const string& colName)
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

/**
 * @brief 补充算法，将给定数字转换成Excel表格列名称：因为Excel表格列从1开始算起，以26进制为运算规则，
 * 显而易见的是数字中没有了0的存在，但数字不能没有0这个概念，所以在每次循环的时候，数字需要自减1，
 * 自减1后会出现三种情况：
 * （1）减1后刚刚好能整除，此时直接取字符‘A’，也间接的有了0这个概念；
 * （2）减1后刚好不能整除（比如676，本来刚好整除，减1后就不能整除了），此时相当于从高位接了1为，高位会比
 *		自减之前减少1，低位借位减1后，变成了25，即字符‘Y’；
 * （3）减1后不能被整除，在取余或者除法运算中，运算本身是有0这个概念的存在的，但是Excel表格序号没有，所以
 *		减1后相当于间接加上了0这个概念。
 * @param colNum Excel表格列的序号数字
 * @return 返回Excel表格列的实际名称
 */
string ConversionExcelName(unsigned int& colNum)
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
	string colName = "ZY";
	cout << colName << " Conversion to column number: " << ExcelColumnName(colName) << endl;
	return 0;
}

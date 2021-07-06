/**************************************************************************************************
 * 【题目描述】
 * 给定一个Excel表格列的名称，返回其相应序号。
 * Excel表格列以A开始作为第1列，到第Z列时，下一列进1位，使用两个字符“AA”，本质上是不包含0的26进制规则。
 *
 * 【输入】
 * Excel 列序号: 701
 *
 * 【输出】
 * 对应的列名称：ZY
 *
 * 【解题思路】
 * 因为Excel表格列从1开始算起，以26进制为运算规则，
 * 显而易见的是数字中没有了0的存在，但数字不能没有0这个概念，所以在每次循环的时候，数字需要自减1，
 * 自减1后会出现三种情况：
 * （1）减1后刚刚好能整除，此时直接取字符‘A’，也间接的有了0这个概念；
 * （2）减1后刚好不能整除（比如676，本来刚好整除，减1后就不能整除了），此时相当于从高位借了1位，
 *		高位会比自减之前减少1，低位借位减1后，变成了25，即为字符‘Y’；
 * （3）减1后不能被整除，同（2）类似，在取余或者除法运算中，运算本身是有0这个概念的存在的，
 *		但是Excel表格序号没有，所以减1后相当于间接加上了0这个概念。
 * 或者也可以将字符‘A’看作是0（但是注意Excel序号数字是从1开始的），字符‘Z’是25，在26进制的运算中，
 * 最大单数为25.
 *
 * 【解题分析】
 * 时间复杂度：O(logN) 准确说是log以26为底N的对数
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-07-05
 **************************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

const string ExcelColumnName(int& colNum)
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
	int colNum = 701;
	cout << colNum << " Conversion to column name: " << ExcelColumnName(colNum) << endl;
	return 0;
}

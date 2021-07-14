/**************************************************************************************************
 * 【题目描述】
 * 给定一个在区间[1, 30]的数n，返回外观数列的第n项；
 * 外观数列为一个整数数列，第k+1项是对第k项的描述，如：
 * 第1项：1			首项；
 * 第2项：11		前一项由1个1组成；
 * 第3项：21		前一项由2个1组成；
 * 第4项：1211		前一项由1个2，1个1组成；
 * 第5项：111221	前一项由1个1，1个2，2个1组成；
 * ......
 *
 * 【输入】
 * n=5
 * 【输出】
 * string="111221"
 * 
 * 【解题思路】
 * 从首项开始，逐一生成外观数列的项，直至第n项为止；
 * 需要特别注意的是：遍历完上次记录的字符串后，需要在循环结束后追加上最后一次的生成结果；
 * 
 * 【解题分析】
 * 时间复杂度：O(N^2)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-04-07
 **************************************************************************************************/
#include <iostream>
#include <string>

using namespace std;

string ExteriorArray(unsigned int &n)
{
	string lastStr = "";
	string curStr = "1";
	unsigned int start = 1;

	char curKey = '\0';
	unsigned int keyCount = 0;

	while (start <= n)
	{
		lastStr = curStr;
		curKey = lastStr[0];
		curStr = "";
		keyCount = 0;

		for (unsigned int idx = 0; idx < lastStr.length(); ++idx)
		{
			if (curKey == lastStr[idx])
			{
				++keyCount;
			}
			else
			{
				curStr += (to_string(keyCount) + curKey);
				curKey = lastStr[idx];
				keyCount = 1;
			}
		}
		// 追加遍历最后一次生成的结果
		curStr += (to_string(keyCount) + curKey);

		++start;
	}

	return curStr;
}

int main()
{
	unsigned int n = 1;
	cout << "Input which item [1, 30]: ";
	cin >> n;
	if (n > 30)
		n = 30;
	cout << "No." << n << " Exterior string: " << ExteriorArray(n) << endl;

	return 0;
}

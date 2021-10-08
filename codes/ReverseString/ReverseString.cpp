/**************************************************************************************************
 * 【题目描述】
 * 反转一个字符串，字符串以字符数组的形式给出，要求原地反转，常数级别空间复杂度。
 *
 * 【输入】
 * String Array = ['A','B','C','D','E','F','G']
 * 【输出】
 * After Reverse = ['G','F','E','D','C','B','A']
 * 
 * 【解题思路】
 * 使用双指针，分别指向数组头尾，交换指针指向元素，左右指针向数组中间移动，相遇时算法结束。 
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-10-08
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

void ReverseString(vector<char>& strArr)
{
	char tempCh = '\0';
	auto arrSize = strArr.size();

	for (unsigned int leftIdx = 0, rightIdx = arrSize - 1; (leftIdx < rightIdx); ++leftIdx, --rightIdx)
	{
		tempCh = strArr[leftIdx];
		strArr[leftIdx] = strArr[rightIdx];
		strArr[rightIdx] = tempCh;
	}

}

int main(int argc, char** argv)
{
	vector<char> strArr{ 'A','B', 'C', 'D', 'E', 'F', 'G', 'H'};

	cout << "String befor reverse: \n";
	for (auto& ch : strArr) cout << ch << ", ";

	ReverseString(strArr);

	cout << "\n\nString after reverse: \n";
	for (auto& ch : strArr) cout << ch << ", ";

	cout << endl << endl;
	return 0;
}
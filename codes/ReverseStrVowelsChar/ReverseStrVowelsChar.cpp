/**************************************************************************************************
 * 【题目描述】
 * 反转一个字符串中的元音字母，字符串以字符数组的形式给出。
 *
 * 【输入】
 * String Array = ['L','e','E','t','c','O','d','E']
 * 【输出】
 * After Reverse = ['L','E','O','t','c','E','d','e']
 *
 * 【解题思路】
 * 使用双指针，分别指向数组头尾，循环遍历到双指针都指向元音字母时，交换指向元素，直到左右指针相遇。
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
#include <unordered_set>
using namespace std;

void ReverseStrVowelsChar(vector<char>& strArr)
{
	char tempChar = '\0';
	static unordered_set<char> vowels{ 'A','E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };

	unsigned int leftIdx = 0, rightIdx = strArr.size() - 1;
	unordered_set<char>::const_iterator endItr = vowels.end();

	while (leftIdx < rightIdx)
	{
		while (leftIdx < rightIdx && vowels.find(strArr[leftIdx]) == endItr)
			++leftIdx;
		while (leftIdx < rightIdx && vowels.find(strArr[rightIdx]) == endItr)
			--rightIdx;

		if (leftIdx < rightIdx)
		{
			tempChar = strArr[leftIdx];
			strArr[leftIdx] = strArr[rightIdx];
			strArr[rightIdx] = tempChar;

			++leftIdx;
			--rightIdx;
		}
	}
}

int main(int argc, char* argv[])
{
	vector<char> strArr{ 'L','e','E','t','c','O','d','E', };

	cout << "String before reverse:\n";
	for (auto& ch : strArr) cout << ch << ", ";

	ReverseStrVowelsChar(strArr);

	cout << "\n\nString after reverse:\n";
	for (auto& ch : strArr) cout << ch << ", ";

	return 0;
}
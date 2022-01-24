/**************************************************************************************************
 * 【题目描述】
 * 给定一个只包含字符 '2' ~ '9' 的字符串，再给定一个字符映射表，就是九宫格手机按键，其映射关系如下：
 * 
 *           2: abc    3: def
 * 4: ghi    5: jkl    6: mno
 * 7: pqrs   8: tuv    9: wxyz
 * 
 * 输出给定字符串在上述字符映射表中所有的组合，可按任意顺序返回。
 * 
 * 【输入】
 * digits = "23";
 * 【输出】
 * combinations = ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"];
 * 
 * 【解题思路】
 * 利用回溯递归的思路，在递归过程中，维护一个字符串 combineStr，它是当前处理的组合字符串，同时也维护一个
 * 下标作为传入的字符串 digits 的下标，在递归过程中，用当前下标 idx 指向的 digits 中的字符，找到对应的映
 * 射字符串，遍历字符串，将遍历的字符加入组合字符串 combineStr，因为 digits 中每个字符映射到组合中也是一
 * 个字符，故 combineStr 长度和 digits 长度一样时，即代表递归触底，此时 combineStr 为一个完整的组合结果，
 * 推入到总的返回结果中（即字符串数组 letters），否则就将传入的 idx 在加 1 后继续递归处理，这里整体的思路
 * 类似于按层次深度遍历所有路径。上述步骤处理完后，必然已经得到以当前 combineStr 为前缀的所有字符串组合，
 * 故弹出 combineStr 的尾字符，回溯到上一层的状态。
 * 
 * 【解题分析】
 * 时间复杂度：O(3^M + 4^N) 对于九宫格手机按键，按一定顺序输入两个按键后，总的组合数量即为这两个按键映射
 *                          的字符数量的乘积，因为字符映射有3个字符和4个字符之分，故复杂度公式中，M表示3
 *                          个字符的映射字母数量，N表示4个字符的映射字母数量
 * 空间复杂度：O(3^M + 4^N) 和时间复杂度中的 M，N 含义一样，除了返回的数据所需空间外，空间复杂度主要取决
 *                          于递归的层数，映射表是已知的，空间复杂度可看作常数
 *
 * @author FrankX
 * @date 2021-01-24
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<char, string> phoneNumbers = {
	{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
	{'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
};

void TraceBackRecursion(vector<string>& letters, string digits, unsigned int idx, string combineStr)
{
	string letterStr = phoneNumbers[digits[idx]];
	for (char ch : letterStr)
	{
		combineStr.push_back(ch);

		if (combineStr.length() == digits.length())
			letters.emplace_back(combineStr);
		else
			TraceBackRecursion(letters, digits, idx + 1, combineStr);

		// 执行到此，必然已经处理完推入 ch 后，再在其后的字符，弹出 ch，即达到回溯目的 
		combineStr.pop_back();
	}
}

vector<string> CombinePhoneNumberLetter(string digits)
{
	if (digits.empty()) return {};

	vector<string> letters;
	string combineStr = "";
	TraceBackRecursion(letters, digits, 0, combineStr);

	return letters;
}

int main(int argc, char** argv)
{
	string digits = "59";
	cout << "The given digits: " << digits;

	vector<string> letters = CombinePhoneNumberLetter(digits);
	cout << "\n\nThe combine letters: \n";
	for (auto& str : letters) cout << str << ", ";

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 * 给定一个数字 num 代表圆括号的对数，找到所有有效的括号组合，返回所有的组合序列。
 *
 * 【输入】
 * num = 3;
 * 【输出】
 * parentheses = ["((()))", "(()())", "(())()", "()(())", "()()()"];
 *
 * 【解题思路】
 * 方法一：
 * 暴力破解，圆括号左右字符 '(' 和 ')' 分别有 num 个，需要构成一个长度为 num*2 的字符串序列，列出所有可
 * 能的字符串序列，并一一判断它们是否为有效的括号组合。
 *
 * 可用递归之法列出所有的组合，维护一个当前的括号组合字符串引用 curStr，对长度达到 num*2 的 curStr 进一
 * 步判断是否为有效的括号组合，是的话存储到返回序列，然后返回本次递归调用。否则，优先将 '(' 加入到 curStr
 * 后紧接着继续递归，当递归返回时表示处理完一个括号组合了，此时需要弹出 curStr 的末尾字符。然后，按将 ')'
 * 按照前述逻辑来一次。
 *
 * 对于有效组合的判断，可以使用一个整型变量 balance 统计字符串中圆括号字符的平衡性，遍历 curStr，遍历字
 * 符为 '(' 则 balance 自加，反之则自减。有效的组合都是以左括号开头的，故每次计算后如果 balance<0 表示组
 * 合众出现了右括号开头的情况，必然不是有效的。当遍历结束时，balance 的值等于零即代表时有效的组合，其大于
 * 零的情况表示左括号数量大于右括号，显然也不是有效的组合。
 *
 * 方法二：
 * 对暴力法进行优化，将 '(' 或 ')' 添加到 curStr 时，只在仍然保持括号组合有效的情况下添加。在一个有效的
 * 括号组合中，左右括号字符的数量一定是相等的。所以在递归回溯的过程中，可以维护 curStr 字符串中左右括号字
 * 符的数量 left 和 right，有一个客观事实是，如果以左括号字符开头，当 curStr 长度达到 num*2 且其中的左
 * 右括号字符数量都相等的情况下，那当前的括号组合 curStr 肯定是有效的。
 *
 * 在递归调用中，承接方法一的逻辑，只不过在添加左括号字符时，left<num 必须成立才执行添加，同理，紧接着在
 * 添加右括号字符时，必须满足 right<left 才添加。
 *
 * 对于有效性判断，因为初始递归调用从 '(' 字符开始处理，故不会出现以右括号字符开头的情况，同时，两个分支
 * 的判断也保证了 curStr 长度达到 num*2 时左右括号字符数量相等，则此时 curStr 必为有效的括号组合。
 *
 * 方法三：
 * 对于任何一个有效的括号组合，都可以看做是字符串 '(' + leftStr + ')' + rightStr 构成的，其中的leftStr
 * 和 rightStr 都分别是一个有效的括号组合（可以为空），且 leftStr 和 rightStr 中的括号的对数等于 num-1，
 * 通过枚举 leftStr 和 rightStr 对应的所有情况，就可以用已求得的比 num 对数更少的有效括号组合的数量，来
 * 构造括号的对数为 num 时的有效组合数量。其中，假设 leftStr 中的括号的对数为 idx 时，对应 rightStr 中
 * 的括号对数就是：num - idx - 1，综上，更大规模的问题可由更小规模问题解决，可以用动态规划的方法解题。
 * 
 * 构建状态转移方程，假设括号的对数为 num 时的所有有效组合的集合表示为 S[num]，则：
 * S[num] = { '(' + leftStr + ')' + rightStr | leftStr 为枚举 [0, num-1] 时的所有有效括号组合的数量，
 * 对应的，rightStr 为枚举 [num-idx-1, num-1] 时的所有有效括号组合的数量 }
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N * 2^2N) 总共有 2^2N 个括号组合，每个组合需要 O(N) 来判断是否有效
 * 空间复杂度：O(2N) 如果每一层递归的视作O(1)，那么复杂度为 O(2N)
 * 方法二：
 * 时间复杂度：O((4^N) / √N) 依据第 N 个 “卡特兰数” (1 / (N+1))(2N N) 得到
 * 空间复杂度：O(2N) 如果每一层递归的视作O(1)，那么复杂度为 O(2N)
 * 方法三：
 * 时间复杂度：O(N^2 * 2^N) 外层两层循环可以确定每层的循环上限最差的情况和 num 的值相等，在内层循环中，
 *                         还有两个嵌套的for循环用以生成当前括号的对数 curNum 的所有有效的括号组合，这两
 *                         个循环的复杂度在 [2^N, 3^N] 的区间内，更加靠近2^N，且随着N越大，会远小于3^N
 * 空间复杂度：O((4^N) / √N) 与方法二的时间复杂度类似，不包含返回序列所需的空间
 *
 * @author FrankX
 * @date 2021-01-26
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * @brief 辅助函数，判断一个字符串中的圆括号是否配对
 * @param str
 * @return 返回是否配对的bool值
 */
bool DetermineMatch(string& str)
{
	/**
	 * 左右括号是否配对平衡，每匹配到一个左括号，自加，反之则自减。所以在循环内，balance 的值肯定大于等于
	 * 0，如果出现 balance < 0，即代表首先出现了右括号，或出现了非圆括号字符，所以不可能会配对；而执行完
	 * 循环后，只有当 balace = 0 成立时才表示整个字符串中圆括号配对。
	 */
	int balance = 0;
	for (char ch : str)
	{
		if (ch == '(') ++balance;
		else --balance;

		if (balance < 0) return false;
	}

	return (balance == 0);
}

void Recursion_DFS_1(vector<string>& parentheses, string& curStr, unsigned int num)
{
	if (curStr.length() == num) // 深度遍历触底 
	{
		if (DetermineMatch(curStr))
			parentheses.emplace_back(curStr);
		return;
	}

	curStr.push_back('(');
	Recursion_DFS_1(parentheses, curStr, num);
	curStr.pop_back();

	curStr.push_back(')');
	Recursion_DFS_1(parentheses, curStr, num);
	curStr.pop_back();
}
vector<string> GenerateParentheses_1(unsigned int num)
{
	vector<string> parentheses;
	string curStr = "";

	Recursion_DFS_1(parentheses, curStr, num * 2);

	return parentheses;
}

void Recursion_DFS_2(vector<string>& parentheses, string& curStr,
	unsigned int left, unsigned int right, unsigned int num)
{
	if (curStr.length() == num * 2)
	{
		parentheses.emplace_back(curStr);
		return;
	}

	if (left < num)
	{
		curStr.push_back('(');
		Recursion_DFS_2(parentheses, curStr, left + 1, right, num);
		curStr.pop_back();
	}

	if (right < left)
	{
		curStr.push_back(')');
		Recursion_DFS_2(parentheses, curStr, left, right + 1, num);
		curStr.pop_back();
	}
}
vector<string> GenerateParentheses_2(unsigned int num)
{
	vector<string> parentheses;
	string curStr = "";
	int left = 0, right = 0;

	Recursion_DFS_2(parentheses, curStr, left, right, num);

	return parentheses;
}

vector<string> GenerateParentheses_3(unsigned int num)
{
	static vector<vector<string>> parentheses = { { "" }, { "()" } };
	if (num < parentheses.size())
		return parentheses[num];

	vector<string> curArr;
	// 计算括号的对数为 curNum 时的所有有效括号组合 
	unsigned int curNum = 1;
	// 动态规划初始已经有两个结果，从括号对数等于2时开始处理（括号的对数等于零也是一种情况） 
	while (++curNum <= num)
	{
		/**
		 * 枚举出 '(' + leftStr + ')' + rightStr 中左右字符串中括号对数分别为 idx 和 curNum-idx-1 时的所
		 * 有有效括号组合
		 */
		for (unsigned int idx = 0; idx < curNum; ++idx)
		{
			// 从之前已经求出的结果中直接取得所有有效组合 
			vector<string>& lefts = parentheses[idx];
			vector<string>& rights = parentheses[curNum - idx - 1];

			for (string& leftStr : lefts)
				for (string& rightStr : rights)
					curArr.emplace_back('(' + leftStr + ')' + rightStr);
		}
		
		parentheses.emplace_back(curArr);
		curArr.clear();
	}

	return parentheses[num];
}

int main(int argc, char* argv[])
{
	unsigned int num = 3;
	cout << "The parenthese number: " << num;

	vector<string> parentheses1 = GenerateParentheses_1(num);
	cout << "\n\n[Solution 1] Generate parentheses:\n";
	for (string& str : parentheses1) cout << str << ", ";

	vector<string> parentheses2 = GenerateParentheses_2(num);
	cout << "\n\n[Solution 2] Generate parentheses:\n";
	for (string& str : parentheses2) cout << str << ", ";

	vector<string> parentheses3 = GenerateParentheses_3(num);
	cout << "\n\n[Solution 3] Generate parentheses:\n";
	for (string& str : parentheses3) cout << str << ", ";

	cout << endl << endl;
	return 0;
}
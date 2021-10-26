/**************************************************************************************************
 * 【题目描述】
 * 给定一个字符串 s 和 t，判断 s 是否 为 t 的子序列。
 * 这里的子序列 s 不一定是 t 中一段连续字符，比如 "ace" 是 "abcde" 的一个子序列。
 *
 * 假定两个字符串都由小写字母组成
 *
 * 考虑超大规模（>=10亿） s 的输入量要对超大量的 s 输入序列依次检查是否为 t 的子序列，需要如何改进？
 *
 * 【输入】
 * s="ace"; t="abcde";
 * 【输出】
 * TRUE
 *
 * 【解题思路】
 * 方法一：
 * 双指针法，两个指针初始分别指向两个字符串首字符，如果指向的字符相同，则指针都向右移一位，否则只将
 * 指向字符串 t 的指针右移一位，当任意一个字符串遍历完成时匹配截止。
 * 此时指向字符串 s 的指针如果指完了，就代表 s 是 t 的子序列，否则代表 s 中还有字符未完成匹配。
 *
 * 此方法不限于题中所说的小写字母。
 *
 *
 * 方法二：
 * 假如字符串 t 很久才有变化，当输入非常多不同的 s 时，需要依次检查它们是否为 t 的子序列，
 * 这样会重复对 t 进行很多次遍历。可以牺牲一定的空间复杂度，记录字符串 t 中各个字符的位置信息，
 * 然后采用二分法来处理。初始时需要构建字符串 t 中字符的位置关系，可利用一个无序map，以 t 中各个字符
 * 作为key，对应的值为该字符在字符串中的下标数组，因为是遍历记录的，故数组中的下标是升序的。
 * 在遍历字符串 s 之前，需要记录下一次的搜索下标 searchIdx，即为在字符串 t 中匹配到的下标+1，然后
 * 遍历字符串 s，找到遍历字符对应在map下标数组中第一个比 searchIdx 大的下标，利用二分法查找有序序列元素。
 *
 * 此方法不限于题中所说的小写字母。
 *
 *
 * 方法三：
 * 假设在遍历 t 的过程中，当遍历到一个字符时，就能知道其后续所有字符首次出现的下标，在此情况下遍历 s 时，
 * 就可以进行跳跃式的遍历了。比如：遍历到 t[0] 时，可知此时 s[0] 对应的字符在 t 中首次出现的下标是5，
 * 那么下次遍历就直接从 t[5+1] 开始，跳过了中间部分不需要处理的元素，从而提升效率，这种方式对超大量输入的
 * s 字符串效率很高。因为遍历到 t 中某个字符 t[searchIdx] 时，能知道从searchIdx之后所有 t 中字符的下标位置，
 * 所以searchIdx值越小就知道 t 中字符下标信息越多，可以理解为规模越大，故此时小规模问题到大规模问题在 t 中是
 * 从后往前开始的，是一个倒过来动态规划的过程。
 *
 * 动态规划首先要建立状态转移方程，规定 f[searchIdx][ch] 是 t 中从searchIdx开始往后，字符ch首次出现的位置，
 * 如果 f[searchIdx][ch] 所表示的下标位置无意义的话，那ch的位置信息就可能在 f[searchIdx + 1][ch] 中出现；
 * 故有状态转移方程：
 *
 * f[searchIdx][ch] == searchIdx               ①
 * f[searchIdx][ch] == f[searchIdx + 1][ch]    ②
 *
 * 注解：等式 ① 即表示 t 中sercharIdx所在位置的字符就是ch；等式 ② 则表示 t 中sercharIdx所在位置字符不是ch，
 * 那ch首次出现的位置必然在 searchIdx + 1 之后；
 *
 * 大致过程：t 从后往前开始，遍历的 searchIdx 对应一个长度为26的数组映射26个小写字母，表示从 searchIdx 开始，
 * 后面的每个字符在 t 中首次出现的位置，因为是从后往前遍历的，所以只需要设置 t[searchIdx] 的位置， 其余字符
 * 位置直接用 t[searchIdx + 1] 对应的值设置即可，对于不存在的字符的下标，默认以 t 的长度作为值，经过动态规划
 * 后可创建一个二维数组 idxArr，长度为 t 的长度+1（+1是为了建立最初时最小规模的问题，后续规模更大的问题就是
 * 基于这个最小问题开始求解的），每个元素对应一个26元素的数组映射26个小写字母在 t 中的位置信息。在动态规划
 * 创建好 t 的字符位置关系后，就可以开始遍历 s 了，如果当前遍历到 s 中的字符，在 idxArr 存在有意义的下标位置，
 * 则下次遍历可以直接从该下标位置+1处开始跳跃式遍历，当遇到在 idxArr 中的下标位置无意义时，表示从此时的
 * 搜索下标开始，s 对应的字符在 t 中已经不存在首次出现的位置了，即在 t 中该字符不存在，判定为非子序列。
 * 
 * 此方法按题意，仅限于小写字母。
 *
 *
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(logN) 在 t 不改变的情况下，只需要构建一次 t 中各字符的关系，每次改变 t 复杂度为O(N+logN)
 * 空间复杂度：O(N) 最差的情况是字符串 t 中没有重复字符
 * 方法三：
 * 时间复杂度：O(M) 其中M为 s 的长度，首次时需要通过动态规划复杂度为O(N)，故首次的复杂度为最差情况O(M+N)
 * 空间复杂度：O(N) 实际为O(N*26)，N为 t 的长度，二维数组每个元素对应一个长度为26的数组映射26个小写字母
 *
 * @author FrankX
 * @date 2021-10-26
 **************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool IsSubString_1(string& s, string& t)
{
	unsigned int sizeS = s.length();
	unsigned int sizeT = t.length();

	unsigned int idxS = 0;
	unsigned int idxT = 0;
	while (idxS < sizeS && idxT < sizeT)
	{
		if (s[idxS] == t[idxT])
		{
			++idxS;
		}

		++idxT;
	}

	return (idxS >= sizeS);
}

bool IsSubString_2(string& s, string& t, bool rebuildMap = true)
{
	static unordered_map<char, vector<unsigned int>> chMap;
	// 按需构建字符串 t 中字符下标映射关系 
	if (rebuildMap)
	{
		unsigned int sizeT = t.length();
		for (unsigned int idx = 0; idx < sizeT; ++idx)
			chMap[t[idx]].emplace_back(idx);
	}

	decltype(chMap)::iterator endItr = chMap.end();
	unsigned int searchIdx = 0, leftIdx = 0, rightIdx = 0, midIdx = 0;
	for (auto& ch : s)
	{
		if (chMap.find(ch) == endItr)
			continue;

		auto& idxArr = chMap[ch];
		leftIdx = 0;
		rightIdx = chMap[ch].size() - 1;

		// 下标数组按升序推入，搜索下标大于数组中最大下标，必为非子字符串 
		if (searchIdx > idxArr[rightIdx])
			return false;

		while (leftIdx < rightIdx)
		{
			midIdx = leftIdx + (rightIdx - leftIdx) / 2;

			if (idxArr[midIdx] < searchIdx)
				leftIdx = midIdx + 1;
			else
				// midIdx不需要减1以免漏掉相等的情况 
				rightIdx = midIdx;
		}

		// idxArr[leftIdx] 为当前已经比较过的字符，下一次自然要从+1处开始 
		searchIdx = idxArr[leftIdx] + 1;
	}

	return true;
}

bool IsSubString_3(string& s, string& t, bool rebuildMap = true)
{
	unsigned int sizeT = t.length();
	using T = vector<unsigned int>;
	// 元素值初始化为 t 的长度，表示该值所对应的下标是无意义的 
	static vector<T> idxArr(sizeT + 1, T(26, sizeT));

	// 按需动态规划 
	if (rebuildMap)
	{
		for (unsigned int chIdx = sizeT - 1; chIdx < sizeT; --chIdx)
		{
			for (unsigned int letterIdx = 0; letterIdx < 26; ++letterIdx)
			{
				if (t[chIdx] == letterIdx + 'a')
					// t 中chIdx对应字符为当前遍历到的字母，记录其下标位置 
					idxArr[chIdx][letterIdx] = chIdx;
				else
					// 否则沿用 chIdx + 1 的值，每个 chIdx 都沿用了后续的值（倒过来的动态规划） 
					idxArr[chIdx][letterIdx] = idxArr[chIdx + 1][letterIdx];
			}
		}
	}

	unsigned int searchIdx = 0;
	for (auto& ch : s)
	{
		// 此分支表示从searchIdx开始，后面就不存在当前遍历的字符了 
		if (idxArr[searchIdx][ch - 'a'] == sizeT)
			return false;

		// idxArr[searchIdx][ch - 'a'] 是在 t 中匹配到相同字符的下标，下次从下标+1开始 
		searchIdx = idxArr[searchIdx][ch - 'a'] + 1;
	}

	return true;
}

int main(int argc, char** argv)
{
	string s = "beede";
	string t = "dfbeadce";

	cout << "The handle string: " << s
		<< "\nThe Search string: " << t;

	cout << "\n\n[Solution 1] Is a sub string: " << (IsSubString_1(s, t) ? "YES" : "NO");

	cout << "\n\n[Solution 2] Is a sub string: " << (IsSubString_2(s, t) ? "YES" : "NO");

	cout << "\n\n[Solution 3] Is a sub string: " << (IsSubString_3(s, t) ? "YES" : "NO");

	cout << endl << endl;
	return 0;
}
/**************************************************************************************************
 * 【题目描述】
 *
 *
 * 【输入】
 *
 * 【输出】
 *
 *
 * 【解题思路】
 *
 *
 *
 * 【解题分析】
 * 时间复杂度：
 * 空间复杂度：
 *
 * @author FrankX
 * @date 2021-
 **************************************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

void CountPrimeNumber_1(vector<unsigned int>& primeVec, const unsigned int targetNum)
{
	if (targetNum <= 1)
		return; // 质数大于1（0和1即不是质数也不是合数） 
	else if (targetNum >= 2)
		primeVec.emplace_back(2); // 2是质数中唯一的偶数 

	unsigned int divNum = 0;
	
	// 除了2以外，只有奇数才可能是质数，故而 += 2 排除偶数
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		// 以平方根为界，如果在左侧有因数，则另一个因数必在右侧，所以只需要判断到平方根就可以
		unsigned int cycleNum = static_cast<unsigned int>(sqrt(num));
		divNum = 3;

		// 因为 num 必为奇数，所以除数不可能是偶数，故而 += 2 排除偶数 
		for (; divNum <= cycleNum; divNum += 2)
		{
			if (num % divNum == 0)
				break;
		}

		if (divNum > cycleNum)
			primeVec.emplace_back(num);
	}
}

void CountPrimeNumber_2(vector<unsigned int>& primeVec, const unsigned int targetNum)
{
	if (targetNum <= 1)
		return; // 质数大于1（0和1即不是质数也不是合数） 
	else if (targetNum >= 2)
		primeVec.emplace_back(2); // 2是质数中唯一的偶数 

	// 排除了偶数的话其实有一半的空间是用不到的，但是有需要进行下标计算，目前没想到好办法 
	vector<bool> judgeVec(targetNum, true);
	
	// 大于2的偶数必定是合数，通过 += 2 排除偶数 
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		if (judgeVec[num] == false) continue;
		
		primeVec.emplace_back(num);
		// 若 num 是质数，则 num 的 N(N >= 2) 倍必定是合数，通过 += num 标记合数 
		for (unsigned int idx = num * num; idx < targetNum; idx += num)
			judgeVec[idx] = false;
	}
}

int main()
{
	unsigned int primeLimit = 100;

	vector<unsigned int> primeGather;
	CountPrimeNumber_1(primeGather, primeLimit);

	cout << "[Solution 1] The prime numbers under " << primeLimit
		<< "（" << primeGather.size() << "）： \n\n";
	for (unsigned int idx = 0; idx < primeGather.size(); ++idx)
	{
		cout << primeGather[idx] << ",\t";
		if (idx + 1 >= 15 && (idx + 1) % 15 == 0) cout << endl;
	}

	vector<unsigned int>().swap(primeGather);
	CountPrimeNumber_2(primeGather, primeLimit);
	cout << "\n\n[Solution 2] The prime numbers under " << primeLimit
		<< "（" << primeGather.size() << "）：\n\n";
	for (unsigned int idx = 0; idx < primeGather.size(); ++idx)
	{
		cout << primeGather[idx] << ",\t";
		if (idx + 1 >= 15 && (idx + 1) % 15 == 0) cout << endl;
	}

	cout << endl;
	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 统计所有小于正整数N的质数的数量。
 * 质数特性：
 * （1）一个数只能被1和自身整除的数，称为质数（素数），否则为合数，0和1既不是质数也不是合数；
 * （2）偶数中，只有2才是质数；
 *
 * 【输入】
 * N = 203898
 * 【输出】
 * Prime numbers count = 18294
 *
 * 【解题思路】
 * 方法一:
 * 最先最直观想到的，就是遍历N以内的正整数了，然后对每一个正整数，遍历小于它的正整数，依次作整除的判断，统计之。
 * 想想就明白时间复杂度会很高，但通过质数的性质可知，0和1既不是质数也不是合数，所以可以直接从2开始遍历，
 * 又因为所有偶数中，只有2才是质数，所以可以从3开始遍历，遍历步长为2，排除所有偶数，提升效率。
 * 但还有改进空间，排除偶数后，还是会遍历到接近N的数，但仔细想想，两个正整数 a,b，如果满足 a*b=N，
 * 则必有以 sqrt(N) 为界，a,b 一大一小，分别位于 sqrt(N) 左右两侧，如果存在正整数 a,b 满足 a*b=N，
 * 只需要从小到大遍历到 sqrt(N) 即可，若存在因数，则另一个因数必大于等于 sqrt(N)。
 *
 * 方法二：
 * 可采用埃氏筛（埃拉托斯特尼筛法），如果一个数 NUM，被判断为是一个质数，显然，NUM 的 N(N>=2) 倍，
 * 必为一个合数。所以，可以用一个数组，以其下标作为操作数，当某一个下标所表示的数值被判断为是一个质数，
 * 可用该下标对应的数组元素值标记之，同时，可标记下标 NUM 后续 N(N>=2) 倍的所有下标，它们必然是合数。
 * 根据质数性质，除了2以外，所有的质数必为奇数，所以其实不需要处理下标为偶数的元素，但因为下标本身就是操作数，
 * 相当于数组有一半的空间是空闲的。
 * 这里标记的遍历可以进一步优化，若一个数值 NUM 被判断为质数，不必从NUM*2 开始标记数组元素为合数，
 * 因为它们肯定被 NUM 之前的质数标记过了，直接从 NUM*NUM 开始标记，遍历的每次步长为 NUM，
 * 依次标记对应下标数值为合数。
 * 最后，仔细考虑，每次的步长 NUM 会有什么效果，比如质数3，从 3*3 开始标记，步长即为3，则下一个处理的数是 9+3=12，
 * 显然，这是一个偶数，因为开头就排除了偶数2，所以剩余偶数中不可能存在质数了，这样就是冗余处理了，可再进一步优化，
 * 将步长设定为 NUM*2，因为 NUM 必然是一个奇数，而 NUM*2 必然是一个偶数，所以它们的和，也必然是奇数，这样就不会
 * 冗余的去处理偶数了。
 *
 * 方法三：
 * 线性筛（欧拉筛），在埃氏筛中，即使从 NUM*NUM 开始标记，仍会存在重复标记，比如45，当遍历到3时，会从 3*3 开始标记，
 * 故 3*15 会被标记为合数，再遍历到5，会从 5*5 开始标记，会将已经标记为合数的45会被 5*9 重复标记一次。
 * 合数有一个性质：任何合数都能分解为唯一一组多个质数的乘积。而线性筛的核心思想就是保证每个被筛选掉的合数，
 * 必定是被其最小质因数筛选掉的，此时中止继续筛选，就可以避免被重复标记了。所以，当遍历到某个 num 时，
 * 只需要将质数容器中的元素与 num 相乘，乘积必定为合数，标记之。而如果 num 是合数，则在质数容器中
 * 必定存在唯一一组质数的乘积等于 num，因为质数是按升序加入容器的，所以容器内的元素一定小于等于 num，此时，
 * 如果找到了第一个能够被 num 整除的质数，那么，这个质数就是 num 的最小质因数。在这里中止掉后续的筛选，避免重复标记。
 * 
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N√N) 虽然复杂度高于埃氏筛和线性筛，但实际执行时间会远小于另外两种算法
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(Nlog(logN))
 * 空间复杂度：O(N) 因为排除掉了偶数，实际上只有O(N/2)的空间有用到
 * 方法三：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 *
 * @author FrankX
 * @date 2021-08-26
 **************************************************************************************************/
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

void CountPrimeNumber_1(vector<unsigned int>& primeVec, const unsigned int& targetNum)
{
	// 质数大于1（0和1即不是质数也不是合数）
	if (targetNum <= 1) return;

	// 2是质数中唯一的偶数 
	primeVec.emplace_back(2);

	// 作为除数判断当前数值的因数 
	unsigned int divNum = 0;

	// 除了2以外，只有奇数才可能是质数，故而 += 2 排除偶数
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		// 以平方根为界，如果在左侧有因数，则另一个因数必在右侧，所以只需要判断到平方根就可以
		unsigned int cycleNum = static_cast<unsigned int>(sqrt(num));
		divNum = 3;

		// 因为 num 必为奇数，所以除数 divNum 不可能是偶数，故而 += 2 排除偶数 
		for (; divNum <= cycleNum; divNum += 2)
		{
			if (num % divNum == 0)
				break;
		}

		if (divNum > cycleNum)
			primeVec.emplace_back(num);
	}
}

void CountPrimeNumber_2(vector<unsigned int>& primeVec, const unsigned int& targetNum)
{
	// 质数大于1（0和1即不是质数也不是合数）
	if (targetNum <= 1) return;

	// 2是质数中唯一的偶数 
	primeVec.emplace_back(2);

	// 排除了偶数的话其实有一半的空间是用不到的，但是又需要进行下标计算 
	vector<bool> judgeVec(targetNum, true);
	// 提升容量，检测无符号数越界 
	unsigned long long int borderNum = 0;
	// 因为奇数的 N(N>=2) 倍包含偶数，所以步长是当前质数的两倍，奇偶之和必为奇 
	unsigned int stepNum = 0;

	// 大于2的偶数必定是合数，通过 += 2 排除偶数 
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		if (judgeVec[num] == false) continue;

		primeVec.emplace_back(num);

		borderNum = static_cast<unsigned long long int>(num) * num;
		if (borderNum >= targetNum) continue;

		/**
		 * 若 num 是质数，则 num 的 N(N >= 2) 倍必定是合数，通过 += num 标记合数
		 * 从 num * 2 开始会有冗余的设置操作，故而从 num * num 开始处理
		 */
		stepNum = num * 2;
		for (unsigned int idx = static_cast<unsigned int>(borderNum); idx < targetNum; idx += stepNum)
		{
			judgeVec[idx] = false;
		}
	}
}

void CountPrimeNumber_3(vector<unsigned int>& primeVec, const unsigned int& targetNum)
{
	// 质数大于1（0和1即不是质数也不是合数）
	if (targetNum <= 1) return;

	// 排除了偶数的话其实有一半的空间是用不到的，但是又需要进行下标计算 
	vector<bool> judgeVec(targetNum, true);
	// 提升容量，检测无符号数越界 
	unsigned long long int borderNum = 0;
	unsigned int primeCount = 0;

	// 大于2的偶数必定是合数，通过 += 2 排除偶数 
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		if (judgeVec[num])
			primeVec.emplace_back(num);

		primeCount = primeVec.size();
		for (unsigned int idx = 0; idx < primeCount; ++idx)
		{
			borderNum = static_cast<unsigned long long int>(num) * primeVec[idx];
			if (borderNum >= targetNum) break;

			// 两数乘积必然为合数，标记之 
			judgeVec[static_cast<unsigned int>(borderNum)] = false;

			// primeVec 按从小到大顺序加入元素，所以能整除时，当前的质数必定为 num 的最小质因数 
			if (num % primeVec[idx] == 0) break;
		}
	}

	/**
	 * 2是质数中唯一的偶数；
	 * 因为算法逻辑中，质数容器每一个元素会参与计算，
	 * 而2作为偶数，与任何大于1的正整数乘积都是合数，
	 * 所以需要在算法主体逻辑完成后，再加入到质数容器
	 */
	primeVec.emplace_back(2);
}

int main()
{
	time_point<system_clock> end;
	time_point<system_clock> start;

	unsigned int primeLimit = 203'898;
	vector<unsigned int> primeGather1, primeGather2, primeGather3;

	start = system_clock::now();

	CountPrimeNumber_1(primeGather1, primeLimit);
	cout << "[Solution 1] The prime numbers under " << primeLimit
		<< "（" << primeGather1.size() << "）";

	end = system_clock::now();
	cout << "\n[Solution 1] Execute time: " << duration_cast<milliseconds>(end - start).count() << " ms  O(N√N)";
	start = end;

	CountPrimeNumber_2(primeGather2, primeLimit);
	cout << "\n\n[Solution 2] The prime numbers under " << primeLimit
		<< "（" << primeGather2.size() << "）";

	end = system_clock::now();
	cout << "\n[Solution 2] Execute time: " << duration_cast<milliseconds>(end - start).count() << " ms  O(Nlog(logN))";
	start = end;

	CountPrimeNumber_3(primeGather3, primeLimit);
	cout << "\n\n[Solution 3] The prime numbers under " << primeLimit
		<< "（" << primeGather3.size() << "）";

	end = system_clock::now();
	cout << "\n[Solution 3] Execute time: " << duration_cast<milliseconds>(end - start).count() << " ms  O(N)";
	start = end;

	cout << endl << endl;
	return 0;
}

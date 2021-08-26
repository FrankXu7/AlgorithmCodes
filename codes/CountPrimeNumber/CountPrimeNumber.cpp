/**************************************************************************************************
 * ����Ŀ������
 * ͳ������С��������N��������������
 * �������ԣ�
 * ��1��һ����ֻ�ܱ�1������������������Ϊ������������������Ϊ������0��1�Ȳ�������Ҳ���Ǻ�����
 * ��2��ż���У�ֻ��2����������
 *
 * �����롿
 * N = 203898
 * �������
 * Prime numbers count = 18294
 *
 * ������˼·��
 * ����һ:
 * ������ֱ���뵽�ģ����Ǳ���N���ڵ��������ˣ�Ȼ���ÿһ��������������С���������������������������жϣ�ͳ��֮��
 * ���������ʱ�临�ӶȻ�ܸߣ���ͨ�����������ʿ�֪��0��1�Ȳ�������Ҳ���Ǻ��������Կ���ֱ�Ӵ�2��ʼ������
 * ����Ϊ����ż���У�ֻ��2�������������Կ��Դ�3��ʼ��������������Ϊ2���ų�����ż��������Ч�ʡ�
 * �����иĽ��ռ䣬�ų�ż���󣬻��ǻ�������ӽ�N����������ϸ���룬���������� a,b��������� a*b=N��
 * ������� sqrt(N) Ϊ�磬a,b һ��һС���ֱ�λ�� sqrt(N) �������࣬������������� a,b ���� a*b=N��
 * ֻ��Ҫ��С��������� sqrt(N) ���ɣ�����������������һ�������ش��ڵ��� sqrt(N)��
 *
 * ��������
 * �ɲ��ð���ɸ��������˹����ɸ���������һ���� NUM�����ж�Ϊ��һ����������Ȼ��NUM �� N(N>=2) ����
 * ��Ϊһ�����������ԣ�������һ�����飬�����±���Ϊ����������ĳһ���±�����ʾ����ֵ���ж�Ϊ��һ��������
 * ���ø��±��Ӧ������Ԫ��ֵ���֮��ͬʱ���ɱ���±� NUM ���� N(N>=2) ���������±꣬���Ǳ�Ȼ�Ǻ�����
 * �����������ʣ�����2���⣬���е�������Ϊ������������ʵ����Ҫ�����±�Ϊż����Ԫ�أ�����Ϊ�±걾����ǲ�������
 * �൱��������һ��Ŀռ��ǿ��еġ�
 * �����ǵı������Խ�һ���Ż�����һ����ֵ NUM ���ж�Ϊ���������ش�NUM*2 ��ʼ�������Ԫ��Ϊ������
 * ��Ϊ���ǿ϶��� NUM ֮ǰ��������ǹ��ˣ�ֱ�Ӵ� NUM*NUM ��ʼ��ǣ�������ÿ�β���Ϊ NUM��
 * ���α�Ƕ�Ӧ�±���ֵΪ������
 * �����ϸ���ǣ�ÿ�εĲ��� NUM ����ʲôЧ������������3���� 3*3 ��ʼ��ǣ�������Ϊ3������һ����������� 9+3=12��
 * ��Ȼ������һ��ż������Ϊ��ͷ���ų���ż��2������ʣ��ż���в����ܴ��������ˣ������������ദ���ˣ����ٽ�һ���Ż���
 * �������趨Ϊ NUM*2����Ϊ NUM ��Ȼ��һ���������� NUM*2 ��Ȼ��һ��ż�����������ǵĺͣ�Ҳ��Ȼ�������������Ͳ���
 * �����ȥ����ż���ˡ�
 *
 * ��������
 * ����ɸ��ŷ��ɸ�����ڰ���ɸ�У���ʹ�� NUM*NUM ��ʼ��ǣ��Ի�����ظ���ǣ�����45����������3ʱ����� 3*3 ��ʼ��ǣ�
 * �� 3*15 �ᱻ���Ϊ�������ٱ�����5����� 5*5 ��ʼ��ǣ��Ὣ�Ѿ����Ϊ������45�ᱻ 5*9 �ظ����һ�Ρ�
 * ������һ�����ʣ��κκ������ֽܷ�ΪΨһһ���������ĳ˻���������ɸ�ĺ���˼����Ǳ�֤ÿ����ɸѡ���ĺ�����
 * �ض��Ǳ�����С������ɸѡ���ģ���ʱ��ֹ����ɸѡ���Ϳ��Ա��ⱻ�ظ�����ˡ����ԣ���������ĳ�� num ʱ��
 * ֻ��Ҫ�����������е�Ԫ���� num ��ˣ��˻��ض�Ϊ���������֮������� num �Ǻ�������������������
 * �ض�����Ψһһ�������ĳ˻����� num����Ϊ�����ǰ�������������ģ����������ڵ�Ԫ��һ��С�ڵ��� num����ʱ��
 * ����ҵ��˵�һ���ܹ��� num ��������������ô������������� num ����С����������������ֹ��������ɸѡ�������ظ���ǡ�
 * 
 * 
 * �����������
 * ����һ��
 * ʱ�临�Ӷȣ�O(N��N) ��Ȼ���Ӷȸ��ڰ���ɸ������ɸ����ʵ��ִ��ʱ���ԶС�����������㷨
 * �ռ临�Ӷȣ�O(1)
 * ��������
 * ʱ�临�Ӷȣ�O(Nlog(logN))
 * �ռ临�Ӷȣ�O(N) ��Ϊ�ų�����ż����ʵ����ֻ��O(N/2)�Ŀռ����õ�
 * ��������
 * ʱ�临�Ӷȣ�O(N)
 * �ռ临�Ӷȣ�O(N)
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
	// ��������1��0��1����������Ҳ���Ǻ�����
	if (targetNum <= 1) return;

	// 2��������Ψһ��ż�� 
	primeVec.emplace_back(2);

	// ��Ϊ�����жϵ�ǰ��ֵ������ 
	unsigned int divNum = 0;

	// ����2���⣬ֻ�������ſ������������ʶ� += 2 �ų�ż��
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		// ��ƽ����Ϊ�磬��������������������һ�����������Ҳ࣬����ֻ��Ҫ�жϵ�ƽ�����Ϳ���
		unsigned int cycleNum = static_cast<unsigned int>(sqrt(num));
		divNum = 3;

		// ��Ϊ num ��Ϊ���������Գ��� divNum ��������ż�����ʶ� += 2 �ų�ż�� 
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
	// ��������1��0��1����������Ҳ���Ǻ�����
	if (targetNum <= 1) return;

	// 2��������Ψһ��ż�� 
	primeVec.emplace_back(2);

	// �ų���ż���Ļ���ʵ��һ��Ŀռ����ò����ģ���������Ҫ�����±���� 
	vector<bool> judgeVec(targetNum, true);
	// ��������������޷�����Խ�� 
	unsigned long long int borderNum = 0;
	// ��Ϊ������ N(N>=2) ������ż�������Բ����ǵ�ǰ��������������ż֮�ͱ�Ϊ�� 
	unsigned int stepNum = 0;

	// ����2��ż���ض��Ǻ�����ͨ�� += 2 �ų�ż�� 
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		if (judgeVec[num] == false) continue;

		primeVec.emplace_back(num);

		borderNum = static_cast<unsigned long long int>(num) * num;
		if (borderNum >= targetNum) continue;

		/**
		 * �� num ���������� num �� N(N >= 2) ���ض��Ǻ�����ͨ�� += num ��Ǻ���
		 * �� num * 2 ��ʼ������������ò������ʶ��� num * num ��ʼ����
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
	// ��������1��0��1����������Ҳ���Ǻ�����
	if (targetNum <= 1) return;

	// �ų���ż���Ļ���ʵ��һ��Ŀռ����ò����ģ���������Ҫ�����±���� 
	vector<bool> judgeVec(targetNum, true);
	// ��������������޷�����Խ�� 
	unsigned long long int borderNum = 0;
	unsigned int primeCount = 0;

	// ����2��ż���ض��Ǻ�����ͨ�� += 2 �ų�ż�� 
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		if (judgeVec[num])
			primeVec.emplace_back(num);

		primeCount = primeVec.size();
		for (unsigned int idx = 0; idx < primeCount; ++idx)
		{
			borderNum = static_cast<unsigned long long int>(num) * primeVec[idx];
			if (borderNum >= targetNum) break;

			// �����˻���ȻΪ���������֮ 
			judgeVec[static_cast<unsigned int>(borderNum)] = false;

			// primeVec ����С����˳�����Ԫ�أ�����������ʱ����ǰ�������ض�Ϊ num ����С������ 
			if (num % primeVec[idx] == 0) break;
		}
	}

	/**
	 * 2��������Ψһ��ż����
	 * ��Ϊ�㷨�߼��У���������ÿһ��Ԫ�ػ������㣬
	 * ��2��Ϊż�������κδ���1���������˻����Ǻ�����
	 * ������Ҫ���㷨�����߼���ɺ��ټ��뵽��������
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
		<< "��" << primeGather1.size() << "��";

	end = system_clock::now();
	cout << "\n[Solution 1] Execute time: " << duration_cast<milliseconds>(end - start).count() << " ms  O(N��N)";
	start = end;

	CountPrimeNumber_2(primeGather2, primeLimit);
	cout << "\n\n[Solution 2] The prime numbers under " << primeLimit
		<< "��" << primeGather2.size() << "��";

	end = system_clock::now();
	cout << "\n[Solution 2] Execute time: " << duration_cast<milliseconds>(end - start).count() << " ms  O(Nlog(logN))";
	start = end;

	CountPrimeNumber_3(primeGather3, primeLimit);
	cout << "\n\n[Solution 3] The prime numbers under " << primeLimit
		<< "��" << primeGather3.size() << "��";

	end = system_clock::now();
	cout << "\n[Solution 3] Execute time: " << duration_cast<milliseconds>(end - start).count() << " ms  O(N)";
	start = end;

	cout << endl << endl;
	return 0;
}

/**************************************************************************************************
 * ����Ŀ������
 *
 *
 * �����롿
 *
 * �������
 *
 *
 * ������˼·��
 *
 *
 *
 * �����������
 * ʱ�临�Ӷȣ�
 * �ռ临�Ӷȣ�
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
		return; // ��������1��0��1����������Ҳ���Ǻ����� 
	else if (targetNum >= 2)
		primeVec.emplace_back(2); // 2��������Ψһ��ż�� 

	unsigned int divNum = 0;
	
	// ����2���⣬ֻ�������ſ������������ʶ� += 2 �ų�ż��
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		// ��ƽ����Ϊ�磬��������������������һ�����������Ҳ࣬����ֻ��Ҫ�жϵ�ƽ�����Ϳ���
		unsigned int cycleNum = static_cast<unsigned int>(sqrt(num));
		divNum = 3;

		// ��Ϊ num ��Ϊ���������Գ�����������ż�����ʶ� += 2 �ų�ż�� 
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
		return; // ��������1��0��1����������Ҳ���Ǻ����� 
	else if (targetNum >= 2)
		primeVec.emplace_back(2); // 2��������Ψһ��ż�� 

	// �ų���ż���Ļ���ʵ��һ��Ŀռ����ò����ģ���������Ҫ�����±���㣬Ŀǰû�뵽�ð취 
	vector<bool> judgeVec(targetNum, true);
	
	// ����2��ż���ض��Ǻ�����ͨ�� += 2 �ų�ż�� 
	for (unsigned int num = 3; num < targetNum; num += 2)
	{
		if (judgeVec[num] == false) continue;
		
		primeVec.emplace_back(num);
		// �� num ���������� num �� N(N >= 2) ���ض��Ǻ�����ͨ�� += num ��Ǻ��� 
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
		<< "��" << primeGather.size() << "���� \n\n";
	for (unsigned int idx = 0; idx < primeGather.size(); ++idx)
	{
		cout << primeGather[idx] << ",\t";
		if (idx + 1 >= 15 && (idx + 1) % 15 == 0) cout << endl;
	}

	vector<unsigned int>().swap(primeGather);
	CountPrimeNumber_2(primeGather, primeLimit);
	cout << "\n\n[Solution 2] The prime numbers under " << primeLimit
		<< "��" << primeGather.size() << "����\n\n";
	for (unsigned int idx = 0; idx < primeGather.size(); ++idx)
	{
		cout << primeGather[idx] << ",\t";
		if (idx + 1 >= 15 && (idx + 1) % 15 == 0) cout << endl;
	}

	cout << endl;
	return 0;
}

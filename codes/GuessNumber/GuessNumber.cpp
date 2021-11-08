/**************************************************************************************************
 * 【题目描述】
 * 猜测数字的大小，给定一个最大值N，从[1,N]选出一个数字 pickNum ，猜出被选中的PICK值并返回。每次猜测的值
 * 为 guessNum ，猜测的判断的核心算子满足：
 * pickNum < guessNum，返回-1，选中数字小于猜测数字；
 * pickNum == guessNum，返回0，选中数字与猜测数字相等；
 * pickNum > guessNum，返回1，选中数字大于猜测数字；
 *
 * 【输入】
 * N=100, pickNum=66
 * 【输出】
 * 找到被选中的66
 *
 * 【解题思路】
 * 二分法查找，初始设定为中间数字，然后与选中数字判断，从而确定新的猜测范围；
 *
 * 【解题分析】
 * 时间复杂度：O(logN)
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-10-18
 **************************************************************************************************/
#include <iostream>
using namespace std;

/**
 * @brief 辅助函数，局部静态变量决定挑选数字，判断猜测数字和挑选数字的关系
 * @param guess 传入猜测数字的引用
 * @return 返回-1、0、1表示猜测数字比挑选数字更小、相等和更大
 */
inline int GuessCalc(const unsigned int& guessNum)
{
	static unsigned int pickNum = 71;
	
	return (pickNum < guessNum) ? (-1) : (pickNum == guessNum ? 0 : 1);
}

unsigned int GuessNumber(unsigned int maxNum)
{
	unsigned int leftNum = 1, rightNum = maxNum, midNum = 0;

	do
	{
		midNum = leftNum + (rightNum - leftNum) / 2;

		if (GuessCalc(midNum) <= 0)
		{
			/**
			 * 猜大了，从[leftNum, midNum]重新猜，因包含相等的情况，
			 * 所以midNum不减1，否则会将刚好猜中的数字给排除掉，
			 * 当猜测数字等于挑选数字时，左右数字相等会终端循环
			 */
			rightNum = midNum;
		}
		else
		{
			// 猜小了，从[midNum+1, rightNum]重新猜 
			leftNum = midNum + 1;
		}


	} while (leftNum < rightNum);

	return leftNum;
}


int main(int argc, char** argv)
{
	unsigned int maxNum = 100;

	cout << "Guess the pick number between [1, " << maxNum << "]\n";
	cout << "\nThe pick number is: " << GuessNumber(maxNum);

	cout << endl << endl;
	return 0;
}
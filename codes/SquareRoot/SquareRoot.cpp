/**************************************************************************************************
 * 【题目描述】
 * 求一个给定的正整数的平方根，对最终答案向下取整。
 *
 * 【输入】
 * inputX=6
 *
 * 【输出】
 * sqrt=2.449
 * answer=2
 *
 * 【解题思路】
 * 可以观察到：
 * （1）当x=[0, 1]时，平方根等于自身；
 * （2）当x=[2, 5]时，平方根等于x/2；
 * （3）当x>5时，平方根必小于x/2，且随着x的增大，x的平方根和 x/2 差的绝对值也越来越大；因为x的平方根肯定小于
 *      等于x，所以用二分法查找。
 *
 * 【解题分析】
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-04-12
 **************************************************************************************************/
#include <iostream>
using namespace std;

int SqusreRoot(int&  x)
{
	if (x < 0) return -1;
	else if (x <= 1) return x;
	else if (x <= 5) return static_cast<int>(x / 2);

	int resultX = 0;

	int leftX = 0;
	/**
	 * 这里没有必要对 x/2，因为在 X>5 之后，x的平方根一定小于 x/2，
	 * 若初始 rightX = x/2，当 x 是奇数的时候，因为 midX 向下取整，导致会多比较一次 midX+1，
	 * 并且，当初始 rightX = x 时，从最终答案的右侧逼近答案，当初始 rightX = x/2，从最终答案的左侧逼近答案
	 */
	int rightX = x;
	int midX = static_cast<int>((leftX + rightX) / 2);
	
	while (leftX <= rightX)
	{
		if (midX * midX <= x)
		{
			resultX = midX;
			leftX = midX + 1;
		}
		else
		{
			rightX = midX - 1;
		}

		midX = static_cast<int>(leftX + rightX) / 2;
	}
	
	return resultX;
}

int main()
{
	int inputX = 0;
	cout << "Input Positive Integer: ";
	cin >> inputX;

	cout << "Standard answer: " << sqrt(inputX) << endl
		 << "Algorithm answer: " << SqusreRoot(inputX) << endl;

	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 给定一个正整数 area 表示一个矩形的面积，该矩形的长和宽用 L 和 W 来表示，需要求得 L 和 W 的值，要求：
 * （1）L 和 W 都是正整数，显然 L * W = area；
 * （2）L >= W 恒成立；
 * （3）L 和 W 的差值的绝对值尽可能的小；
 * 
 * 【输入】
 * area = 50;
 * 【输出】
 * L = 10; W = 5;
 * 
 * 满足 L * W = area 的所有情况为：[50, 1], [25, 2], [10, 5], [5, 10] [2, 25], [1, 50]
 * 排除掉不满足 L >= W 的情况：[50, 1], [25, 2], [10, 5]
 * L 和 W 的差值绝对值尽可能小：[10, 5]
 * 
 * 【解题思路】
 * 方法一：
 * 使得 L 和 W 尽可能接近的情况无疑是 area 的算术平方根是个整数，故而 L 肯定不会小于 area 的平方根，因为
 * L >= W 必须恒成立，如果 L 小于 area 的平方根的话，那么就不能满足 L * W = area 的条件了。所以，先求得
 * area 的平方根取整后赋值给 L，并使得初始时 L = W，然后遍历 W--，看是否能找都 L * (W--) == area 的情况。
 * 一轮遍历找不到的话，++L 后继续遍历。
 * 
 * 方法二：
 * 在方法一中，每轮遍历因为初始时 L = W，故每一轮遍历都需要枚举小于等于 W 的所有正整数，效率较低。可以换一
 * 角度，因为必须满足 L * W == area，所以 area 必须能够整除 L，所以在 ++L 的遍历过程中，找到首个满足等式：
 * area % L == 0 的 L（之所以是首个是为了保证 L 和 W 尽可能接近）即为矩形的长度，而宽度则可以通过 area/L
 * 来求得。
 * 
 * 方法三：
 * 有一个客观的现象是，一个数的平方根，会随着数字的增大，平方根和数字的差值会越来越大，在方法二中，是从面
 * 积的平方根作为起点开始遍历的，如果给定的面积逐渐的增大，那么区间 [√area, area] 的差值增大率会远大于区
 * 间 [1, √area] 的差值增大率，那显然枚举 [1, √area] 区间的值效率更高，又因为 L >= W 恒成立，故而该区间
 * 枚举出的肯定是 W，找到首个 area % W == 0 的 W 即为矩形的宽度，同理，长度 L 即为 area / W 的值。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N^2) 随着 area 的增大，可认为 [√area, area] 几乎包含了 [1, area]
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N) 随着 area 的增大，[√area, area] 差值和 [1, area] 渐进，可认为最差复杂度就是 O(N)
 * 空间复杂度：O(1)
 * 方法三：
 * 时间复杂度：O(√N) 只遍历 [1, √area] 区间，元素较少，且area为质数时，复杂度才会是 O(√N)
 * 空间复杂度：O(1)
 * 
 * @author FrankX
 * @date 2021-12-16
 *************************************************************************************************/
#include <iostream>
using namespace std;

pair<int, int> ConstructRectangle_1(int area)
{
	// len 必然要大于等于 area 的平方根，否则无法满足 len >= wdt && len * wdt == area 的条件 
	int len = static_cast<int>(sqrt(area)), wdt = len;

	while (len <= area)
	{
		while (len * wdt > area)
		{
			--wdt;
		}

		if (len * wdt == area)
		{
			break;
		}

		wdt = ++len;
	}

	return { len, wdt };
}

pair<int, int> ConstructRectangle_2(int area)
{
	int len = static_cast<int>(sqrt(area));

	while (area % len != 0)
	{
		++len;
	}

	return { len, area / len };
}

pair<int, int> ConstructRectangle_3(int area)
{
	int wdt = static_cast<int>(sqrt(area));
	
	while (area % wdt != 0)
	{
		--wdt;
	}

	return { area / wdt, wdt };
}

int main(int argc, char** argv)
{
	int area = 50;
	cout << "The give area of rectangle: " << area;

	pair<int, int> rect1 = ConstructRectangle_1(area);
	cout << "\n\n[Solution 1] The length and width of rectangle: " << rect1.first << ", " << rect1.second;

	pair<int, int> rect2 = ConstructRectangle_2(area);
	cout << "\n\n[Solution 2] The length and width of rectangle: " << rect2.first << ", " << rect2.second;

	pair<int, int> rect3 = ConstructRectangle_3(area);
	cout << "\n\n[Solution 3] The length and width of rectangle: " << rect3.first << ", " << rect3.second;

	cout << endl << endl;
	return 0;
}
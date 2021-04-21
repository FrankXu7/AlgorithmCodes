/**************************************************************************************************
 *
 * 【题目描述】
 * 给定两个升序数组，将第二个数组元素合并至第一个数组
 *
 * 【输入】
 * array1={1,3,5,7,9}
 * array2={2,4,6,8,10}
 * 【输出】
 * mergeArray={1,2,3,4,5,6,7,8,9,10}
 *
 * 【解题思路】
 * 利用 vector<T>::resize 特性：
 * （1）重置容器大小，减容时释放内存，扩容时会申请内存并初始化；
 * （2）重置后，不会改变原来在数组中数据的值（如果没被释放的话）；
 * 对数组1扩容，数组1扩容后容量 = 数组1扩容前容量 + 数组2容量；
 * 这里需要保存扩容前数组1数据的最大下标，用以之后的合并比较；
 * 从扩容后的数组1的末尾开始，依次反序遍历数组2，和扩容前数组1数据的最大下标；
 * 将数据从大到小，依次从扩容后的数组1末尾插入。
 *
 * @author FrankX
 * @date 2021-04-21
 **************************************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void MergeTwoSortedArray(vector<T>& beMergeArr, vector<T>& mergeArr)
{
	// 重置后beMergeArr实际大小会改变，保存重置前的大小，便以拿到该数组数据最大下标 
	unsigned int beMergeSize = beMergeArr.size();
	
	beMergeArr.resize(beMergeSize + mergeArr.size());
	typename vector<T>::reverse_iterator itr = beMergeArr.rbegin();
	
	for (int i = beMergeSize - 1, k = mergeArr.size() - 1; i >= 0 || k >= 0;)
	{
		if (i >= 0 && k >= 0)
		{
			*itr = beMergeArr[i] > mergeArr[k] ? beMergeArr[i--] : mergeArr[k--];
		}
		else if (i >= 0)
		{
			*itr = beMergeArr[i--];
		}
		else if (k >= 0)
		{
			*itr = mergeArr[k--];
		}
		else continue;

		++itr;
	}

	vector<T>().swap(mergeArr);
}

int main()
{
	vector<int> beMergeArr = {1,3,5,7,9};
	vector<int> mergeArr = {2,4,6,8,10};
	
	cout << "Size after merge: " << beMergeArr.size() + mergeArr.size() << endl;
	MergeTwoSortedArray(beMergeArr, mergeArr);
	
	for (vector<int>::iterator itr = beMergeArr.begin(); itr != beMergeArr.end(); ++itr)
	{
		cout << *itr << ' ';
	}
	cout << endl;

	return 0;
}

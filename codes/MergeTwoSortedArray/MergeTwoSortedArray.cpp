#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void MergeTwoSortedArray(vector<T>& beMergeArr, vector<T>& mergeArr)
{
	unsigned int beMergeSize = beMergeArr.size();
	unsigned int mergeSize = mergeArr.size();

	beMergeArr.resize(beMergeSize + mergeSize);
	typename vector<T>::reverse_iterator itr = beMergeArr.rbegin();
	
	for (int i = beMergeSize - 1, k = mergeSize - 1; i >= 0 || k >= 0;)
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
	vector<int> beMergeArr = {2, 3, 3, 5, 7, 9, 11, 11, 13, 27, 55, 60};
	vector<int> mergeArr = {5, 7, 7, 10, 45, 50, 61, 61, 89};
	
	cout << "Size after merge: " << beMergeArr.size() + mergeArr.size() << endl;
	MergeTwoSortedArray(beMergeArr, mergeArr);
	
	for (vector<int>::iterator itr = beMergeArr.begin(); itr != beMergeArr.end(); ++itr)
	{
		cout << *itr << ' ';
	}
	cout << endl;

	return 0;
}

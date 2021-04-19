#include <iostream>
#include <vector>

using namespace std;

void MergeTwoSortedArray(vector<int>& beMergeArr, vector<int>& mergeArr)
{

}

int main()
{
	vector<int> arr = {6,6,8,8};
	arr[8] = 999;
	for (vector<int>::iterator itr = arr.begin(); itr != arr.end(); ++itr)
	{
		cout << *itr << '\t';
	}
	cout << endl;
	cout << arr.size() << endl;
	cout << arr[8] <<endl;
	return 0;
}

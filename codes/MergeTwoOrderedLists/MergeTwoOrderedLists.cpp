/* No.21 Merge two ascending linked list and return the new ascending linked list.  */
#include "../public_helper/global_define.h"
#include <iostream>
#include <vector>

using namespace std;

/*
 * @brief Merge two ascending linked list to a new ascending linkes list
 * @param resultArr The first and also as the final result list
 * @param mergeArr The second list which is merge to the first list
 * @return The first list and the second list should be empty
 * */
LinkOb<int>* MergeList(LinkOb<int>* resultArr, LinkOb<int>* mergeArr)
{
	LinkOb<int> *r = resultArr;
	LinkOb<int> *last_r = nullptr;

	while (r && mergeArr)
	{
		if (r->data <= mergeArr->data)
		{
			last_r = r;
			r = mergeArr;
			mergeArr = mergeArr->next;
			r->next = last_r->next;
			last_r->next = r;
		}
		else
		{
			if (!last_r)
			{
				resultArr = mergeArr;
				mergeArr = mergeArr->next;
				resultArr->next = r;
				last_r = resultArr;
			}
			else
			{
				last_r->next = mergeArr;
				last_r = mergeArr;
				mergeArr = mergeArr->next;
				last_r->next = r;
			}
		}
	}

	if (mergeArr) r ? r->next = mergeArr : last_r->next = mergeArr;

	return resultArr;
}

int main()
{
	LinkOb<int> *resultArr = new LinkOb<int>();
	LinkOb<int> *mergeArr = new LinkOb<int>();

	LinkOb<int> *pr = resultArr;
	LinkOb<int> *pm = mergeArr;
	
	vector<int> arr1 = { 2 };
	vector<int> arr2 = { 1, 3 };

	for (int i = 0; i < arr1.size() || i < arr2.size(); ++i)
	{
		if (i < arr1.size())
		{
			pr->data = arr1[i];
			if (i + 1 < arr1.size())
			{
				pr->next = new LinkOb<int>();
				pr = pr->next;
			}
		}

		if (i < arr2.size())
		{
			pm->data = arr2[i];
			if (i + 1 < arr2.size())
			{
				pm->next = new LinkOb<int>();
				pm = pm->next;
			}
		}
	}

	// Now resultArr has including all new LinkObs
	resultArr = MergeList(resultArr, mergeArr);
	// mergeArr had all merged to resultArr
	mergeArr = nullptr;
	pm = nullptr;

	cout << "Merge result: " << endl;
	while (resultArr)
	{
		cout << resultArr->data << ' ';
		pr = resultArr;
		resultArr = resultArr->next;
		delete pr;
	}
	pr = nullptr;
	resultArr = nullptr;
	cout << endl;

	return 0;
}

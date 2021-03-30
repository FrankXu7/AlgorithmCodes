/* No.27 Remove the element which is equal to the given number in an unsorted array. */
#include "../public_helper/global_define.h"
#include <iostream>

using namespace std;

/*
 * @brief Remove the element which is equal to the given number in an unsorted array
 * @param arr Target array
 * @param num The given number
 * */
int removeElement(LinkOb<int>* arr, int num)
{
	int countElement = 0;
	while(arr)
	{
		if (arr->data == num)
		{
			arr = arr->next;
			p->next = arr->next;
		}
		else
		{
			++countElement;
		}

		arr = arr->next;
		p = arr;
	}

	return countElement;
}

int main()
{
	int num[100];
	int i = 0;
	while (cin >> num[i])
	{
		++i;
	}
	cout << i << endl;
	return 0;
}

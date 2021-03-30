/* No.27 Remove the element which is equal to the given number in an unsorted array. */
#include <iostream>

using namespace std;

template <typename T>
struct LinkOb
{
	T data;
	LinkOb<T>* next;
};

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
		arr = arr->next;
	}

	return countElement;
}

int main()
{
	return 0;
}

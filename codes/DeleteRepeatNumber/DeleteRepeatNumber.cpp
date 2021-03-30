/* No.26 Delete repeat numbers in an ascing array. */
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct LinkOb
{
	T data;
	LinkOb<T>* next;
};

/*
 * @brief Delete repeat numbers in an ascing array
 * @param resultArr The given array pointer
 * @return The length after handle
 * */
int DelRepeatNum(LinkOb<int>* resultArr)
{
	int idx = 0;
	
	while (resultArr)
	{
		if (resultArr->next && resultArr->data == resultArr->next->data)
		{
			resultArr->next = resultArr->next->next;
		}
		else 
		{
			resultArr = resultArr->next;
			++idx;
		}
	}

	return idx;
}

int main()
{
	LinkOb<int> *resultArr = new LinkOb<int>();
	LinkOb<int>* p = resultArr;

	vector<int> tempArr = { 0,0,1,1,1,2,2,3,4 };
	for (unsigned int i = 0; i < tempArr.size(); ++i)
	{
		p->data = tempArr[i];
		if (i + 1 < tempArr.size())
		{
			p->next = new LinkOb<int>();
		}
	
		p = p->next;
	}
	
	cout << "Size: " << DelRepeatNum(resultArr) << endl;
	while (resultArr)
	{
		p = resultArr;
		cout << p->data << ' ';
		resultArr = resultArr->next;
		delete p;
	}
	p = nullptr;
	resultArr = nullptr;
	cout << endl;

	return 0;
}

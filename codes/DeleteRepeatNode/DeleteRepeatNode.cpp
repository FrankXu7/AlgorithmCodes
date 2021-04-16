#include <iostream>
#include <vector>

using namespace std;

template<typename TYPE>
struct ListNode
{
	TYPE data;
	ListNode<int>* next;
};

ListNode<int>* DeleteRepeatNode(ListNode<int>* head, ListNode<int>*& delHead)
{
	ListNode<int>* p = head;
	ListNode<int>* t;
	delHead = head;
	while (0)
	{
		if (p->next && p->data == p->next->data)
		{

		}
	}

	return head;
}

int main()
{
	vector<int> listData = { 1,2,3,3,3,4,5 };
	
	ListNode<int>* head = new ListNode<int>;
	ListNode<int>* delHead = nullptr;
	ListNode<int>* p = head;

	for (vector<int>::iterator itr = listData.begin(); itr != listData.end(); ++itr)
	{
		p->data = *itr;
		p->next = new ListNode<int>;
		p = p->next;
	}

	cout << head << '\t' << delHead << endl;
	DeleteRepeatNode(head, delHead);
	cout << head << '\t' << delHead << endl;


	return 0;
}

/**************************************************************************************************
 * 【题目描述】
 * 给定一个链表表头head，判断该链表是否为回文链表，是则返回true，否则返回false；
 * 回文链表即以中间节点分割，左右两侧数据对称相等。
 * 
 * 原题设数据的取值区间为：[0, 9]，节点个数区间为：[1, 10^5]
 * 
 * 【输入】
 * Linked List = [1,2,3,2,1]
 * 【输出】
 * 返回true
 * 
 * 【解题思路】
 * 方法一：
 * 题意要求数值的取值区间是 [0, 9]，且节点个数区间为 [1, 10^5]，所以可直接遍历链表，将链表各节点组合为
 * 一个数字，然后判断这个数字是否为回文数即可。
 * 
 * 方法二：
 * 题目对节点取值和节点个数有了很大限制所以可采用方法一，考虑适用性更强的方法，不限制节点取值和节点个数。
 * 链表的特点就是无法随机访问，所以可以先遍历一遍链表，将节点暂存到一个数组中，使用vector容器作为接收数组，
 * 然后就可以利用数组的随机访问性，分别从头尾进行比较判断是否为回文数组，也即是回文链表。
 * 
 * 方法三：
 * 规避掉链表的无法随机访问，但却造成了空间复杂度的提升，在方法二中，需要一个额外的数组存储链表所有数据，
 * 为了将空间复杂度降下来，一般会想到递归，比如先全局保存头指针，然后递归到链表尾指针，这样就可以在递归函
 * 数逐个弹出之时，拿到链表对称的头尾指针。不过此方法依然需要较高的空间复杂度，且递归层级太深会使得该方案
 * 实际比方法二的效率更加低下。
 * 
 * 可以使用 “快慢指针” 法，慢指针步长为1，快指针步长为2，这样，当快指针指向链表尾部时，慢指针刚好指向链表中间，
 * 以慢指针为分割节点，将链表右侧进行一次反转，然后将分割节点左侧的链表，和分割节点右侧反转过后的链表，进行
 * 比较判断是否为回文链表。这里有一些注意点：
 * （1）慢指针指向分割节点时，其next需要指向null，从结构上彻底分割；
 * （2）反转链表时，表头节点首次赋值需要将next指向null，因为首个表头最后会作为表尾，不置null会产生循环链表；
 * （3）记得要将分割节点右侧链表反转回来，并且重新续上，算法最后不会改变链表的结构。
 * 
 * 该方法的时间复杂度虽然是O(N)级别，但实际包含三个部分：
 * 遍历链表找到分割点O(N) + 反转链表节点O(N/2) + 比较链表节点O(N/2) + 二次反转链表节点并续上O(N/2)；
 * 牺牲了一定的时间复杂度，并且降低代码可读性，最终得到常数级别的空间复杂度。
 * 
 * 【解题分析】
 * 方法一：
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 方法二：
 * 时间复杂度：O(N)
 * 空间复杂度：O(N)
 * 方法三：
 * 时间复杂度：O(N) 实际时间复杂度为O(N + N/2 + N/2 +N/2)，实际以牺牲时间复杂度和代码可读性来降低空间复杂度
 * 空间复杂度：O(1)
 *
 * @author FrankX
 * @date 2021-09-07
 **************************************************************************************************/
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

template<typename Data_Type>
struct ListNode
{
	Data_Type data;
	shared_ptr<ListNode<Data_Type>> next;

	ListNode(Data_Type _data)
	{
		data = _data;
		next = nullptr;
	}
};

#define N(val, Data_Type) (make_shared<ListNode<Data_Type>>(val));


bool PalindromeList_1(shared_ptr<ListNode<int>> head)
{
	int sum = 1;
	while (head)
	{
		sum = sum * 10 + head->data;
		head = head->next;
	}

	int palindrome = 1;
	while (palindrome < sum)
	{
		palindrome = (palindrome * 10) + (sum % 10);
		sum = static_cast<int>(sum / 10);
	}

	return (palindrome == sum || static_cast<int>(palindrome / 10) == sum);
}

template<typename Data_Type>
bool PalindromeList_2(shared_ptr<ListNode<Data_Type>> head)
{
	if (!head) return true;

	vector<decltype(head)> dataArr;
	while (head)
	{
		dataArr.emplace_back(head);
		head = head->next;
	}

	auto dataSize = dataArr.size();
	unsigned int leftIdx = 0;
	unsigned int rightIdx = dataSize - 1;

	while (leftIdx < rightIdx)
	{
		if (dataArr[leftIdx]->data != dataArr[rightIdx]->data)
		{
			return false;
		}

		++leftIdx;
		--rightIdx;
	}

	return true;
}

/**
 * @brief 辅助函数，反转一个链表
 * @param 链表头节点
 * @return 返回反转后的链表头节点
 */
template<typename Data_Type>
shared_ptr<ListNode<Data_Type>> ReverseList(shared_ptr<ListNode<Data_Type>> head)
{
	decltype(head) pNewHead = nullptr, p = nullptr;

	while (head)
	{
		p = head;
		head = head->next;

		// 首次赋值时节点next一定要指向null，否则会行成循环链表 
		if (!pNewHead)
			p->next = nullptr;
		else
			p->next = pNewHead;

		pNewHead = p;
	}

	return pNewHead;
}

template<typename Data_Type>
bool PalindromeList_3(shared_ptr<ListNode<Data_Type>> head)
{
	if (!head) return true;

	auto spFast = head;
	auto spSlow = head;

	// 找到链表的中间分割点 
	while (spFast->next && spFast->next->next)
	{
		spSlow = spSlow->next;
		spFast = spFast->next->next;
	}
	// 指向分割节点 
	auto spDivide = spSlow->next;
	// 断开分割节点指向 
	spSlow->next = nullptr;

	// 从中间分割点开始，反转右侧列表 
	auto reverseHead = ReverseList(spDivide);
	// 反转后更新分割节点，便于后面还要反转回来 
	spDivide = reverseHead;

	// 进行数据比较 
	bool bPalindrome = true;
	while (head && reverseHead)
	{
		if (head->data != reverseHead->data)
		{
			bPalindrome = false;
			break;
		}

		head = head->next;
		reverseHead = reverseHead->next;
	}

	// 进行二次反转，将分割的右侧链表掰回来 
	reverseHead = ReverseList(spDivide);

	// 左右链表重新续上，从哪里断开就从哪里续上 
	spSlow->next = reverseHead;

	return bPalindrome;
}


int main(int argc, char** argv)
{
	shared_ptr<ListNode<int>> head = nullptr;
	shared_ptr<ListNode<int>> sp = nullptr;

	// 构造单链表 
	vector<int> arr{ 1,2,3,7,3,2,1 };
	for (auto itr = arr.begin(); itr != arr.end(); ++itr)
	{
		if (!head)
		{
			sp = head = N(*itr, int);
		}
		else
		{
			sp->next = N(*itr, int);
			sp = sp->next;
		}
	}

	cout << "Linked list datas:\n";
	sp = head;
	while (sp)
	{
		cout << sp->data << ", ";
		sp = sp->next;
	}

	cout << "\n\n[Solution 1] Is palindrome linked list ? " << (PalindromeList_1(head) ? "YES\n" : "NO\n");
	cout << "\n\n[Solution 2] Is palindrome linked list ? " << (PalindromeList_2(head) ? "YES\n" : "NO\n");
	cout << "\n\n[Solution 3] Is palindrome linked list ? " << (PalindromeList_3(head) ? "YES\n" : "NO\n");

	cout << "\n\nLinked list datas after calc:\n";
	sp = head;
	while (sp)
	{
		cout << sp->data << ", ";
		sp = sp->next;
	}

	cout << endl << endl;
	return 0;
}
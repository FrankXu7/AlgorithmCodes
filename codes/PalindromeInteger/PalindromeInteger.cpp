/* No.9 A palindrome number. */
#include <iostream>

using namespace std;

void JudgePalindrome(int num)
{
	if (num <= 0 || num % 10 == 0)
	{
		cout << "Not a palindrome number." << endl;
		return;
	}

	int tempNum = 0;
	while (num > tempNum)
	{
		tempNum = tempNum * 10 + num % 10;
		num = static_cast<int>(num / 10);
	}
	
	// For the case: 1221 or 12321
	if (tempNum == num || static_cast<int>(tempNum / 10) == num) 
		cout << "This is a Palindrome number." << endl;
	else
		cout << "Not a Palindrome number." << endl;
}

int main()
{
	int inputNum = 0;
	cout << "Input:  ";
	cin >> inputNum;

	JudgePalindrome(inputNum);

	return 0;
}

/* No.20 Find out valid brackets pairs. */
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

unordered_map<char, char> brackets = {
	{'(', ')'},
	{'[', ']'}, 
	{'{', '}'},
	{')', 0},
	{']', 0},
	{'}', 0},
};

bool PairBrackets(string& str)
{
	stack<char> desired;

	for (int idx = 0; idx < str.length(); ++idx)
	{
		if (brackets.count(str[idx]) != 0)
		{
			if (brackets[str[idx]] != 0)
				desired.push(brackets[str[idx]]);
			else if (!desired.empty() && str[idx] == desired.top())
				desired.pop();
			else 
				return false;
		}
		else 
			// Find char which not belongs to brackets
			return false;
	}

	return desired.empty();
}

int main()
{
	cout << "Input: ";
	string inputStr = "";
	cin >> inputStr;
	cout << (PairBrackets(inputStr) ? "Pairs Match!" : "Invalid pairs!") << endl;

	return 0;
}

/* No.13 A Roman numeral turned into an integer.  */

Not ready yet.

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>
#include <iterator>

using namespace std;

/*
 * Special case:
 * IV=4		IX=9
 * XL=40	XC=90
 * CD=400	CM=900
 * */
map<char, int> numMap = {
	{'I', 1}, {'V', 5},
	{'X', 10}, {'L', 50},
	{'C', 100}, {'D', 500},
	{'M', 1000},
	{'i', 1}, {'v', 5},
	{'x', 10}, {'l', 50},
	{'c', 100}, {'d', 500},
	{'m', 1000},
};

/*
 * @brief Convert the given Roman numerals steing intoto Integer
 * @param str The given Roman numerals string
 * */
void RomanToInt(vector<char>& str)
{
	int resultNum = 0;

	char curKey = '\0';
	int nextValue = 0;

	vector<char>::iterator itr = str.begin();

	cout << "Valid Input: ";
	for (; itr != str.end(); ++itr)
	{
		if (!curKey)
		{
			curKey = *itr;
			++itr;
		}
		if (numMap.count(curKey) == 0)
		{
			curKey = '\0';
			continue;
		}
		
		if (itr != str.end() && numMap.count(*itr) == 0) continue;
		if (itr == str.end()) nextValue = 0;
		else nextValue = numMap[*itr];

		if (numMap[curKey] >= nextValue)
		{
			resultNum += numMap[curKey];
			cout << curKey;
		}
		else if (nextValue / numMap[curKey] <= 10)
		{
			resultNum += (nextValue - numMap[curKey]);
			numMap.erase(curKey);
			cout << curKey << *itr;
		}
		else continue;

		--itr;
		curKey = '\0';
	}

	cout << endl << "Integer: " << resultNum << endl;
}

int main()
{
	vector<char> inputStr;

	cout << "Roman numeral: ";
	char tempChar = '\0';
	while ((tempChar = cin.get()) != '\n')
	{
		inputStr.push_back(tempChar);
	}
	RomanToInt(inputStr);

	return 0;
}

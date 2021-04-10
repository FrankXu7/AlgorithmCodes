#include <iostream>
#include <string>

using namespace std;

string BinaryPlus(string& s1, string& s2)
{
	string resultStr = "";
	int carryOne = 0;

	int idx = 0, n = 0;
	if (s1.length() < s2.length())
	{
		idx = s1.length() - 1;
		n = s2.length();
	}
	else
	{
		idx = s2.length() - 1;
		n = s1.length();
	}

	for (; idx >= 0; --idx)
	{
		if (s1[idx] == s2[idx])
		{
			resultStr.insert(resultStr.begin(), (carryOne == 1) ? '1' : '0');
			carryOne = (s1[idx] != '0') ? 1 : 0;
		}
		else
		{
			resultStr.insert(resultStr.begin(), '1');
			carryOne = 0;
		}
	}
	
	return resultStr;
}

int main()
{
	string s1 = "1010";
	string s2 = "0011";

	cout << BinaryPlus(s1, s2) << endl;

	return 0;
}

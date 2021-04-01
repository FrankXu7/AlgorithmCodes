#include <iostream>
#include <string>

using namespace std;

int StrStr(string& haystack, string& needle)
{
	if (needle.length() == 0) return 0;

	int strIdx = -1;
	int searchIdx = 0;

	for (int idx = 0; idx < haystack.length(); ++idx)
	{
		if (searchIdx >= needle.length())
		{
			break;
		}
		else if (haystack[idx] == needle[idx])
		{
			++strIdx;
			++searchIdx;
		}
		else
		{
			strIdx = -1;
			searchIdx = 0;
		}
	}

	return strIdx;
}

int main()
{
	string haystack = "";
	string needle = "";

	cout << "Input target string: " << endl;
	cin >> haystack;
	cout << "Input search string:" << endl;
	cin >> needle;

	cout << "Search Index: " << StrStr(haystack, needle) << endl;

	return 0;
}


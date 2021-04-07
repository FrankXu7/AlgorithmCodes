#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string ExteriorArray(string& exteriorStr, int& n)
{
	vector<string> resultStr;
	unordered_map<char, int> tempMap;
	tempMap.insert({ exteriorStr[0], 1 });
	
	char curKey = exteriorStr[0];
	for (int idx = 1; idx < exteriorStr.length(); ++idx)
	{
		if (curKey == exteriorStr[idx])
		{
			++tempMap[curKey];
		}
		else
		{
			resultStr.push_back(tempMap[curKey] + curKey);
			tempMap[curKey] = 0;
			curKey = exteriorStr[idx];
			tempMap[curKey] = 1;

		}
	}

	return resultStr[n];
}

int main()
{
	return 0;
}

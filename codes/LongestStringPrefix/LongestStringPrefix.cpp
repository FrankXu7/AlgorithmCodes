/* No.14 Find out the max length prefix of a string array. */
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

/*
 * @brief Find out the max length prefix of given string vector
 * @param strArr String vector
 * */
void MaxStrPre(vector<string>& strArr)
{
	string strPre = "";
	// Get the first string for reduce one cycle
	string firstStr = strArr[0];
	vector<string>::iterator itn;

	for (int m = 0; m < firstStr.length(); ++m)
	{
		for (itn = strArr.begin() + 1; itn != strArr.end(); ++itn)
		{
			// While exist one char is not equal in the same index then break
			if (firstStr[m] != (*itn)[m]) break;
		}

		if (itn == strArr.end())
			strPre += firstStr[m];
		else 
			break;
	}

	cout << "The finall prefixo: " << strPre << endl;
}

int main()
{
	vector<string> inputStr;
	string tempStr = "";
	
	do
	{
		getline(cin, tempStr);
		if (tempStr != "")
			inputStr.push_back(tempStr);
	}
	while (tempStr != "");

	MaxStrPre(inputStr);

	return 0;
}

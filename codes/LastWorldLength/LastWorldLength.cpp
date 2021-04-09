#include <iostream>
#include <string>

using namespace std;

unsigned int LastWorldLength(string& str)
{
	unsigned int len = 0;
	for (int idx = str.length() - 1; idx >= 0; --idx)
	{
		if (str[idx] != ' ' && str[idx] != '\t')
			++len;
		else if (len > 0)
			break;
	}

	return len;
}

int main()
{
	string inputStr = "";
	cout << "Input string: ";
	getline(cin, inputStr);
	
	cout << "Last world length: " << LastWorldLength(inputStr) << endl;

	return 0;
}

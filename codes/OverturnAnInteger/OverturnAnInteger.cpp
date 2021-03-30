/* No.7 Overturn an Integer. */
#include <iostream>
#include <climits>

using namespace std;

void OverturnNum(int inputNum)
{
	int resultNum = 0;

	while (inputNum != 0)
	{
		resultNum = resultNum * 10 + inputNum % 10;
		inputNum = static_cast<int>(inputNum / 10);
	}

	cout << "Overturn Number: " << resultNum << endl;
}

int main()
{
	int inputNum = 0;
	cout << "Input an Integer: ";
	cin >> inputNum;

	OverturnNum(inputNum);

	cout << endl << "Integer Range: " << endl << INT_MIN << endl << INT_MAX << endl;

	return 0;
}

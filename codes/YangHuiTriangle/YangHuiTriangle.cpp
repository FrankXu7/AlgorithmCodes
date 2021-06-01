#include <iostream>
#include <vector>
using namespace std;

void YangHuiTriangle(unsigned int numRows)
{
	vector<vector<unsigned int>> triangle = {{ 1 }};
	cout << triangle[0][0];
	
	for (unsigned int row = 1; row < numRows; ++row)
	{
		triangle.push_back({});
		cout << endl;
		for (unsigned int idx = 0; idx <= row + 1; ++idx)
		{
			vector<unsigned int> lastRow = triangle[row - 1];
			unsigned int leftNum = (idx == 0) ? 0 : lastRow[idx - 1];
			unsigned int rightNum = (idx == row + 1) ? 0 : lastRow[idx];

			cout << (leftNum + rightNum) << ", ";
			triangle[row].push_back(leftNum + rightNum);
		}
	}
}

int main()
{
	YangHuiTriangle(10);
	return 0;
}

#include <iostream>
#include <vector>
using namespace std;

void YangHuiTriangle(unsigned int numRows)
{
	vector<vector<unsigned int>> triangle = {{ 1 }};
	cout << triangle[0][0] << endl;
	
	for (unsigned int row = 1; row < numRows; ++row)
	{
		triangle.push_back({});
		cout << endl;
		for (unsigned int idx = 0; idx <= row; ++idx)
		{
			unsigned int leftNum = (idx == 0) ? 0 : triangle[row - 1][idx - 1];
			unsigned int rightNum = (idx == triangle[row - 1].size()) ? 0 : triangle[row - 1][idx - 1];
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

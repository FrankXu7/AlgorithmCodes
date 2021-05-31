#include <iostream>
#include <vector>
using namespace std;

void YangHuiTriangle(const vector<vector<unsigned int>>& triangle, unsigned int numRows)
{
	triangle.push_back({ 1 });
	for (unsigned int row = 1; row < numRows; ++row)
	{
		for (unsigned int idx = 0; idx <= row; ++idx)
		{
			triangle;
		}
	}
}

int main()
{
	return 0;
}

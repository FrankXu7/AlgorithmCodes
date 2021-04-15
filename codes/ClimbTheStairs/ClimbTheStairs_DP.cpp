#include <iostream>
#include <vector>

using namespace std;

unsigned int ClimbTheStairs(const unsigned int& n)
{
	if (n <= 2) return n;
	else if (n >= 47) return 0;

	vector<unsigned int> midN = { 1, 2 };

	for (unsigned int idx = 2; idx < n; ++idx)
	{
		midN[idx] = midN[idx - 1] + midN[idx - 2];	
	}

	return midN[n - 1];
}

int main()
{
	unsigned int inputN = 0;
	cout << "Input N: " ;
	cin >> inputN;

	cout << ClimbTheStairs(inputN) << endl;

	return 0;
}

#include <iostream>
using namespace std;

unsigned int SqusreRoot(unsigned int&  x)
{
	if (x <= 1) return x;
	else if (x <= 5) return static_cast<unsigned int>(x / 2);

	unsigned int resultX = 0;

	unsigned int leftX = 0;
	unsigned int rightX = static_cast<unsigned int>(x / 2);
	unsigned int midX = static_cast<unsigned int>((leftX + rightX) / 2);

	while (leftX <= rightX)
	{
		if (midX * midX <= x)
		{
			resultX = midX;
			leftX = midX + 1;
		}
		else
		{
			rightX = midX - 1;
		}

		midX = static_cast<unsigned int>(leftX + rightX);
	}
	
	return resultX;
}

int main()
{
	unsigned

	return 0;
}

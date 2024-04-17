#include <iostream>
#include "RandomGenerator.h"

int main()
{
	RandomGenerator rand(3, 5, 11);
	std::vector<int> res = rand.generate(1,100);
	for (int i = 0; i < res.size(); i++)
		std::cout << res[i] << " ";
	return 0;
}
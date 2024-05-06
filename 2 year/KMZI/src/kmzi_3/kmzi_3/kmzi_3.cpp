#include <iostream>
#include "RandomGenerator.h"

int main()
{
	int a = 1;
	RandomGenerator rand(a, 5, 64);
	std::vector<int> res = rand.generate(1,100);
	for (int i = 0; i < res.size(); i++)
		std::cout << res[i] << " ";
	return 0;
}
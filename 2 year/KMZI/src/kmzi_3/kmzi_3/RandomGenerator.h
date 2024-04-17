#pragma once
#include <vector>
#include <iostream>
class RandomGenerator
{
private:
	int a,c,N;
	int extendedEuclidean(int a, int b, int& x, int& y);
	int findMultiplicativeInverse(int x);
	int calculateNewX(int x0);
public:
	RandomGenerator(int a, int c, int N);
	std::vector<int> generate(int x0, int size);
};


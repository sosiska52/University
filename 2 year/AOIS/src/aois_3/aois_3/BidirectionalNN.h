#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class BidirectionalNN
{
private:
	int n, m;
	std::vector<std::vector<int>> Weight;
	std::vector<std::vector<int>> WeightTransposed;

	std::vector<std::vector<int>> transposeMatrix(std::vector<std::vector<int>>);
	void roundVector(std::vector<int>&);
	void test(std::vector<std::vector<int>> XT, std::vector<std::vector<int>> Y);
public:
	BidirectionalNN(int n, int m);
	void predict(bool mode, std::vector<int>);
	void initializeWeight(std::vector<std::vector<int>> X, std:: vector<std::vector<int>> Y);
};


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

	std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2);
	std::vector<std::vector<int>> transposeMatrix(std::vector<std::vector<int>>);
	std::vector<std::vector<int>> roundVector(std::vector<std::vector<int>>);
public:
	BidirectionalNN(int n, int m);
	std::vector<std::vector<int>> function(bool mode, std::vector<std::vector<int>>);
	void initializeWeight(std::vector<std::vector<int>> X, std:: vector<std::vector<int>> Y);
};


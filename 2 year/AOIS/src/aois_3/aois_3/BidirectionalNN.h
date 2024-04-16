#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class BidirectionalNN
{
private:
	int n, m;
	std::vector<std::vector<double>> Weight;
	std::vector<std::vector<double>> WeightTransposed;

	std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2);
	std::vector<std::vector<double>> transposeMatrix(std::vector<std::vector<double>>);
	std::vector<std::vector<double>> roundVector(std::vector<std::vector<double>>);
public:
	BidirectionalNN(int n, int m);
	std::vector<std::vector<double>> function(bool mode, std::vector<std::vector<double>>);
	void initializeWeight(std::vector<std::vector<double>> X, std:: vector<std::vector<double>> Y);
};


#pragma once
#include <vector>
#include <time.h>
#include <iostream>
class Matrix
{
public:
	static void fillRand(std::vector<std::vector<double>>& matrix);

	static std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector);
	static std::vector<double> multiplyMatrixVector_T(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector);

	static std::vector<std::vector<double>> extractSubMatrix(const std::vector<std::vector<double>>& matrix, int startRow, int startCol, int length);
};


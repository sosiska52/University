#pragma once
#include <vector>
#include <iostream>
class Matrix
{
public:
	static void fillRand(std::vector<std::vector<double>>& matrix);

	static std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector);
	static std::vector<double> multiplyMatrixVector_T(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector);

	static double convolute(const std::vector<double>& neurons, const std::vector<double>& kernel, int length);
	static double convolute(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2);
	std::vector<double> extractSubMatrix(const std::vector<double>& matrix, int matrixRows, int matrixCols, int startRow, int startCol, int length);
	std::vector<std::vector<double>> extractSubMatrix(const std::vector<std::vector<double>>& matrix, int startRow, int startCol, int length);
};


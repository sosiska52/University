#pragma once
#include <vector>
#include <time.h>
#include <iostream>
class Matrix
{
public:
	static void fillRand(std::vector<std::vector<double>>& matrix);

	static std::vector<std::pair<double, double>> summ(const std::vector<std::pair<double, double>>& vector1, const std::vector<double>& vector2);

	static std::vector<std::pair<double, double>> multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<std::pair<double, double>>& vector);

	static std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector);

	static std::vector<std::pair<double, double>> multiplyMatrixVector_T(const std::vector<std::vector<double>>& matrix, const std::vector<std::pair<double, double>>& vector);

	static std::vector<double> multiplyMatrixVector_T(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector);
};


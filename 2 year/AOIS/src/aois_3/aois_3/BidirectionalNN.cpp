#include "BidirectionalNN.h"

BidirectionalNN::BidirectionalNN(int n, int m) {
	this->n = n;
	this->m = m;
	Weight = std::vector<std::vector<int>>(m , std::vector<int>(n, 0));
	WeightTransposed = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
}

void BidirectionalNN::roundVector(std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > 1)
			vec[i] = 1;
		if (vec[i] < -1)
			vec[i] = -1;
	}
}

std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    if (matrix1.empty() || matrix2.empty() || matrix1[0].size() != matrix2.size()) {
        return {}; 
    }

    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

std::vector<std::vector<int>> BidirectionalNN::transposeMatrix(std::vector<std::vector<int>> matrix) {
	std::vector<std::vector<int>> transposedMatrix(matrix[0].size(),std::vector<int>( matrix.size()));
	for (int i = 0; i < matrix.size(); i++) 
		for (int j = 0; j < matrix[i].size(); j++) 
			transposedMatrix[j][i] = matrix[i][j];
	return transposedMatrix;
}

void BidirectionalNN::initializeWeight(std::vector<std::vector<int>> X, std::vector<std::vector<int>> Y) {
	X = transposeMatrix(X);
	Weight = multiplyMatrices(X, Y);
	WeightTransposed = transposeMatrix(Weight);
}
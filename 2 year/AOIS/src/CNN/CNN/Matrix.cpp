#include "Matrix.h"

void Matrix::fillRand(std::vector<std::vector<double>>& matrix) {
    srand(time(NULL));
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[i].size(); j++)
            matrix[i][j] = ((std::rand() % 100)) * 0.03 / (matrix.size() + 35);
    //matrix[i][j] = 0.04;
}

std::vector<double> Matrix::multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    // Проверка на корректность размеров матрицы и вектора
    int num_rows = matrix.size();
    int num_cols = matrix[0].size();
    if (num_cols != vector.size()) {
        std::cout << "Can't myltiply 2\n";
    }

    // Инициализация результирующего вектора
    std::vector<double> result(num_rows, 0);

    // Умножение матрицы на вектор
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<double> Matrix::multiplyMatrixVector_T(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    // Проверка на корректность размеров матрицы и вектора
    int num_rows = matrix.size();
    int num_cols = matrix[0].size();
    if (num_rows != vector.size()) {
        std::cout << "Can't multiply\n";
    }

    // Инициализация результирующего вектора
    std::vector<double> result(num_cols, 0);

    // Умножение транспонированной матрицы на вектор
    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < num_rows; j++) {
            result[i] += matrix[j][i] * vector[j];
        }
    }

    return result;
}

std::vector<std::vector<double>> Matrix::extractSubMatrix(const std::vector<std::vector<double>>& matrix, int startRow, int startCol, int length) {
    if (startRow < 0 || startRow + length > matrix.size() || startCol < 0 || startCol + length > matrix[0].size()) {
        std::cout << "ERROR EXTRACTING\n";
        return {};
    }

    std::vector<std::vector<double>> subMatrix(length, std::vector<double>(length));

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            subMatrix[i][j] = matrix[startRow + i][startCol + j];
        }
    }

    return subMatrix;
}
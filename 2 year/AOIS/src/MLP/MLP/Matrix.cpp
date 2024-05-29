#include "Matrix.h"

void Matrix::fillRand(std::vector<std::vector<double>>& matrix) {
    srand(time(NULL));
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[i].size(); j++)
            matrix[i][j] = ((std::rand() % 100)) * 0.03 / (matrix.size() + 35);
    //matrix[i][j] = 0.04;
}

std::vector<std::pair<double, double>> Matrix::multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<std::pair<double, double>>& vector) {
    // Проверка на корректность размеров матрицы и вектора
    int num_rows = matrix.size();
    int num_cols = matrix[0].size();
    if (num_cols != vector.size()) {
        std::cout << "Can't myltiply 1\n";
    }

    // Инициализация результирующего вектора
    std::vector<std::pair<double, double>> result(num_rows, std::pair<double, double>(0, 0));

    // Умножение матрицы на вектор
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            result[i].first += matrix[i][j] * vector[j].second;
        }
    }

    return result;
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


std::vector<std::pair<double, double>> Matrix::summ(const std::vector<std::pair<double, double>>& vector1, const std::vector<double>& vector2) {
    // Проверка на корректность размеров векторов
    int size1 = vector1.size();
    int size2 = vector2.size();
    if (size1 != size2) {
        throw std::invalid_argument("Несовместимые размеры векторов!");
    }

    // Инициализация результирующего вектора
    std::vector<std::pair<double, double>> result(size1);

    // Сложение векторов
    for (int i = 0; i < size1; i++) {
        result[i].first = vector1[i].first + vector2[i];
    }

    return result;
}

std::vector<std::pair<double, double>> Matrix::multiplyMatrixVector_T(const std::vector<std::vector<double>>& matrix, const std::vector<std::pair<double, double>>& vector) {
    // Проверка на корректность размеров матрицы и вектора
    int num_rows = matrix.size();
    int num_cols = matrix[0].size();
    if (num_rows != vector.size()) {
        std::cout << "Can't multiply\n";
    }

    // Инициализация результирующего вектора
    std::vector<std::pair<double, double>> result(num_cols, std::pair<double, double>(0, 0));

    // Умножение транспонированной матрицы на вектор
    for (int i = 0; i < num_cols; i++) {
        for (int j = 0; j < num_rows; j++) {
            result[i].first += matrix[j][i] * vector[j].first;
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
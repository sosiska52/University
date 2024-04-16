#include <iostream>
#include <random>
#include "BidirectionalNN.h"

void printMatrix(std::vector<std::vector<double>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++)
			std::cout << matrix[i][j] << "\t";
		std::cout << "\n";
	}
}

void corruptVec(int corruptions, std::vector <double>& vec){
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = 0; i < corruptions; i++) {
		std::uniform_int_distribution<> dis(0, vec.size() - 1);
		vec[dis(gen)] *= -1;
	}
}

std::vector<std::vector<double>> generateRandomVector(int n) {
	std::vector<double> result;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1);

	for (int i = 0; i < n; i++) {
		int randomValue = dis(gen);
		if (randomValue == 0)
			randomValue = -1;
		result.push_back(randomValue);
	}

	return { result };
}

int efficiency(std::vector<std::vector<double>> vec1, std::vector<std::vector<double>> vec2) {
	int counter = 0;
	for (int i = 0; i < vec1[0].size(); i++) {
		if (vec1[0][i] != vec2[0][i])
			counter++;
	}
	return counter;
}

int main()
{
	
	int n = 12;
	int m = 8;
	BidirectionalNN neuronN(n, m);
	std::vector <std::vector <double>> X(3, std::vector<double>(n));
	std::vector <std::vector <double>> Y(3, std::vector<double>(m));

	X = {
		{-1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1},
		{1,1,1,1,-1,-1,-1,-1,1,1,1,1},
		{1,1,1,-1,-1,-1,1,1,1,-1,-1,-1}
	};
	Y = {
		{1,1,1,1,-1,-1,-1,-1},
		{-1,-1,-1,-1,1,1,1,1},
		{1,1,1,-1,-1,-1,1,1}
	};

	neuronN.initializeWeight(X, Y);
	std::vector <std::vector <double>> curVec(1, std::vector <double>());
	for (int i = 0; i < X.size(); i++) {
		curVec[0] = X[i];
		printMatrix(neuronN.function(true, curVec));
	}
	std::cout << "\n";
	for (int i = 0; i < Y.size(); i++) {
		curVec[0] = Y[i];
		printMatrix(neuronN.function(false, curVec));
	}
	std::cout << "\n";

	for (int i = 0; i < n; i++) {
		curVec = generateRandomVector(n);
		std::cout << "Original X vector:\n";
		printMatrix(curVec);
		std::cout << "Result:\n";
		std::vector <std::vector <double>> result = neuronN.function(true, curVec);
		printMatrix(result);
		corruptVec(i + 1,curVec[0]);
		std::cout << "Corrupted with " << i + 1 << " bits X vector : \n";
		printMatrix(curVec);
		std::cout << "Result:\n";
		std::vector <std::vector <double>> corrResult = neuronN.function(true, curVec);
		printMatrix(corrResult);
		std::cout << "Recognition efficiency:\n" << efficiency(result, corrResult) << "\n\n";
	}
}
#include <iostream>
#include "BidirectionalNN.h"

void printMatrix(std::vector<std::vector<int>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++)
			std::cout << matrix[i][j] << " ";
		std::cout << "\n";
	}
}

int main()
{
	
	int n = 12;
	int m = 8;
	BidirectionalNN neuronN(n, m);
	std::vector <std::vector <int>> X(3, std::vector<int>(n));
	std::vector <std::vector <int>> Y(3, std::vector<int>(m));

	X = {
		{0,0,0,0,1,1,1,1,0,0,0,0},
		{1,1,1,1,0,0,0,0,1,1,1,1},
		{1,1,1,0,0,0,1,1,1,0,0,0}
	};
	Y = {
		{1,1,1,1,0,0,0,0},
		{0,0,0,0,1,1,1,1},
		{1,1,1,0,0,0,1,1}
	};
	
	/*
	int n = 3;
	int m = 4;
	BidirectionalNN neuronN(n, m);
	std::vector <std::vector <int>> X(2, std::vector<int>(n));
	std::vector <std::vector <int>> Y(2, std::vector<int>(m));

	X = {
		{-1,1,-1},
		{1,-1,1}
	};
	Y = {
		{-1,1,-1,-1},
		{1,-1,1,1}
	};
	*/
	neuronN.initializeWeight(X, Y);
	std::vector <std::vector <int>> curVec(1, std::vector <int>());
	std::vector <std::vector <int>> result;
	for (int i = 0; i < 3; i++) {
		curVec[0] = X[i];
		result = neuronN.function(true, curVec);
		printMatrix(result);
	}
}
#include <iostream>
#include "ADALINE.h"

double function(double x) {
	return 4 * std::sin(x * 7) + 0.2;
}

int main()
{
	int n = 4;
	int m = 300;
	std::vector <std::vector<std::pair<double,double>>> trainSample(m / n, std::vector<std::pair<double,double>>(n));
	std::vector<std::pair<double, double>> testSample(m / 2, std::pair<double, double>());

	double temp = 0;
	for (int i = 0; i < trainSample.size(); i++) {
		for (int j = 0; j < trainSample[i].size(); j++) {
			trainSample[i][j].first = temp;
			trainSample[i][j].second = function(trainSample[i][j].first);
			temp += 0.1;
		}
	}

	ADALINE adaline(n);
	std::ofstream referenceFile("reference.txt");
	std::ofstream resultFile("result.txt");
	int counter = 0;
	double minError = 99999;
	for (int i = 0; i < testSample.size(); i++) {
			testSample[i].first = temp;
			testSample[i].second = function(testSample[i].first);
			temp += 0.1;
			referenceFile << testSample[i].first + 0.1 << " " << function(testSample[i].first + 0.1) << "\n";
	}

	adaline.predict(trainSample, testSample);

	return 0;
}
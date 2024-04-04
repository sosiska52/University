#include <iostream>
#include "ADALINE.h"

double function(double x) {
	return 3 * std::sin(x * 7) + 0.3;
}

int main()
{
	int n = 5;
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
	//adaline.train(trainSample);
	//adaline.load();
	std::ofstream referenceFile("reference.txt");
	std::ofstream resultFile("result.txt");
	int counter = 0;
	double minError = 99999;
	std::cout << "\n\n\n";
	for (int i = 0; i < testSample.size(); i++) {
			testSample[i].first = temp;
			testSample[i].second = function(testSample[i].first);
			temp += 0.1;
			referenceFile << testSample[i].first + 0.1 << " " << function(testSample[i].first + 0.1) << "\n";

		/*double res = std::abs(adaline.predict(testSample[i]) - function(testSample[i][n - 1].first + 0.1));
		std::cout << std::setw(5) << std::left << i 
			<< std::setw(13) << std::left << adaline.predict(testSample[i])
			<< std::setw(13) << std::left << function(testSample[i][n - 1].first + 0.1)
			<< std::setw(13) << std::left << res << "\n";

		resultFile << testSample[i][n - 1].first + 0.1 << " " << adaline.predict(testSample[i]) << "\n";
		if (res > 0.0183)
			counter++;
		if (minError > res)
			minError = res;*/
	}

	adaline.predict(trainSample, testSample);

	return 0;
}
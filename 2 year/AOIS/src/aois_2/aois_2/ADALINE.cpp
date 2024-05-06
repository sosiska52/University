#include "ADALINE.h"

double ADALINE::function(double x) {
	return 4 * std::sin(x * 7) + 0.2;
}

double ADALINE::getRandomNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.1, 1.0);
	return dis(gen);  
}

ADALINE::ADALINE(int n) {
	this->n = n;
	W = std::vector <double>(n);
	T = getRandomNumber();
	alphaSpd = 0.04;
	minMistake = 1e-8;
	for (int i = 0; i < n; i++) {
		W[i] = getRandomNumber();
	}
}

double ADALINE::calculateY() {
	double res = 0;
	for (int i = 0; i < W.size(); i++)
		res += W[i] * X[i].second;
	return res - T;
}

void ADALINE::adjustWeight(int ind, double Y, double referense){
	W[ind] -= alphaSpd * (Y - referense) * X[ind].second;
}

void ADALINE::adjustThreshhold(double Y, double referense) {
	T += alphaSpd * (Y - referense);
}

double ADALINE::calculateError(double Y, double referense) {
	return 0.5 * std::pow(Y - referense, 2);
}

void ADALINE::train(std::vector <std::vector<std::pair<double, double>>> trainSample) {
	for (int i = 0; i < trainSample.size(); i++) {
		X = trainSample[i];
		double reference = function(X[n - 1].first + 0.1);
		double Y = calculateY();

		for (int i = 0; i < W.size(); i++)
			adjustWeight(i, Y, reference);
		adjustThreshhold(Y, reference);
	}
}

bool ADALINE::test(std::vector<std::pair<double, double>> testSample) {
	double sumMistake = 0;
	int start = 0;
	std::vector<std::pair<double, double>> result(testSample.size());
	std::vector <std::pair<double, double>> temp;
	for (int i = 0; i < testSample.size() && start < testSample.size() - n; i++) {
		temp = std::vector <std::pair<double, double>>();
		for (int j = start; j < n + start; j++) {
			temp.push_back(testSample[j]);
		}
		start++;
		X = temp;
		double reference = function(X[n - 1].first + 0.1);
		double Y = calculateY();
		sumMistake += calculateError(Y, reference);
		result[i].first = X[n - 1].first + 0.1;
		result[i].second = Y;
	}
	sumMistake *= 0.5;
	std::cout << "sum mistake: " << sumMistake << "\n";
	if (sumMistake > minMistake)
		return false;
	else {
		std::ofstream fout("result.txt");
		for (int i = 0; i < result.size(); i++)
			fout << result[i].first << " " << result[i].second << "\n";
		fout.close();
		return true;
	}
}

void ADALINE::predict(std::vector <std::vector<std::pair<double, double>>> trainSample, std::vector<std::pair<double, double>> testSample) {
	train(trainSample);
	while (!test(testSample)) {
		train(trainSample);
	}
}
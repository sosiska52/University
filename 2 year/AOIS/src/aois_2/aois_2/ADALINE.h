#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <iomanip>
class ADALINE
{
private:
	int n;
	std::vector <double> W;
	std::vector <std::pair<double, double>> X;
	double T;
	double alphaSpd;
	double minMistake;
	double function(double x);
	double getRandomNumber();
	double calculateY();
	void adjustWeight(int ind,double Y, double referense);
	void adjustThreshhold(double Y, double referense);
	double calculateError(double y, double referense);
	void train(std::vector <std::vector<std::pair<double, double>>>);
	bool test(std::vector<std::pair<double, double>>);
public:
	ADALINE(int n);
	void predict(std::vector <std::vector<std::pair<double, double>>>, std::vector<std::pair<double, double>>);
	void save();
	void load();
};


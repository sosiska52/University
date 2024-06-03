#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"

class ConvNetwork
{
public:
	struct Mnist_data {
		int label;
		std::vector<double> pixels;

		static const int numImages = 10000;
		static const int imageSize = 16;
		Mnist_data() {
			pixels = std::vector<double>(784);
		}
	};
private:
	/*
	std::vector<double> inputNeuron;
	std::vector<std::vector<double>> hidenNeuron1;
	std::vector<std::vector<double>> hidenNeuron2;
	std::vector<double> outputNeuron;

	std::vector<std::vector<double>> kernel1;
	std::vector<std::vector<double>> kernel2;
	*/

	std::vector<std::vector<double>> inputNeuron;
	std::vector<std::vector<std::vector<double>>> hidenNeuron1;
	std::vector<std::vector<std::vector<double>>> hidenNeuron2;
	std::vector<double> outputNeuron;

	std::vector<std::vector<std::vector<double>>> kernel1;
	std::vector<std::vector<std::vector<double>>> kernel2;

	void ReLUFunc(std::vector<double>& vec);
	double ReLUDer(double num);
	void ReLUDer(std::vector<double>& vec);

	void givePicture(Mnist_data& image);
	int findMaxOutput();

	double maxPooling();
	void backPropogation(double expected, double alph);
public:
	ConvNetwork();

	int predict(Mnist_data&);

	void train(std::vector<Mnist_data>& images);
	void test(std::vector<Mnist_data>& images);

	void saveWeight();
	void loadWeight();
};


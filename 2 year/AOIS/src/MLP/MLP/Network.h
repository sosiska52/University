#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Matrix.h"

class Network{
public:
	struct Cifar_data {
		unsigned char label;
		std::vector<unsigned char> pixels;

		static const int numImages = 10000;
		static const int imageSize = 3072;
		static const int labelSize = 1;
		static const int channelSize = 1024;
	};

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
	int numOfLayers;
	std::vector <int> sizeOfLayer;
	std::vector<std::vector<std::vector<double>>> weight;
	std::vector<std::vector<double>> neuronVal;
	std::vector<std::vector<double>> activatedVal;
	std::vector<std::vector<double>> neuronErr;

	void activationFunc(std::vector<double>&, std::vector<double>&);
	double activationDer(double);
	void activationDer(std::vector<double>&, std::vector<double>&);

	void backPropogation(double expect, double alph);
	void givePicture(Mnist_data);
	void givePicture(Cifar_data);
	int findMax();

public:
	Network();
	void train(std::vector<Mnist_data>& images);
	void test(std::vector<Mnist_data>& images);
	void train(std::vector<Cifar_data>& images);
	void test(std::vector<Cifar_data>& images);
	void loadWeight();
	void saveWeight();
	int predict();

	void printVector();
};


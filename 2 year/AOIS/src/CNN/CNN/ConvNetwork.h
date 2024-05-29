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
	std::vector<int> sizeOfLayer;
	std::vector<std::vector<double>> neuronVal;
	void activationFunc(std::vector<double>& vec);
	double activationDer(double num);
	void activationDer(std::vector<double>& vec);

	void givePicture(Mnist_data image);
	int findMaxOutput();

	double maxPooling();

public:
	ConvNetwork();
	void saveWeight();
	void loadWeight();
};


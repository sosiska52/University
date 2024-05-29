#include "ConvNetwork.h"

void ConvNetwork::activationFunc(std::vector<double>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] < 0)
			vec[i] *= 0.01;
		if (vec[i] > 1)
			vec[i] = 1. + 0.01 * (vec[i] - 1.);
	}
}
double ConvNetwork::activationDer(double val) {
	if (val < 0 || val > 1)
		val = 0.01;
	else
		val = 1.;
	return val;
}
void ConvNetwork::activationDer(std::vector<double>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] < 0 || vec[i] > 1)
			vec[i] = 0.01;
		else
			vec[i] = 1.;
		//vec[i] = vec[i] * (1 - vec[i]);
	}
}

void ConvNetwork::givePicture(Mnist_data image) {
	for (int i = 0; i < inputNeuron.size(); i++)
		inputNeuron[i] = image.pixels[i];
}
int ConvNetwork::findMaxOutput() {
	double max = outputNeuron[0];
	int ind = 0;
	for (int i = 1; i < outputNeuron.size(); i++)
		if (max < outputNeuron[i]) {
			max = outputNeuron[i];
			ind = i;
		}
	return ind;
}

void ConvNetwork::saveWeight() {
	std::ofstream fout("weights.txt");
	if (!fout.is_open()) {
		std::cout << "Couldn't open file\n";
		fout.close();
		return;
	}

	std::cout << "START SAVING\n";
	for (int i = 0; i < weight.size(); i++) {
		for (int j = 0; j < weight[i].size(); j++) {
			for (int k = 0; k < weight[i][j].size(); k++) {
				fout << weight[i][j][k] << " ";
			}
			fout << "\n";
		}
		fout << "\n\n";
	}
	std::cout << "DONE SAVING\n";
	fout.close();
}
void ConvNetwork::loadWeight() {
	std::ifstream fin("weights.txt");
	if (!fin.is_open()) {
		std::cout << "Couldn't open file\n";
		fin.close();
		return;
	}

	std::cout << "START LOADING\n";
	for (int i = 0; i < weight.size(); i++)
		for (int j = 0; j < weight[i].size(); j++)
			for (int k = 0; k < weight[i][j].size(); k++)
				fin >> weight[i][j][k];

	std::cout << "DONE LOADING\n";
	fin.close();
}
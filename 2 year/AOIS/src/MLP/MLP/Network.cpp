#include "Network.h"

void Network::printVector() {
	for (int i = 0; i < 10; i++) {
		std::cout << neuronVal[2][i] << " ";
	}
	std::cout << "\n";
}

Network::Network() {
	numOfLayers = 3;

	sizeOfLayer = std::vector <int>(3);
	sizeOfLayer[0] = 784; 
	sizeOfLayer[1] = 392;
	sizeOfLayer[2] = 10;

	//numOfLayers = 3;

	//sizeOfLayer = std::vector <int>(numOfLayers);
	//sizeOfLayer[0] = 3072; 
	//sizeOfLayer[1] = 384;
	//sizeOfLayer[2] = 10;

	weight = std::vector<std::vector<std::vector<double>>>(numOfLayers - 1);

	for (int i = 0; i < numOfLayers - 1; i++) {
		weight[i] = std::vector<std::vector<double>>(sizeOfLayer[i + 1], std::vector<double>(sizeOfLayer[i]));
		Matrix::fillRand(weight[i]);
	}

	neuronVal = std::vector<std::vector<double>>(numOfLayers);
	activatedVal = std::vector<std::vector<double>>(numOfLayers);
	neuronErr = std::vector<std::vector<double>>(numOfLayers);


	for (int i = 0; i < numOfLayers; i++) {
		neuronVal[i] = std::vector<double>(sizeOfLayer[i]);
		neuronErr[i] = std::vector<double>(sizeOfLayer[i]);
		activatedVal[i] = std::vector<double>(sizeOfLayer[i]);
	}
}

void Network::givePicture(Mnist_data image) {
	for (int i = 0; i < sizeOfLayer[0]; i++)
		neuronVal[0][i] = image.pixels[i];
}

void Network::givePicture(Cifar_data image) {
	for (int i = 0; i < image.channelSize; i++) {
		neuronVal[0][i] = static_cast<double>(image.pixels[i]) / 255;
		neuronVal[0][i + image.channelSize] = static_cast<double>(image.pixels[i + image.channelSize]) / 255;
		neuronVal[0][i + image.channelSize * 2] = static_cast<double>(image.pixels[i + image.channelSize * 2] ) / 255;

		/*int red = static_cast<int>(image.pixels[i]);
		int green = static_cast<int>(image.pixels[i + image.channelSize]);
		int blue = static_cast<int>(image.pixels[i + image.channelSize] * 2);*/

		/*red = std::max(0, std::min(255, red));
		green = std::max(0, std::min(255, green));
		blue = std::max(0, std::min(255, blue));

		int rgb = (red << 16) + (green << 8) + blue;
		double drgb = static_cast<double>(rgb) / 16777215.0;*/

		//neuronVal[0][i] = drgb;
	}
}

int Network::predict() {
	neuronVal[1] = Matrix::multiplyMatrixVector(weight[0], neuronVal[0]);
	activationFunc(neuronVal[1], neuronVal[1]);

	neuronVal[2] = Matrix::multiplyMatrixVector(weight[1], neuronVal[1]);
	activationFunc(neuronVal[2], neuronVal[2]);
	//printVector(neuronVal[2]);
	return findMax();
}

int Network::findMax() {
	double max = neuronVal[2][0];
	int ind = 0;
	for (int i = 1; i < sizeOfLayer[2]; i++)
		if (max < neuronVal[2][i]) {
			max = neuronVal[2][i];
			ind = i;
		}
	return ind;
}

void Network::backPropogation(double expect, double alph) {
	for (int i = 0; i < sizeOfLayer[numOfLayers - 1]; i++) {
		if (i != int(expect))
			neuronErr[numOfLayers - 1][i] = -neuronVal[numOfLayers - 1][i] * activationDer(neuronVal[numOfLayers - 1][i]);
		else
			neuronErr[numOfLayers - 1][i] = (1.0 - neuronVal[numOfLayers - 1][i]) * activationDer(neuronVal[numOfLayers - 1][i]);
	}
	for (int k = numOfLayers - 2; k > 0; k--) {
		neuronErr[k] = Matrix::multiplyMatrixVector_T(weight[k], neuronErr[k + 1]);
		for (int j = 0; j < sizeOfLayer[k]; j++)
			neuronErr[k][j] *= activationDer(neuronVal[k][j]);
	}

	for (int i = 0; i < numOfLayers - 1; ++i) {
		for (int j = 0; j < sizeOfLayer[i + 1]; ++j) {
			for (int k = 0; k < sizeOfLayer[i]; ++k) {
				weight[i][j][k] += neuronVal[i][k] * neuronErr[i + 1][j] * alph;
			}
		}
	}
}

void Network::train(std::vector<Mnist_data>& images) {
	int epoch = 0;
	double errPercent = 100;
	while (errPercent > 5. && epoch < 20) {
		auto start = std::chrono::steady_clock::now();
		int ra = 0;
		for (int i = 0; i < images.size(); i++) {
			int referense = static_cast<int>(images[i].label);
			givePicture(images[i]);
			int result = predict();
			if (result != referense) {
				backPropogation(referense, 0.2 * exp(-epoch / 20.));
			}
			else {
				std::cout << i << "\n";
				//std::cout << "photo_" << i << " " << referense << " - " << result << "\n";
				//printVector();
				ra++;
			}
		}
		errPercent = 100 - (static_cast<double>(ra) / images.size() * 100);
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		//system("cls");
		std::cout << "Epoch " << epoch << " err percent: " << errPercent << " time: " << duration.count() << "\n";
		epoch++;
	}
}

void Network::train(std::vector<Cifar_data>& images) {
	int epoch = 0;
	double errPercent = 100;
	while (errPercent > 1. && epoch < 20) {
		auto start = std::chrono::steady_clock::now();
		int ra = 0;
		for (int i = 0; i < images.size(); i++) {
			int referense = static_cast<int>(images[i].label);
			givePicture(images[i]);
			int result = predict();
			if (result != referense) {
				backPropogation(referense, 0.2 * exp(-epoch / 20.));
			}
			else {
				std::cout << "photo_" << i << " " << referense << " - " << result << "\n";
				printVector();
				ra++;
			}
		}
		errPercent = 100 - (static_cast<double>(ra) / images.size() * 100);
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		system("cls");
		std::cout << "Epoch " << epoch << " err percent: " << errPercent << " time: " << duration.count() << "\n";
		epoch++;
	}
}

void Network::test(std::vector<Mnist_data>& images) {
	double error = 0;
	for (int i = 0; i < images.size(); i++) {
		givePicture(images[i]);
		int result = predict();
		if (result != images[i].label){
			std::cout << i << "\n";
			error += 1.;
		}
	}
	double errPercent = error / images.size() * 100;
	std::cout << "Test\nError percent: " << errPercent << "\n";
}

void Network::test(std::vector<Cifar_data>& images) {
	double error = 0;
	for (int i = 0; i < images.size(); i++) {
		givePicture(images[i]);
		int result = predict();
		if (result != images[i].label)
			error += 1.;
	}
	double errPercent = error / images.size() * 100;
	std::cout << "Test\nError percent: " << errPercent << "\n";
}

void Network::activationFunc(std::vector<double>& from, std::vector<double>& to) {
	for (int i = 0; i < from.size(); i++) {
		if (from[i] < 0)
			to[i] *= 0.01;
		if (from[i] > 1)
			to[i] = 1. + 0.01 * (from[i] - 1.);
		//vec[i].second = 1 / (1 + exp(-vec[i].first));
	}
}

double Network::activationDer(double num) {
	double val = num;
	if (val < 0 || val > 1)
		val = 0.01;
	else
		val = 1.;
	return val;
	//return val * (1 - val);
}

void Network::activationDer(std::vector<double>& from, std::vector<double>& to) {
	for (int i = 0; i < from.size(); i++) {
		if (from[i] < 0 || from[i] > 1)
			to[i] = 0.01;
		else
			to[i] = 1.;
		//vec[i] = vec[i] * (1 - vec[i]);
	}
}

void Network::saveWeight() {
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

void Network::loadWeight() {
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
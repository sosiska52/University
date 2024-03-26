#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <Eigen/Dense>
class Hill {
private:
	int size;
	int numOfLetters;
	char fillerLetter;
	char textLimiter;
	std::vector<std::vector <int>> key;

	int getAlphabetPosition(char letter);
	int getRandomNumber();

	std::vector<int> transformToNumbers(std::string);
	std::vector<int> encrypt(std::vector<int>);
	void saveEncryptedText(std::string, std::vector<int>);


public:
	Hill();
	void encryptText(std::string& path);
	void decryptText(std::string& path);;
};


#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
class Hill {
private:
	int size;
	int numOfLetters;
	char fillerLetter;
	char textLimiter;
	std::vector<std::vector <int>> enkey;
	std::vector<std::vector <int>> dekey;

	int getRandomNumber();

	std::vector<int> transformToNumbers(std::string);
	std::vector<int> encrypt(std::vector<int>, bool);
	void saveEncryptedText(std::string, std::vector<int>);
	void cleanFile(std::string);
	int getAlphabetPosition(char letter);
	char getAlphabetLetter(int num);

	void cryptText(std::string& path, bool mode);

public:
	Hill();
	void encryptText(std::string& path);
	void decryptText(std::string& path);
};


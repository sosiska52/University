#pragma once
#include <vector>
#include <bitset>
#include <string>
#include <iostream>
#include <fstream>

class CBCTable
{
private:
	std::vector<std::vector<std::string>> translationTable;

	std::string charToBinary(char character);
	char binaryToChar(const std::string& binaryString);
	std::string applyXor(const std::string& binaryString1, const std::string& binaryString2);
	std::string encryptThroughTable(std::string);
	std::string decryptThroughTable(std::string);
public:
	CBCTable();
	void encryptStandard(std::string path);
	void decryptStandard(std::string path);
	void encryptDouble(std::string path); //двойное шифрование
	void decryptDouble(std::string path);
};


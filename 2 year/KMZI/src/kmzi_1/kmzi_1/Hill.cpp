#include "Hill.h"
#include <fstream>
#include <vector>
#include <string>
#include <random>

class Hill {
private:
	int size;
	std::vector<std::vector <int>> key;
	std::vector<int> originalTextMatrix;
	std::vector<int> encryptedTextMatrix;
	std::string originalText;
	std::string encryptedText;

	int getAlphabetPosition(char letter) {
		letter = std::toupper(letter);
		int asciiCode = static_cast<int>(letter);
		int alphabetPosition = asciiCode - 64;
		return alphabetPosition;
	}

	int getRandomNumber() {
		std::random_device rd;  // ������������� ���������� ��������� �����
		std::mt19937 gen(rd());  // ��������� ��������� �����
		std::uniform_int_distribution<int> dis(0, 25);  // ����������� ������������� �� 1 �� 25

		return dis(gen);  // ���������� ��������� �����
	}
public:
	Hill() {
		size = 10;
		key = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
		originalTextMatrix = std::vector<int>(size, 0);
		encryptedTextMatrix = std::vector<int>(size, 0);

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				key[i][j] = getRandomNumber();
			}
		}
	}

	void encryptText(std::string path) {
		std::ifstream fin;
	}
};
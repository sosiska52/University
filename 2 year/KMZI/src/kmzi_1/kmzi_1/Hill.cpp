#include "Hill.h"

int Hill::getAlphabetPosition(char letter) {
	if (letter == '.')
		return 26;
	if (letter == ',')
		return 27;
	if (letter == '-')
		return 28;
	if (letter == '\n')
		return 29;
	if (letter == ' ')
		return 30;

	letter = std::toupper(letter);
	int asciiCode = static_cast<int>(letter);
	int alphabetPosition = asciiCode - 64;
	return alphabetPosition;
}

int Hill::getRandomNumber() {
	std::random_device rd;  // Инициализация генератора случайных чисел
	std::mt19937 gen(rd());  // Генератор случайных чисел
	std::uniform_int_distribution<int> dis(0, numOfLetters);  // Равномерное распределение от 1 до 25

	return dis(gen);  // Возвращаем случайное число
}

Hill::Hill() {
	size = 10;
	numOfLetters = 30;
	fillerLetter = '.';
	textLimiter = ';';
	key = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			key[i][j] = getRandomNumber();
		}
	}
}

void Hill::encryptText(std::string& path) {
	std::ifstream fin;
	fin.open(path);

	if (!fin.is_open()) {
		std::cout << "Failed to open file: " << path << std::endl;
		return;
	}

	std::string line;
	std::string foutPath = "encrypted.txt";

	while (std::getline(fin, line,textLimiter)) {
		if (line.length() >= size) {
			for (size_t i = 0; i < line.length(); i += size) {
				std::string substr = line.substr(i, size);

				if (substr.length() == size)
					saveEncryptedText(foutPath,encrypt(transformToNumbers(substr)));
				else {
					substr.append(size - substr.length(), fillerLetter);
					saveEncryptedText(foutPath, encrypt(transformToNumbers(substr)));
				}
			}
		}
		else {
			line.append(64 - line.length(), fillerLetter);
			saveEncryptedText(foutPath, encrypt(transformToNumbers(line)));
		}
	}
	
	fin.close();
}

std::vector<int> Hill::transformToNumbers(std::string str) {
	std::vector <int> res(str.size());
	for (int i = 0; i < str.size(); i++) {
		res[i] = getAlphabetPosition(str[i]);
	}
	return res;
}

std::vector<int> Hill::encrypt(std::vector<int> origText) {
	std::vector <int> res(origText.size());

	for (int i = 0; i < origText.size(); i++) {
		for (int j = 0; j < origText.size(); j++) {
			res[i] += key[i][j] * origText[j];
		}
	}

	return res;
}

void Hill::saveEncryptedText(std::string path, std::vector<int> encryptedText) {
	std::ofstream fout;
	fout.open(path, std::ios::app);
	for (int i = 0; i < encryptedText.size(); i++) {
		fout << encryptedText[i] << " ";
	}
	fout.close();
}

void Hill::decryptText(std::string& path) {
	std::ifstream fin;
	fin.open(path);

	if (!fin.is_open()) {
		std::cout << "Failed to open file: " << path << std::endl;
		return;
	}

	std::vector <int> encryptedText(size);
	int number;
	int counter = 0;
	while (fin >> number) {
		encryptedText[counter] = number;
		counter++;

		if (counter == size) {
			counter = 0;
			//
			encryptedText = std::vector <int>(size);
		}
	}

	fin.close();
}
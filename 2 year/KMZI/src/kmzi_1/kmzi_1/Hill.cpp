#include "Hill.h"

int Hill::getAlphabetPosition(char letter) {
	if (letter == '.')
		return 25;
	if (letter == ',')
		return 26;
	if (letter == '-')
		return 27;
	if (letter == ' ')
		return 28;

	letter = std::toupper(letter);
	int asciiCode = static_cast<int>(letter);
	int alphabetPosition = asciiCode - 65;
	return alphabetPosition;
}

char Hill::getAlphabetLetter(int num) {
	if (num < 0) {
		num += 29;
	}
	if (num > -1 && num < 25)
		return 'A' + num;
	if (num == 25)
		return '.';
	if (num == 26)
		return ',';
	if (num == 27)
		return '-';
	if (num == 28)
		return ' ';

	return '*';
}

int Hill::getRandomNumber() {
	std::random_device rd;  // Инициализация генератора случайных чисел
	std::mt19937 gen(rd());  // Генератор случайных чисел
	std::uniform_int_distribution<int> dis(0, numOfLetters);  // Равномерное распределение от 1 до 25

	return dis(gen);  // Возвращаем случайное число
}

Hill::Hill() {
	size = 2;
	numOfLetters = 29;
	fillerLetter = '.';
	textLimiter = ';';
	enkey = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));

	/*for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			enkey[i][j] = getRandomNumber();
		}
	}*/

	enkey[0][0] = 4;
	enkey[0][1] = 5;
	enkey[1][0] = 3;
	enkey[1][1] = 4;

	dekey = enkey;
	dekey[0][1] *= -1;
	dekey[1][0] *= -1;
}

void Hill::encryptText(std::string& path) {
	cryptText(path, true);
}

std::vector<int> Hill::transformToNumbers(std::string str) {
	std::vector <int> res(str.size());
	for (int i = 0; i < str.size(); i++) {
		res[i] = getAlphabetPosition(str[i]);
	}
	return res;
}

std::vector<int> Hill::encrypt(std::vector<int> origText, bool mode) {
	//mode true = encrypt
	//mode false = decrypt
	std::vector <int> res(origText.size());
	if (mode) {
		for (int i = 0; i < origText.size(); i++) {
			for (int j = 0; j < origText.size(); j++) {
				res[i] += enkey[i][j] * origText[j];
			}
			res[i] = res[i] % numOfLetters;
		}
	}
	else {
		for (int i = 0; i < origText.size(); i++) {
			for (int j = 0; j < origText.size(); j++) {
				res[i] += dekey[i][j] * origText[j];
			}
			res[i] = res[i] % numOfLetters;
		}
	}
	
	return res;
}

void Hill::saveEncryptedText(std::string path, std::vector<int> encryptedText) {
	std::ofstream fout;
	fout.open(path, std::ios::app);
	for (int i = 0; i < encryptedText.size(); i++) {
		fout << getAlphabetLetter(encryptedText[i]);
	}
	fout.close();
}

void Hill::cleanFile(std::string path) {
	std::ofstream file(path);
	file.close();
}

void Hill::decryptText(std::string& path) {
	cryptText(path, false);
}

void Hill::cryptText(std::string& path, bool mode) {
	//true = encrypt
	//false = decrypt
	std::string foutPath;
	bool subMode;
	if (mode) {
		foutPath = "encrypted.txt";
		subMode = true;
	}
	else {
		foutPath = "decrypted.txt";
		subMode = false;
	}
	std::ifstream fin;
	fin.open(path);

	if (!fin.is_open()) {
		std::cout << "Failed to open file: " << path << std::endl;
		return;
	}

	std::string line;
	cleanFile(foutPath);

	while (std::getline(fin, line, textLimiter)) {
		if (line.length() >= size) {
			for (size_t i = 0; i < line.length(); i += size) {
				std::string substr = line.substr(i, size);

				if (substr.length() == size)
					saveEncryptedText(foutPath, encrypt(transformToNumbers(substr), subMode));
				else {
					substr.append(size - substr.length(), fillerLetter);
					saveEncryptedText(foutPath, encrypt(transformToNumbers(substr), subMode));
				}
			}
		}
		else {
			line.append(63 - line.length(), fillerLetter);
			saveEncryptedText(foutPath, encrypt(transformToNumbers(line), subMode));
		}
	}
	std::ofstream fout(foutPath, std::ios::app);
	fout << ";";
	fin.close();
}
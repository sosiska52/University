#include "Huffman.h"

Huffman::Huffman() {
	alphabetSize = 26;
	alphabet = std::vector <node*>();
	for (int i = 0; i < alphabetSize; i++) {
		node* newNode = new node(i);
		alphabet.push_back(newNode);
	}

	alphabet[0]->chance = 817;
	alphabet[1]->chance = 149;
	alphabet[2]->chance = 278;
	alphabet[3]->chance = 425;
	alphabet[4]->chance = 1270;
	alphabet[5]->chance = 223;
	alphabet[6]->chance = 202;
	alphabet[7]->chance = 609;
	alphabet[8]->chance = 697;
	alphabet[9]->chance = 15;
	alphabet[10]->chance = 77;
	alphabet[11]->chance = 403;
	alphabet[12]->chance = 241;
	alphabet[13]->chance = 675;
	alphabet[14]->chance = 751;
	alphabet[15]->chance = 193;
	alphabet[16]->chance = 10;
	alphabet[17]->chance = 599;
	alphabet[18]->chance = 633;
	alphabet[19]->chance = 906;
	alphabet[20]->chance = 276;
	alphabet[21]->chance = 98;
	alphabet[22]->chance = 236;
	alphabet[23]->chance = 15;
	alphabet[24]->chance = 197;
	alphabet[25]->chance = 7;
	encodedLetters = std::vector<std::string>(alphabet.size(), "");
	encodeLetters();
}

std::pair<int, int> Huffman::find2minId(std::vector<node*>& vec) {
	std::pair <int, int> minId = { -1, -1 };
	std::pair <int, int> minChance = { 99999, 99999 };
	int temp = -1;
	for (int i = 0; i < vec.size(); i++) {
		if (!vec[i]->isUsed && vec[i]->chance < minChance.first && i != temp) {
			minChance.first = vec[i]->chance;
			minId.first = i;
			temp = i;
		}
	}
	for (int i = 0; i < vec.size(); i++) {
		if (!vec[i]->isUsed && vec[i]->chance < minChance.second && i != temp) {
			minChance.second = vec[i]->chance;
			minId.second = i;
		}
	}
	return minId;
}

void Huffman::encodeLetters() {
	std::vector <node*> tempVector;
	tempVector = alphabet;
	std::pair <int, int> minId = { -1, -1 };

	while(true){
		minId = find2minId(tempVector);

		if (minId.first == -1 || minId.second == -1) {
			break;
		}

		tempVector[minId.first]->isUsed = true;
		tempVector[minId.second]->isUsed = true;
		node* newNode = new node(tempVector.size());
		tempVector[minId.first]->next = newNode;
		tempVector[minId.second]->next = newNode;
		newNode->prev1 = tempVector[minId.first];
		newNode->prev2 = tempVector[minId.second];
		newNode->chance = tempVector[minId.first]->chance + tempVector[minId.second]->chance;
		tempVector.push_back(newNode);
		minId = { -1, -1 };
	}

	for (int i = 0; i < alphabet.size(); i++) {
		encodeHelper(tempVector[i], encodedLetters[i]);
		//encodedLetters[i] = encodedLetters[i].substr(0, encodedLetters[i].length() / 2);
		std::reverse(encodedLetters[i].begin(), encodedLetters[i].end());
		std::cout << tempVector[i]->letter << " " << encodedLetters[i] << "\n";
	}
}

void Huffman::encodeHelper(node* cur, std::string& res) {
	if (cur->next == nullptr)
		return;

	node* nextNode = cur->next;
	if (nextNode->prev1 >= nextNode->prev2) {
		if (nextNode->prev1->letter == cur->letter)
			res += '1';
		else if (nextNode->prev2->letter == cur->letter)
			res += '0';
	}
	else if (nextNode->prev1 < nextNode->prev2) {
		if (nextNode->prev1->letter == cur->letter)
			res += '0';
		else if (nextNode->prev2->letter == cur->letter)
			res += '1';
	}
	encodeHelper(nextNode, res);
}

std::string Huffman::encodeLetter(char letter) {
	for (int i = 0; i < alphabetSize; i++) {
		if (alphabet[i]->letter == letter)
			return encodedLetters[i];
	}
	return "*-*";
}

void Huffman::compressData(std::string path) {
	std::ifstream fin(path);
	std::ofstream fout("compressed.txt");
	if (!fin.is_open()) {
		std::cout << "File don't exist\n";
		fin.close();
		return;
	}

	char letter;
	while (fin.get(letter)) {
		fout << encodeLetter(letter);
	}

	fin.close();
	fout.close();
}

char Huffman::decodeLetter(std::string str) {
	for (int i = 0; i < alphabetSize; i++) {
		if (encodedLetters[i] == str)
			return alphabet[i]->letter;
	}
	return '*';
}

void Huffman::decompressData(std::string path) {
	std::ifstream fin(path);
	std::ofstream fout("decompressed.txt");
	if (!fin.is_open()) {
		std::cout << "File don't exist\n";
		fin.close();
		return;
	}

	char number;
	std::string tempstr = "";
	while (fin.get(number)) {
		tempstr += number;
		char foundLetter = decodeLetter(tempstr);
		if (foundLetter != '*') {
			fout << foundLetter;
			tempstr = "";
		}
	}

	fin.close();
	fout.close();
}
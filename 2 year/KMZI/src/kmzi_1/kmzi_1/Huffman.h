#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
class Huffman
{
private:
	struct node {
		char letter;
		int chance;
		node* next;
		node* prev1;
		node* prev2;
		bool isUsed;
		node(int i) {
			letter = 'A' + i;
			chance = NULL;
			next = nullptr;
			prev1 = nullptr;
			prev2 = nullptr;
			isUsed = false;
		}
	};
	int alphabetSize;
	std::vector <node*> alphabet;
	std::vector <std::string> encodedLetters;

	void encodeLetters();
	void encodeHelper(node*, std::string&);
	std::string encodeLetter(char);
	char decodeLetter(std::string);
	std::pair<int, int> find2minId(std::vector<node*>&);
public:
	Huffman();
	void compressData(std::string path);
	void decompressData(std::string path);
};


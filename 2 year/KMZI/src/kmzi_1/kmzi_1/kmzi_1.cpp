#include <iostream>
#include "Hill.h"
#include "Huffman.h"

int main()
{
	
	Hill hill;
	std::string name = "test.txt";
	std::string foutPath = "encrypted.txt";
	hill.encryptText(name);
	hill.decryptText(foutPath);
	

	Huffman haffman;
	haffman.compressData("task2.txt");
	haffman.decompressData("compressed.txt");
	return 0;
}
#include <iostream>
#include "Hill.h"

int main()
{
	Hill hill;
	std::string name = "test.txt";
	std::string foutPath = "encrypted.txt";
	hill.encryptText(name);
	hill.decryptText(foutPath);
	return 0;
}
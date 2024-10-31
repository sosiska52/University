#pragma once
#include "RipeMD160_Hash.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>
#include <cmath>
#include <functional>
#include <iomanip>
#include <sstream>
#include <cstdint>

class ShnorDigitalSignature
{
public:
	ShnorDigitalSignature();
	std::pair <unsigned long long, unsigned long long> sign(const std::string& message);
	bool verify(std::pair<unsigned long long, unsigned long long> signature, const std::string& massage);
private:
	unsigned long long p;
	unsigned long long q;
	unsigned long long g;
	//RIPEMD160 hashFunc;
	unsigned long long x;
	unsigned long long y;

	long long randomInRange(int min, int max);
	bool isPrime(int num);
	int modInverse(int a, int m);
	int modExp(int base, int exp, int mod);
	unsigned long long hashFunction(int r, const std::string& message);
};


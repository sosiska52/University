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
	unsigned long long p; //public
	unsigned long long q; //public
	unsigned long long a; //public
	unsigned long long v; //public key

	ShnorDigitalSignature();
	std::pair <unsigned long long, unsigned long long> sign(const std::string& message);
	bool verify(std::pair<unsigned long long, unsigned long long> signature, const std::string& massage);
private:
	//RIPEMD160 hashFunc;
	unsigned long long s; //secret key

	long long randomInRange(int min, int max);
	bool isPrime(int num);
	int modInverse(int a, int m);
	int modExp(int base, int exp, int mod);
	unsigned long long hashFunction(int r, const std::string& message);
};


#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <iostream>
#include <cmath>
class Cache
{
private:
	std::vector<std::vector<int>> dataMatrix;
	std::vector<std::bitset<6>> tags;
	std::vector<std::vector<int>> LRU;
	int lines;
	int blocks;
	int setSize;
	int wordSize;
	int tagSize;

	std::bitset<64> getBinaryAddress(void* ptr);
	int* getValueAtAddress(const std::bitset<64>& address);
	void saveAddress(std::bitset<6>&, unsigned long, unsigned long, int);
	void updateLRU(int set, int i);
public:
	Cache(int, int, int);
	//int find(int* address);
	int find(const std::bitset<6>&);
	void show();
};


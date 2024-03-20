#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "BasicTable.h"
class HashTable
{
public:
	struct Dog {
		std::string name;
		std::string breed;
		int age;

		Dog();
		Dog(std::string name, std::string breed, int age);
	};
	HashTable(int size);
	void showTable();
	void getData(std::vector<BasicTable::Dog> HashTable);
	void addData(std::string name, std::string breed, int age);
	void deleteData(std::string);
	int searchData(std::string);
	void redactData(std::string key, std::string name, std::string breed, int age);
	void chanceOfColision();
	Dog showData(int ind);
private:
	int N;
	double numOfCollisions;
	double numOfData;
	double numOfSearchTries;
	std::vector <bool> collisions;
	std::vector <Dog> table;
	int hashF(std::string key);
	bool tryAdd(int ind, std::string name, std::string breed, int age);
	int collisionHelper(int start, std::string key);
};

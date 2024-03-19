#include "HashTable.h"
#include <cmath>

HashTable::Dog::Dog() {
	name = "NULL";
	breed = "NULL";
	age = NULL;
}

HashTable::Dog::Dog(std::string newname, std::string newbreed, int newage) {
	name = newname;
	breed = newbreed;
	age = newage;
}

HashTable::HashTable(int size) {
	table = std::vector <Dog>(size, Dog());
	collisions = std::vector <bool>(size, false);
	N = size;
	numOfCollisions = 0;
	numOfData = 0;
	numOfSearchTries = 0;
}

void HashTable::showTable() {
	for (int i = 0; i < N; i++) {
		if (collisions[i])
			std::cout << "*";
		std::cout << i << " " << table[i].name << " " << table[i].breed << " " << table[i].age << "\n";
	}
}

int HashTable::hashF(std::string key) {
	int firstAscii = static_cast<int>(key[0]);
	int thirdAscii = static_cast<int>(key[2]);
	int lastAscii = static_cast<int>(key[key.length() - 1]);

	double product = firstAscii * thirdAscii * lastAscii;

	double C = 0.6180339887;
	double normHashAdress = std::modf(product * C, &normHashAdress);

	return std::trunc(N * normHashAdress);
}

void HashTable::addData(std::string name, std::string breed, int age) {
	if (name != "NULL" || name != "") {
		int index = hashF(name);
		if (!tryAdd(index, name, breed, age)) {
			numOfCollisions++;
			collisions[index] = true;
		}
	}
}

bool HashTable::tryAdd(int ind, std::string name, std::string breed, int age) {
	if (table[ind].name == "NULL") {
		table[ind] = Dog(name, breed, age);
		numOfData++;
		return true;
	}
	else if (ind + 1 == N)
		return true;
	else {
		for (int i = ind + 1; i < N; i++) {
			if (table[i].name == "NULL") {
				table[i] = Dog(name, breed, age);
				numOfData++;
				return false;
			}
		}
	}
	return true;
}

void HashTable::getData(std::vector<BasicTable::Dog> basicTable) {
	for (int i = 0; i < N; i++) {
			addData(basicTable[i].name, basicTable[i].breed, basicTable[i].age);
	}
}

int HashTable::searchData(std::string key) {
	numOfSearchTries++;
	int ind = hashF(key);
	if (table[ind].name == key) {
		return ind;
	}
	else {
		for (int i = ind + 1; i < N; i++) {
			numOfSearchTries++;
			if (table[i].name == key) {
				return i;
			}
		}
	}
	return -1;
}

void HashTable::deleteData(std::string key) {
	int ind = searchData(key);
	if (ind) {
		table[ind] = Dog();
		numOfData--;
	}
}

void HashTable::redactData(std::string key, std::string name, std::string breed, int age) {
	int ind = searchData(key);
	if (ind) {
		table[ind] = Dog(name, breed, age);
	}
}

void HashTable::chanceOfColision() {
	std::cout << "Chance of collision: " << numOfCollisions / numOfData << "\n";
	std::cout << "Average num of search tries: " << numOfSearchTries / numOfData << "\n";
	numOfSearchTries = 0;
}
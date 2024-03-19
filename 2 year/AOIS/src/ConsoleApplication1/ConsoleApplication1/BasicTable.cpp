#include "BasicTable.h"

BasicTable::Dog::Dog() {
	name = "NULL";
	breed = "NULL";
	age = NULL;
}

BasicTable::Dog::Dog(std::string newname, std::string newbreed, int newage) {
	name = newname;
	breed = newbreed;
	age = newage;
}

BasicTable::BasicTable(int size) {
	table = std::vector <Dog>(size, Dog());
	N = size;
}

void BasicTable::showTable() {
	for (int i = 0; i < N; i++) {
		std::cout << i << " " << table[i].name << " " << table[i].breed << " " << table[i].age << "\n";
	}
}

void BasicTable::addData(std::string name, std::string breed, int age) {
	for (int i = 0; i < N; i++) {
		if (table[i].name == "NULL") {
			table[i] = Dog(name, breed, age);
			return;
		}
	}
	std::cout << "No more space.\n";
}

void BasicTable::deleteData(std::string key) {
	for (int i = 0; i < N; i++) {
		if (table[i].name == key) {
			table[i] = Dog();
		}
	}
}

void BasicTable::redactData(std::string key, std::string newname, std::string newbreed, int newage) {
	for (int i = 0; i < N; i++) {
		if (table[i].name == key) {
			table[i] = Dog(newname, newbreed, newage);
		}
	}
}

int BasicTable::searchData(std::string key) {
	for (int i = 0; i < N; i++) {
		if (table[i].name == key) {
			return i;
		}
	}
	return NULL;
}

std::vector<BasicTable::Dog> BasicTable::passData() {
	return table;
}
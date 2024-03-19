#pragma once
#include <iostream>
#include <string>
#include <vector>

class BasicTable{
public:
	struct Dog {
		std::string name;
		std::string breed;
		int age;

		Dog();
		Dog(std::string name, std::string breed, int age);
	};
	BasicTable(int size);
	void showTable();
	void addData(std::string name, std::string breed, int age);
	void deleteData(std::string key);
	void redactData(std::string key, std::string newname, std::string newbreed, int newage);
	int searchData(std::string key);
	std::vector<Dog> passData();
private:
	int N;
	std::vector <Dog> table;
};
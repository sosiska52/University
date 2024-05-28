#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
class DataBase
{
private:
	std::vector<std::string> dataBase;
	std::vector<bool> mask;
	std::vector<int> findInd(std::string, int op);
public:
	void readDataBase(const std::string path);
	void editMask();
	void find(std::string);
	void add(std::string);
	void remove(std::string);
	void show();
};
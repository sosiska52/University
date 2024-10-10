#pragma once
#include"Guitarist.h"
#include "Drummer.h"
#include <vector>
class Band{
public:
	std::string name;
	std::vector<Musician*> members;

	Band(std::string);
	void addMember(Musician*);
	void makeStandartBand();
	void play();
};


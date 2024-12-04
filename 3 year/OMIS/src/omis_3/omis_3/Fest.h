#pragma once
#include "Band.h"
class Fest{
public:
	std::string name;
	Fest(const std::string& name);
	void addBand(const std::string& name);
	void start();
private:
	std::vector<Band> bands;
};


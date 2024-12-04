#include "Fest.h"

void Fest::addBand(const std::string& name) {
	Band band(name);
	band.makeStandartBand();
	bands.push_back(band);
}

Fest::Fest(const std::string& name) {
	this->name = name;
}

void Fest::start() {
	std::cout << name << " festival is starting!\n";
	for (Band band : bands) 
		band.play();
}
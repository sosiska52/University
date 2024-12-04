#include "Band.h"

Band::Band(std::string name) {
	this->name = name;
}

void Band::addMember(Musician* freshman) {
	members.push_back(freshman);
}

void Band::play() {
	std::cout << name << " band is perfoming\n";
	for (int i = 0; i < members.size(); i++) {
		std::cout << members[i]->name << ": ";
		members[i]->play();
	}
}

void Band::makeStandartBand() {
	Musician* guitarist = new Guitarist();
	Musician* drummer = new Drummer();
	Musician* singer = new Musician("Unknown singer");

	addMember(guitarist);
	addMember(drummer);
	addMember(singer);
}
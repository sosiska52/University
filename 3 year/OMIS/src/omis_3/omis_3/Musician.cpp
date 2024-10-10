#include "Musician.h"

Musician::Musician(std::string name) {
	this->name = name;
}

Musician::~Musician() {
	std::cout << "Another musician has left us\n";
}

Musician& Musician::operator = (const Musician& other) {
    this->name = other.name;
    return *this;
}

void Musician::play() const{
	std::cout << "Lalalalalala\n";
}

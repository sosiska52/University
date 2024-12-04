#pragma once
#include <string>
#include <iostream>

class Musician{
public:
	std::string name;
	Musician(std::string);
	~Musician();
	virtual void play() const;
	Musician& operator = (const Musician& other);
};


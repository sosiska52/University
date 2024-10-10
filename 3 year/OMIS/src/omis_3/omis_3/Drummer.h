#pragma once
#include "Musician.h"
class Drummer: public Musician{
public:
	Drummer() : Musician("Unknown drummer") {}
	void play() const ;
};


#pragma once
#include "Musician.h"
class Guitarist: public Musician{
public: 
	Guitarist() : Musician("Unknown guitarist") {}
	void play() const;
};


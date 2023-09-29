#pragma once
#include <fstream>
#include "Functions.h"

void TXTinput(product*& shop, int& size, product**& index);
void TXToutput(product shop[], int size, product**& index);
void sortedOutput(int size, product**& index, bool choise);
void sortedInput(product shop[], int size, product**& index);
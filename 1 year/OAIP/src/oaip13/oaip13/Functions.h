#pragma once
#include "Product.h"
#include <iostream>
#include <iomanip>

using namespace std;

void input(product*& shop, int& size, product**& index);
void output(int size, product**& index);
void remove(product shop[], int& size, product**& index);
void sort(int size, product**& index, bool& choise);
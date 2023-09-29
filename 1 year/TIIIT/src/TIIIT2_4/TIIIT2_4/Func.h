#pragma once
#include <cmath>
#include <iostream>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

void population();

double func(double, int, double);

double minOfFunc(int, int, int, int);

double threadsFunc(int, int, int, int);
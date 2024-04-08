#include <iostream>
#include "BidirectionalNN.h"

int main()
{
	int n = 12;
	int m = 8;
	BidirectionalNN neuronN(n, m);
	/*
	0	0	0	0	1	1	1	1	0	0	0	0   	1	1	1	1	0	0	0	0
	1	1	1	1	0	0	0	0	1	1	1	1   	0	0	0	0	1	1	1	1
	1	1	1	0	0	0	1	1	1	0	0	0       1	1	1	0	0	0	1	1
	*/
	std::vector <std::vector <int>> X(3, std::vector<int>(n));
	std::vector <std::vector <int>> Y(3, std::vector<int>(m));
	X = {
		{0,	0,	0,	0,	1,	1,	1,	1,	0,	0,	0,	0},
		{1,	1,	1,	1,	0	,0,	0,	0,	1,	1,	1	,1},
		{1,	1,	1,	0	,0,	0,	1,	1,	1,	0,	0,	0}
		};
	Y = {
		{1,	1	,1,	1,	0,	0,	0,	0},
		{0,	0,	0,	0,	1,	1,	1	,1},
		{1	,1	,1	,0	,0	,0	,1	,1}
	};
	neuronN.initializeWeight(X, Y);
}
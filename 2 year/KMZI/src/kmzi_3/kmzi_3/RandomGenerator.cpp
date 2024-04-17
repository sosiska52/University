#include "RandomGenerator.h"

int RandomGenerator::extendedEuclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedEuclidean(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int RandomGenerator::findMultiplicativeInverse(int x) {
    int inv, y;
    int gcd = extendedEuclidean(x, N, inv, y);

    if (gcd != 1)
        return -1;

    inv = (inv % N + N) % N;

    return inv;
}

RandomGenerator::RandomGenerator(int a, int c, int N){
    this->a = a;
    this->c = c;
    this->N = N;
}

int RandomGenerator::calculateNewX(int x0) {
	if (x0 == 0)
		return c;
    else {
        int inverse = findMultiplicativeInverse(x0);
        std::cout << x0 << " inverted: " << inverse << "\n";
        if (inverse != -1)
            return (a * inverse + c) % N;
        else
            return (a * x0 + c) % N;
    }
}

std::vector<int> RandomGenerator::generate(int x0, int size) {
	int x = x0;
	std::vector<int> result;
	for (int i = 0; i < size; i++) {
		result.push_back(x);
        x = calculateNewX(x);
	}
	return result;
}

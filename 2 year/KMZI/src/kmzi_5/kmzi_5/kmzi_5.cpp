#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

void trialDivisions(int N) {
    std::ifstream fin;
    fin.open("prime_numbers.txt");
    for (int i = 0; i < 300; i++) {
        int primeNum;
        fin >> primeNum;
        if (N % primeNum == 0)
            std::cout << primeNum << " ";
    }
    fin.close();
}

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modular_pow(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int pollards_p_minus_1(int n, int B, int a) {
    srand(time(0)); 
    int g = gcd(a, n);
    if (g > 1) {
        return g;
    }

    for (int j = 2; j <= B; ++j) {
        a = modular_pow(a, j, n);
        g = gcd(a - 1, n);
        if (g > 1 && g < n) {
            return g;
        }
    }

    return -1; 
}

bool findEl(std::vector<int> vec, int num) {
    if (vec.empty())
        return false;

    for (int i = 0; i < vec.size(); i++) 
        if (vec[i] == num)
            return true;
    return false;
}

int main()
{
    int number = 267584;
    std::cout << "Trial divisions method: ";
    trialDivisions(number);
    std::cout << "\n";

    std::vector<int>used;
    for (int i = 1; i < number; i++) {
        int result = pollards_p_minus_1(number, 100, i);
        if (!findEl(used, result))
            used.push_back(result);
    }

    std::cout << "Pollard: ";
    for (int i = 1; i < used.size(); i++) {
        std::cout << used[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
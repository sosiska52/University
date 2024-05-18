#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <conio.h>

void readrimeNumbers(std::vector<int>& vec) {
    std::ifstream fin("prime_numbers.txt");
    vec.resize(300);
    for (int i = 0; i < 300; i++) {
        fin >> vec[i];
    }
    fin.close();
}

int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool isPrime(int num) {
    if (num < 2) {
        return false;
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int findLargestPrimeDivisor(int num) {
    int largestPrime = 2;

    if (isPrime(num)) {
        return num;
    }

    for (int i = 2; i <= num / 2; ++i) 
        if (num % i == 0 && isPrime(i))
            largestPrime = i;

    return largestPrime;
}

bool checkIfPrime(int n) {
    if (n < 2)
        return false;

    std::vector<int> primeNumbers;
    readrimeNumbers(primeNumbers);
    for (int i = 0; i < 300; i++) {
        if (n == primeNumbers[i])
            return true;
        if (n % primeNumbers[i] == 0)
            return false;
    }
       
    int r = 1;
    while (r < n) {
        if (findGCD(r, n) != 1)
            return false;
        if (isPrime(r)) {
            int q = findLargestPrimeDivisor(r - 1);
            if (q > 4 * sqrt(r)*log2(n) && (int)pow(n, (r - 1) / q) % r == 1)
                break;
        }
        r++;
    }
    
    if (r == n)
        return false;
    
    if (n - 1 <= 2 * sqrt(r) * log2(n)) {
        for (int a = r; a < n; a++) 
            if (findGCD(a, n) != 1)
                return false;
    }
    else
        for (int a = 1; a <= 2 * sqrt(r) * log2(n); a++)
            if ((int)pow((3 - a), n) % ((int)pow(3, r) - 1) != (int)pow(3, n) - a)
                return false;
    
    return true;
}

void menu() {
    int number;
    while(true) {
        system("cls");
        std::cout << "Enter number (0 to exit): ";
        std::cin >> number;
        if (number == 0)
            break;
        if (isPrime(number))
            std::cout << "Prime\n(Press Enter)\n";
        else
            std::cout << "Complex\n(Press Enter)\n";
        _getch();
    }
}

int main()
{
    menu();
    return 0;
}
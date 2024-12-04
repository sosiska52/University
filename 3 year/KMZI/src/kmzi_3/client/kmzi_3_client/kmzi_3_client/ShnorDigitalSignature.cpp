#include "ShnorDigitalSignature.h"

ShnorDigitalSignature::ShnorDigitalSignature() {
    do p = randomInRange(160, 256);
    while (!isPrime(p));

    do q = randomInRange(3, p - 1);
    while (!isPrime(q) || (p - 1) % q != 0);

    do a = randomInRange(1, p - 1);
    while (modExp(a, q, p) != 1);

	s = randomInRange(1, q);
    v = modInverse(modExp(a, s, q), q);
    std::cout << "p: " << p << "\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               /* p = 191;*/
    std::cout << "q: " << q << "\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                /*q = 19;*/
    std::cout << "a: " << a << "\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               /* a = 150;*/
    std::cout << "s: " << s << "\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               /* s = 1;*/
    std::cout << "v: " << v << "\n";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                /*v = 9;*/
}

long long ShnorDigitalSignature::randomInRange(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(min, max);
    return dis(gen);
}

bool ShnorDigitalSignature::isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int ShnorDigitalSignature::modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int ShnorDigitalSignature::modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

std::pair <unsigned long long, unsigned long long> ShnorDigitalSignature::sign(const std::string& message) {
    unsigned long long r = randomInRange(1, q);
    unsigned long long X = modExp(a, r, p);

    unsigned long long e = hashFunction(X, message);

    unsigned long long y = (r + s * e) % q;

    std::cout << "Signing: r = " << r << ", X = " << X << ", e = " << e << ", y = " << y << std::endl;

    return { e, y };
}

bool ShnorDigitalSignature::verify(std::pair<unsigned long long, unsigned long long> signature, const std::string& message) {
    long long exp = signature.second - s * signature.first;
    long long X_prime = modExp(a, exp, p);

    long long e_prime = hashFunction(X_prime, message);

    std::cout << "Verifying: X' = " << X_prime << ", e' = " << e_prime << std::endl;

    return signature.first == e_prime;
}

unsigned long long ShnorDigitalSignature::hashFunction(int r, const std::string& message) {
    std::hash<std::string> hasher;
    return hasher(std::to_string(r) + message) % q;
}
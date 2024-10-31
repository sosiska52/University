#include "ShnorDigitalSignature.h"

ShnorDigitalSignature::ShnorDigitalSignature() {
    p = randomInRange(160, 256);
    while(!isPrime(p))
        p = randomInRange(160, 256);

    q = randomInRange(3, p - 1);
    while (!isPrime(q) || (p - 1) % q != 0)
        q = randomInRange(3, p - 1);

    g = randomInRange(1, p - 1) + randomInRange(1, 10) * p;
	x = randomInRange(1, q - 1);
    //y = modInverse(modExp(g, x, p), p);
    y = std::pow(g, -1 * x);
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
    unsigned long long k = randomInRange(1, q - 1);
    unsigned long long r = modExp(g, k, p);

    /*std::string msg1 = std::to_string(r) + message;
    uint8_t digest[20];
    hashFunc.hash(msg1, msg1.length(), digest);
    std::ostringstream oss;
    for (size_t i = 0; i < sizeof(digest); ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    
    unsigned long long e = std::stoull(oss.str(), nullptr, 2);*/
    unsigned long long e = hashFunction(r, message) ;
    unsigned long long s = (k + x * e) ;
    return {e, s};
}

bool ShnorDigitalSignature::verify(std::pair<unsigned long long, unsigned long long> signature, const std::string& message) {
   //RIPEMD160 hashFunc;
   unsigned long long r = (modExp(g, signature.second, p) * modExp(y, signature.first, p)) % p;
   
   /*std::string msg = std::to_string(r) + message;
   uint8_t digest[20];
   hashFunc.hash(msg, sizeof(msg), digest);
   std::ostringstream oss;
   for (size_t i = 0; i < sizeof(digest); ++i)
       oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);

   unsigned long long e = std::stoull(oss.str(), nullptr, 16);*/
   unsigned long long e = hashFunction(r, message) % q;

   return e == signature.first;
}

unsigned long long ShnorDigitalSignature::hashFunction(int r, const std::string& message) {
    std::hash<std::string> hasher;
    return hasher(std::to_string(r) + message);
}
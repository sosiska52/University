#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>

class RIPEMD160 {
public:
    RIPEMD160();
    void hash(const uint8_t* message, size_t length, uint8_t digest[20]);
private:
    void update(const uint8_t* message, size_t length);
    void finalize(uint8_t digest[20]);
    uint32_t state[5];
    uint32_t count[2];
    uint8_t buffer[64];
    static const int R1[80];
    static const int R2[80];
    static const int S1[80];
    static const int S2[80];

    uint32_t f(uint32_t j, uint32_t x, uint32_t y, uint32_t z);
    uint32_t K1(int j);
    uint32_t K2(int j);
    void processBlock(const uint8_t* block);
};
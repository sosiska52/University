#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>

typedef unsigned char uint8;
typedef unsigned int uint32;

class RIPEMD160 {
public:
    RIPEMD160() {
        state[0] = 0x67452301;
        state[1] = 0xEFCDAB89;
        state[2] = 0x98BADCFE;
        state[3] = 0x10325476;
        state[4] = 0xC3D2E1F0;
        count[0] = 0;
        count[1] = 0;
        memset(buffer, 0, sizeof(buffer));
    }

    void update(const uint8_t* message, size_t length) {
        size_t index = count[0] / 8 % 64;
        count[0] += length * 8;
        if (count[0] < length * 8) {
            count[1]++;
        }
        count[1] += length >> 29;

        size_t firstPart = 64 - index;
        size_t i = 0;

        if (length >= firstPart) {
            memcpy(&buffer[index], message, firstPart);
            processBlock(buffer);
            for (i = firstPart; i + 63 < length; i += 64) {
                processBlock(&message[i]);
            }
            index = 0;
        }
        memcpy(&buffer[index], &message[i], length - i);
    }

    void finalize(uint8_t digest[20]) {
        uint8_t padding[64] = { 0x80 };
        size_t index = count[0] / 8 % 64;
        size_t padLen = index < 56 ? 56 - index : 120 - index;

        update(padding, padLen);
        uint8_t length[8];
        for (int i = 0; i < 8; i++) {
            length[i] = (count[i / 4] >> ((3 - (i % 4)) * 8)) & 0xFF;
        }
        update(length, 8);

        for (int i = 0; i < 5; i++) {
            digest[i * 4] = (state[i] >> 24) & 0xFF;
            digest[i * 4 + 1] = (state[i] >> 16) & 0xFF;
            digest[i * 4 + 2] = (state[i] >> 8) & 0xFF;
            digest[i * 4 + 3] = state[i] & 0xFF;
        }
    }

private:
    uint32 state[5];
    uint32 count[2];
    uint8_t buffer[64];

    static const int R1[80];
    static const int R2[80];
    static const int S1[80];
    static const int S2[80];

    uint32 f(uint32 j, uint32 x, uint32 y, uint32 z) {
        if (j >= 0 && j <= 15)
            return x ^ y ^ z;
        if (j > 15 && j <= 31)
            return (x & y) | (~x & z);
        if (j > 31 && j <= 47)
            return (x | ~y) ^ z;
        if (j > 47 && j <= 63)
            return (x & z) | (y & ~z);
        if (j > 63 && j <= 79)
            return x ^ (y | ~z);
        return 0;
    }

    uint32_t K1(int j) {
        if (j < 16)
            return 0x00000000;
        else if (j < 32)
            return 0x5A827999;
        else if (j < 48)
            return 0x6ED9EBA1;
        else if (j < 64)
            return 0x8F1BBCDC;
        else
            return 0xA953FD4E;
    }

    uint32_t K2(int j) {
        if (j < 16) return 0x00000000;
        else if (j < 32) return 0x5C4DD124;
        else if (j < 48) return 0x6D703EF3;
        else if (j < 64) return 0xA6D9D649;
        else return 0x00000000;
    }

    void processBlock(const uint8_t* block) {
        uint32 M[16];
        std::ofstream fout("hash8.txt");
        for (int i = 0; i < 16; ++i) {
            M[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
                (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
        }

        uint32 h0 = state[0], h1 = state[1], h2 = state[2], h3 = state[3], h4 = state[4];

        uint32 A1 = h0, B1 = h1, C1 = h2, D1 = h3, E1 = h4;
        uint32 A2 = h0, B2 = h1, C2 = h2, D2 = h3, E2 = h4;

        uint32 htemp[5];
        htemp[1] = h1;
        htemp[2] = h2;
        htemp[3] = h3;
        htemp[4] = h4;
        htemp[0] = h0;

        for (int j = 0; j < 80; ++j) {
            uint32 T1 = A1 + f(j, B1, C1, D1) + M[R1[j]] + K1(j);
            T1 = (T1 << S1[j]) | (T1 >> (32 - S1[j]));
            E1 = D1;
            D1 = (C1 << 10) | (C1 >> (32 - 10));
            C1 = B1;
            B1 = T1;

            uint32 T2 = A2 + f(79 - j, B2, C2, D2) + M[R2[j]] + K2(j);
            T2 = (T2 << S2[j]) | (T2 >> (32 - S2[j]));
            E2 = D2;
            D2 = (C2 << 10) | (C2 >> (32 - 10));
            C2 = B2;
            B2 = T2;

            uint32 Tt = htemp[1] + C1 + D2;
            htemp[1] = htemp[2] + D1 + E2;
            htemp[2] = htemp[3] + E1 + A2;
            htemp[3] = htemp[4] + A1 + B2;
            htemp[4] = htemp[0] + B1 + C2;
            htemp[0] = Tt;

            uint8_t digest[20];
            for (int i = 0; i < 5; i++) {
                digest[i * 4] = (htemp[i] >> 24) & 0xFF;
                digest[i * 4 + 1] = (htemp[i] >> 16) & 0xFF;
                digest[i * 4 + 2] = (htemp[i] >> 8) & 0xFF;
                digest[i * 4 + 3] = htemp[i] & 0xFF;
            }

            for (const auto& byte : digest) {
                fout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
            }
            fout << std::endl;
        }

        uint32 T = h1 + C1 + D2;
        h1 = h2 + D1 + E2;
        h2 = h3 + E1 + A2;
        h3 = h4 + A1 + B2;
        h4 = h0 + B1 + C2;
        h0 = T;

        state[0] += h0;
        state[1] += h1;
        state[2] += h2;
        state[3] += h3;
        state[4] += h4;


        fout.close();
    }
};
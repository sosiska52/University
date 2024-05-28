#include "Cache.h"

Cache::Cache(int lines, int blocks, int setsNum) {
    this->blocks = blocks;
    this->lines = lines;
    setSize = lines / setsNum;
    wordSize = log2(blocks);
    tagSize = 64 - setSize - wordSize;

    tags = std::vector<std::bitset<64>>(lines, 0000000000000000000000000000000000000000000000000000000000000000);
    dataMatrix = std::vector<std::vector<int>>(lines, std::vector<int>(blocks, NULL));
    LRU = std::vector<std::vector<int>>(setsNum, std::vector<int>(setSize));

    for (int i = 0; i < setsNum; i++) {
        for (int j = 0; j < setSize; j++) {
            LRU[i][j] = j;
        }
    }
}

int* Cache::getValueAtAddress(const std::bitset<64>& address) {
    int* ptr = reinterpret_cast<int*>(address.to_ullong());

    return ptr;
}

std::bitset<64> Cache::getBinaryAddress(void* ptr) {
    uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    std::bitset<64> binary_address(address);

    return binary_address;
}

int Cache::find(int* data) {
    std::bitset<64> address = getBinaryAddress(data);
    std::cout << "Address: " << address << "\n";
    unsigned long set = ((address >> wordSize) & std::bitset<64>(0b11)).to_ulong();
    std::cout << "Set: " << set << "\n";
    std::bitset<64> tag = address >> 7;
    std::cout << "Tag: " << tag << "\n";

    bool isFound = false;
    for (int i = 0; i < setSize; i++) {
        if (tags[set * setSize + i] == tag) {
            unsigned long word = (address & std::bitset<64>(0b111)).to_ulong();
            std::cout << "Ofset: " << word << "\n";
            if (dataMatrix[set * setSize + i][word] == NULL)
                dataMatrix[set * setSize + i][word] = *getValueAtAddress(address);

            isFound = true;
            updateLRU(set, i);
            std::cout << "Hit\n\n";
            return dataMatrix[set * setSize + i][word];
        }
    }

    if (!isFound) {
        unsigned long word = (address & std::bitset<64>(0b111)).to_ulong();
        std::cout << "Ofset: " << word << "\n";
        int data = *getValueAtAddress(address);
        saveAddress(tag, set, word, data);
        std::cout << "Miss\n\n";
        return data;
    }
}

int Cache::find(const std::bitset<64>& address) {
    std::cout << "Address: " << address << "\n";
    unsigned long set = ((address >> wordSize) & std::bitset<64>(0b11)).to_ulong();
    std::cout << "Set: " << set << "\n";
    std::bitset<64> tag = address >> 7;
    std::cout << "Tag: " << tag << "\n";

    bool isFound = false;
    for (int i = 0; i < setSize; i++) {
        if (tags[set * setSize + i] == tag) {
            unsigned long word = (address & std::bitset<64>(0b111)).to_ulong();
            std::cout << "Ofset: " << word << "\n";

            if (dataMatrix[set * setSize + i][word] == NULL)
                dataMatrix[set * setSize + i][word] = *getValueAtAddress(address);

            isFound = true;
            updateLRU(set, i);
            std::cout << "Hit\n";
            return dataMatrix[set * setSize + i][word];
        }
    }

    if (!isFound) {
        unsigned long word = (address & std::bitset<64>(0b111)).to_ulong();
        std::cout << "Ofset: " << word << "\n";
        int* ptr = getValueAtAddress(address);
        int data = *ptr;
        saveAddress(tag, set, word, data);
        std::cout << "Miss\n";
        return data;
    }
}

void Cache::saveAddress(std::bitset<64>& tag, unsigned long set, unsigned long word, int data) {
    int ind = LRU[set][0];
    tags[set * setSize + ind] = tag;
    dataMatrix[set * setSize + ind] = std::vector<int>(blocks, NULL);
    dataMatrix[set * setSize + ind][word] = data;
    updateLRU(set, ind);
}

void Cache::updateLRU(int set, int ind) {
    LRU[set].push_back(ind);
    LRU[set].erase(LRU[set].begin() + ind);
}

void Cache::show() {
    for (int i = 0; i < lines; i++) {
        std::cout << tags[i] << " ";
        for (int j = 0; j < blocks; j++) {
            std::cout << dataMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}
#include "Cache.h"

Cache::Cache(int lines, int blocks, int setsNum) {
    this->blocks = blocks;
    this->lines = lines;
    setSize = lines / setsNum;
    wordSize = log2(blocks);
    tagSize = 6 - setSize - wordSize;

    tags = std::vector<std::bitset<6>>(lines, 000000);
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

//int Cache::find(int* data) {
//    std::bitset<6> address = getBinaryAddress(data);
//    std::cout << "Address: " << address << "\n";
//    unsigned long set = ((address >> wordSize) & std::bitset<6>(0b11)).to_ulong();
//    std::cout << "Set: " << set << "\n";
//    std::bitset<6> tag = address >> (wordSize + setSize);
//    std::cout << "Tag: " << tag << "\n";
//
//    bool isFound = false;
//    for (int i = 0; i < setSize; i++) {
//        if (tags[set * setSize + i] == tag) {
//            unsigned long word = (address & std::bitset<6>(0b111)).to_ulong();
//            std::cout << "Ofset: " << word << "\n";
//
//            if (dataMatrix[set * setSize + i][word] == NULL)
//                dataMatrix[set * setSize + i][word] = address.to_ullong();
//
//            isFound = true;
//            updateLRU(set, i);
//            std::cout << "Hit\n";
//            return dataMatrix[set * setSize + i][word];
//        }
//    }
//
//    if (!isFound) {
//        unsigned long word = (address & std::bitset<6>(0b111)).to_ulong();
//        std::cout << "Ofset: " << word << "\n";
//        int data = address.to_ullong();
//        saveAddress(tag, set, word, data);
//        std::cout << "Miss\n";
//        return data;
//    }
//}

int Cache::find(const std::bitset<6>& address) {
    std::cout << "Address: " << address << "\n";
    unsigned long set = ((address >> wordSize) & std::bitset<6>(0b11)).to_ulong();
    std::cout << "Set: " << set << "\n";
    std::bitset<6> tag = address >> (wordSize + setSize);
    std::cout << "Tag: " << tag[tagSize - 1] << "\n";

    bool isFound = false;
    for (int i = 0; i < setSize; i++) {
        if (tags[set * setSize + i] == tag) {
            unsigned long word = (address & std::bitset<6>(0b111)).to_ulong();
            std::cout << "Ofset: " << word << "\n";

            if (dataMatrix[set * setSize + i][word] == NULL)
                //dataMatrix[set * setSize + i][word] = *getValueAtAddress(address);
                dataMatrix[set * setSize + i][word] = address.to_ullong();

            isFound = true;
            updateLRU(set, i);
            std::cout << "Hit\n";
            return dataMatrix[set * setSize + i][word];
        }
    }

    if (!isFound) {
        unsigned long word = (address & std::bitset<6>(0b111)).to_ulong();
        std::cout << "Ofset: " << word << "\n";
        //int* ptr = getValueAtAddress(address);
        int data = address.to_ullong();
        saveAddress(tag, set, word, data);
        std::cout << "Miss\n";
        return data;
    }
}

void Cache::saveAddress(std::bitset<6>& tag, unsigned long set, unsigned long word, int data) {
    int ind = LRU[set][0];
    tags[set * setSize + ind] = tag;
    dataMatrix[set * setSize + ind] = std::vector<int>(blocks, NULL);
    dataMatrix[set * setSize + ind][word] = data;
    updateLRU(set, ind);
}

void Cache::updateLRU(int set, int ind) {
    LRU[set].push_back(ind);

    for (int i = 0; i < LRU[set].size() - 1; i++) {
        if(LRU[set][i] == ind)
            LRU[set].erase(LRU[set].begin() + i);
    }
}

void Cache::show() {
    for (int i = 0; i < lines; i++) {
        std::cout << tags[i][tagSize - 1] << " ";
        for (int j = 0; j < blocks; j++) {
            std::cout << dataMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}
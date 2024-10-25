#include "RipeMD160_Hash.h"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string content;

    if (!file) {
        std::cerr << "Error. Can't open file: " << filename << std::endl;
        return content;
    }
    std::getline(file, content);

    std::cout << content;
    file.close();
    return content;
}

void hexToBinary(const std::string& hexStr, std::vector<bool>& binaryVec) {
    for (char hexChar : hexStr) {
        int value = (hexChar >= '0' && hexChar <= '9') ? hexChar - '0' : hexChar - 'a' + 10;
        for (int i = 3; i >= 0; --i) {
            binaryVec.push_back((value >> i) & 1);
        }
    }
}

int countDifferentBits(const std::vector<bool>& binary1, const std::vector<bool>& binary2) {
    int diffCount = 0;
    for (size_t i = 0; i < binary1.size(); ++i) {
        if (binary1[i] != binary2[i]) {
            ++diffCount;
        }
    }
    return diffCount;
}

void compareFiles(const std::string& file1, const std::string& file2) {
    std::ifstream ifs1(file1);
    std::ifstream ifs2(file2);

    if (!ifs1.is_open() || !ifs2.is_open()) {
        std::cerr << "Error opening one of the files!" << std::endl;
        return;
    }

    std::string line1, line2;
    int lineNumber = 0;

    while (std::getline(ifs1, line1) && std::getline(ifs2, line2)) {
        lineNumber++;

        std::vector<bool> binary1, binary2;
        hexToBinary(line1, binary1);
        hexToBinary(line2, binary2);

        if (binary1.size() != binary2.size()) {
            std::cerr << "Lines have different lengths at line " << lineNumber << std::endl;
            continue;
        }

        int diffBits = countDifferentBits(binary1, binary2);
        std::cout << lineNumber << "; " << diffBits << std::endl;
    }

    ifs1.close();
    ifs2.close();
}

int main() {
    /*std::string filename;
    std::cout << "Enter path: ";
    std::cin >> filename;
    std::string msg = readFile(filename);*/

    std::string msg1 = "Рello my name is nikita and this is my secret message";

    RIPEMD160 ripemd160;
    ripemd160.update(reinterpret_cast<const uint8_t*>(msg1.c_str()), msg1.length());

    uint8_t digest[20];
    ripemd160.finalize(digest);

    std::cout << "RIPEMD160(\"" << msg1 << "\") = ";
    for (const auto& byte : digest) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    std::cout << std::endl;

    return 0;
}
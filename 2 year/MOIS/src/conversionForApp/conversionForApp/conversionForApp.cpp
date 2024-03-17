#include <iostream>
#include <fstream>
#include <string>

void convertFormat(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file: " << inputFileName << std::endl;
        return;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file: " << outputFileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        size_t start = line.find("'") + 1;
        size_t end = line.find("'", start);
        while (start != std::string::npos && end != std::string::npos) {
            std::string word = line.substr(start, end - start);
            outputFile << "<item>" << word << "</item>" << std::endl;
            start = line.find("'", end + 1) + 1;
            end = line.find("'", start);
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    std::string inputFileName = "minibus.txt";
    std::string outputFileName = "output.txt";

    convertFormat(inputFileName, outputFileName);

    std::cout << "Conversion complete." << std::endl;

    return 0;
}
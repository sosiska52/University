#include <iostream>
#include "ConvNetwork.h"

void readMNIST(std::vector<ConvNetwork::Mnist_data>& images, std::string filename, int size) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "cant open mnist\n";
    }
    images = std::vector<ConvNetwork::Mnist_data>(size);
    std::cout << "start reading\n";
    for (int i = 0; i < size; i++) {
        fin >> images[i].label;
        for (int j = 0; j < 784; j++) {
            fin >> images[i].pixels[j];
        }
    }
    std::cout << "end reading\n";
    fin.close();
}


int main()
{
    std::vector<ConvNetwork::Mnist_data> testBatch;
    std::vector<ConvNetwork::Mnist_data> dataBatch2;
    readMNIST(dataBatch2, "lib_MNIST_edit.txt", 20000);
    readMNIST(testBatch, "lib_10k.txt", 10000);
}
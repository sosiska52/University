#include <iostream>
#include <string>
#include <fstream>
#include "Network.h"

void readCifar(std::vector<Network::Cifar_data>& images, std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error: Failed to open file." << std::endl;
        return;
    }
    images = std::vector<Network::Cifar_data>(Network::Cifar_data::numImages);

    for (int i = 0; i < Network::Cifar_data::numImages; ++i) {
        Network::Cifar_data& image = images[i];

        file.read(reinterpret_cast<char*>(&image.label), Network::Cifar_data::labelSize);
        //std::cout << static_cast<double>(image.label) << "\n";
        image.pixels.resize(Network::Cifar_data::imageSize);
        file.read(reinterpret_cast<char*>(image.pixels.data()), Network::Cifar_data::imageSize);
    }

    file.close();
}

void readMNIST(std::vector<Network::Mnist_data>& images, std::string filename, int size) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "cant open mnist\n";
    }
    images = std::vector<Network::Mnist_data>(size);
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

void menu() {
    Network network;
    std::vector<Network::Cifar_data> dataBatch1;
    std::vector<Network::Mnist_data> testBatch;
    std::vector<Network::Mnist_data> dataBatch2;
    //readCifar(dataBatch1, "data_batch_1.bin");
    //readMNIST(dataBatch2, "lib_MNIST_edit.txt", 20000);
    readMNIST(testBatch, "lib_10k.txt", 10000);

    while (true) {
        int choise;
        std::cout << "Menu\n";
        std::cout << "1. Train from scratch\n";
        std::cout << "2. Load weights\n";
        std::cout << "3. Save weights\n";
        std::cout << "4. Test\n";
        std::cin >> choise;
        switch (choise)
        {
        case 1:
            network.train(dataBatch2);
            network.saveWeight();
            break;
        case 2:
            network.loadWeight();
            break;
        case 3:
            network.saveWeight();
            break;
        case 4:
            network.test(testBatch);
            break;
        default:
            system("cls");
            break;
        }
    }
}

int main(){
    menu();
    return 0;
}
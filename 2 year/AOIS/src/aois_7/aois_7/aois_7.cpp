#include <iostream>
#include "Cache.h"

int* getValueAtAddress(const std::bitset<64>& address) {
    uintptr_t addr = address.to_ullong();
    if (addr % alignof(int) != 0) {
        // Адрес не выровнен по границе int
        return nullptr;
    }
    return static_cast<int*>(reinterpret_cast<void*>(addr));
}

//void test(Cache& cache) {
//    int d0 = -1;
//    int d1 = 1;
//    int d2 = 2;
//    int d3 = 3;
//    int d4 = 4;
//    int d5 = 5;
//    int d6 = 6;
//    int d7 = 7;
//    int d8 = 8;
//    int d9 = 9;
//
//    int* ptr1 = &d1;
//    ptr1 = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(ptr1) + 1);
//
//    for (int i = 0; i < 5; i++) {
//        std::cout << i << ":\n--------------------------------------------------\n";
//        cache.find(&d0);
//        cache.show();
//        cache.find(&d1);
//        cache.show();
//        cache.find(&d2);
//        cache.show();
//        cache.find(&d3);
//        cache.show();
//        cache.find(&d4);
//        cache.show();
//        cache.find(&d4);
//        cache.show();
//        cache.find(&d4);
//        cache.show();
//        cache.find(&d5);
//        cache.show();
//        cache.find(&d6);
//        cache.show();
//        cache.find(&d7);
//        cache.show();
//        cache.find(&d8);
//        cache.show();
//        cache.find(&d9);
//        cache.find(ptr1);
//        cache.show();
//    }
//}

void menu() {
    Cache cache(8, 8, 4);
    int choise;
    std::bitset<6> bitset;
    std::string input;
    int data = 2;
    while (true) {
        system("cls");
        std::cout << "MENU\n";
        std::cout << "1.Find\n";
        std::cout << "2.Show\n";
        std::cout << "3.Test\n";
        std::cout << "4.Exit\n";
        std::cin >> choise;
        switch (choise)
        {
        case 1:
            system("cls");
            std::cout << "Enter address by bit(6): ";
            std::cin >> input;

            for (char c : input) {
                if (c != '0' && c != '1') {
                    std::cerr << "Invalid input. Please enter only 0 and 1." << std::endl;
                    system("pause");
                    system("cls");
                    break;
                }
            }
            bitset = std::bitset<6>(input);
            std::cout << cache.find(bitset) << "\n";
            system("pause");
            break;
        case 2:
            system("cls");
            cache.show();
            system("pause");
            break;
        case 3:
            system("cls");
            //test(cache);
            system("pause");
            break;
        case 4:
            return;
        default:
            system("cls");
            break;
        }
    }
}

int main()
{
    menu();
}
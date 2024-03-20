#include <iostream>
#include "BasicTable.h"
#include "HashTable.h"
#include <fstream>

void loadFromFile(BasicTable &basicTable) {
    std::ifstream fin("list.txt");
    std::string name;
    std::string breed;
    int age;
    for (int i = 0; i < 40; i++) {
        fin >> name >> breed >> age;
        basicTable.addData(name, breed, age);
    }
    fin.close();
}

void basicMenu(BasicTable basicTable){
    while (true) {
        std::cout << "\nMenu\n";
        std::cout << "1. Show table\n";
        std::cout << "2. Add data\n";
        std::cout << "3. Delete data\n";
        std::cout << "4. Find data\n";
        std::cout << "5. Edit data\n";
        std::cout << "6. Exit\n";
        int choise;
        std::string key;
        std::string name;
        std::string breed;
        int age;
        int ind;
        std::cin >> choise;

        switch (choise)
        {
        case 1:
            basicTable.showTable();
            break;
        case 2:
            std::cout << "Enter name, breed, age:\n";
            std::cin >> name >> breed >> age;
            basicTable.addData(name, breed, age);
            system("cls");
            break;
        case 3:
            std::cout << "Enter name:\n";
            std::cin >> key;
            ind = basicTable.searchData(key);
            if (ind == -1) {
                std::cout << "NotFound\n";
            }
            else {
                basicTable.deleteData(key);
            }
            system("cls");
            break;
        case 4:
            std::cout << "Enter name:\n";
            std::cin >> key;
            ind = basicTable.searchData(key);
            if (ind == -1) {
                std::cout << "NotFound\n";
            }
            else {
                std::cout << "Found at: " << ind << "\n";
            }
            system("cls");
            break;
        case 5:
            std::cout << "Enter name:\n";
            std::cin >> key;
            if (basicTable.searchData(key) == -1) {
                std::cout << "Not found\n";
            }
            else {
                std::cout << "Enter name, breed, age:\n";
                std::cin >> name >> breed >> age;
                basicTable.redactData(key, name, breed, age);
            }
            break;
        case 6:
            return;
        default:
            system("cls");
            std::cout << "Wrong option\n";
            break;
        }
    }
}

void hashMenu(HashTable hashTable) {
    while (true) {
        std::cout << "\nMenu\n";
        std::cout << "1. Show table\n";
        std::cout << "2. Add data\n";
        std::cout << "3. Delete data\n";
        std::cout << "4. Find data\n";
        std::cout << "5. Edit data\n";
        std::cout << "6. Find chance of collision\n";
        std::cout << "7. Exit\n";
        HashTable::Dog tempDog;
        int choise;
        int subchoise;
        std::string key;
        std::string name;
        std::string breed;
        int age;
        int ind;
        std::cin >> choise;

        switch (choise)
        {
        case 1:
            hashTable.showTable();
            break;
        case 2:
            std::cout << "Enter name, breed, age:\n";
            std::cin >> name >> breed >> age;
            hashTable.addData(name, breed, age);
            system("cls");
            break;
        case 3:
            std::cout << "Enter name:\n";
            std::cin >> key;
            ind = hashTable.searchData(key);
            if (ind == -1) {
                std::cout << "NotFound\n";
            }
            else {
                hashTable.deleteData(key);
            }
            system("cls");
            break;
        case 4:
            std::cout << "Enter name:\n";
            std::cin >> key;
            ind = hashTable.searchData(key);
            if (ind == -1) {
                std::cout << "NotFound\n";
            }
            else {
                tempDog = hashTable.showData(ind);
                std::cout << ind << " " << tempDog.name << " " << tempDog.breed << " " << tempDog.age << "\n";
            }
            break;
        case 5:
            std::cout << "Enter name:\n";
            std::cin >> key;
            ind = hashTable.searchData(key);
            if (ind == -1) {
                std::cout << "Not found\n";
            }
            else {
                tempDog = hashTable.showData(ind);
                
                std::cout << "Edit name? (1 - yes, 0 - no)\n";
                std::cin >> subchoise;
                if (subchoise)
                    std::cin >> name;
                else name = tempDog.name;

                std::cout << "Edit breed? (1 - yes, 0 - no)\n";
                std::cin >> subchoise;
                if (subchoise)
                    std::cin >> breed;
                else breed = tempDog.breed;

                std::cout << "Edit age? (1 - yes, 0 - no)\n";
                std::cin >> subchoise;
                if (subchoise)
                    std::cin >> age;
                else age = tempDog.age;

                hashTable.redactData(key, name, breed, age);
            }
            break;
        case 6:
            hashTable.chanceOfColision();
            break;
        case 7:
            return;
        default:
            system("cls");
            std::cout << "Wrong option\n";
            break;
        }
    }
}

int main()
{
    BasicTable basicTable(44);
    loadFromFile(basicTable);
    //basicMenu(basicTable);

    HashTable hashTable(44);
    hashTable.getData(basicTable.passData());
    hashMenu(hashTable);
}
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

int main()
{
    BasicTable basicTable(44);
    loadFromFile(basicTable);
    std::cout << "Basic table:\n";
    basicTable.showTable();
    basicTable.deleteData("Mark");
    basicTable.redactData("Hatiko", "HATIKO", "AKITA", 100);
    int ind = basicTable.searchData("Lola");
    if (ind)
        std::cout << "\nFound at " << ind << "\n\n";
    basicTable.showTable();

    HashTable hashTable(44);
    hashTable.getData(basicTable.passData());
    std::cout << "\nHash table:\n";
    hashTable.showTable();
    hashTable.deleteData("Dima");
    hashTable.redactData("Boba", "Boba", "SOBAKA", 999);
    ind = hashTable.searchData("David");
    if (ind)
        std::cout << "\nFound at " << ind << "\n\n";
    hashTable.showTable();
    hashTable.chanceOfColision();
}
#include <iostream>
#include "DataBase.h"

void menu() {
    int choise;
    std::string word;
    DataBase dataBase;
    dataBase.readDataBase("data_base.txt");
    while (true) {
        system("cls");
        std::cout << "Menu\n";
        std::cout << "1. Find word\n";
        std::cout << "2. Edit masc\n";
        std::cout << "3. Remove word\n";
        std::cout << "4. Add word\n";
        std::cout << "5. Show database\n";
        std::cout << "6. Exit\n";
        std::cin >> choise;
        switch (choise)
        {
        case 1:
            system("cls");
            std::cout << "Enter word: ";
            std::cin >> word;
            dataBase.find(word);
            system("pause");
            break;
        case 2:
            system("cls");
            dataBase.editMask();
            break;
        case 3:
            system("cls");
            std::cout << "Enter word: ";
            std::cin >> word;
            dataBase.remove(word);
            break;
        case 4:
            system("cls");
            std::cout << "Enter word: ";
            std::cin >> word;
            dataBase.add(word);
            system("pause");
            break;
        case 5:
            system("cls");
            dataBase.show();
            system("pause");
            break;
        case 6:
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
    return 0;
}
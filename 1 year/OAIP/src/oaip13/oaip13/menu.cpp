#include "menu.h"
void menu()
{
    short int menu;
    bool choise;
    int size = 0;
    product* shop = new product[size];
    product** index = new product * [size];
    TXTinput(shop, size, index);
    do {
        cout << endl << "Выберите действие: " << endl;
        cout << "1) Добавить продукт через консоль" << endl;
        cout << "2) Загрузить оригинальный список" << endl;
        cout << "3) Загрузить отсортированный список" << endl;
        cout << "4) Вывести весь список на консоль" << endl;
        cout << "5) Сортировка по названию" << endl;
        cout << "6) Сортировка по цене" << endl;
        cout << "7) Удаление продукта" << endl;
        cout << "0) Выход" << endl;
        cin >> menu;
        switch (menu) {
        case 1: {
            system("cls");
            input(shop, size, index);
            TXToutput(shop, size, index);
            sort(size, index, choise);
            sortedOutput(size, index, choise);
            break;
        }
        case 2: {
            system("cls");
            TXTinput(shop, size, index);
            break;
        }
        case 3: {
            system("cls");
            sortedInput(shop, size, index);
            break;
        }
        case 4: {
            system("cls");
            output(size, index);
            break;
        }
        case 5: {
            system("cls");
            choise = false;
            sort(size, index, choise);
            sortedOutput(size, index, choise);
            output(size, index);
            break;
        }
        case 6: {
            system("cls");
            choise = true;
            sort(size, index, choise);
            sortedOutput(size, index, choise);
            output(size, index);
            break;
        }
        case 7: {
            system("cls");
            TXTinput(shop, size, index);
            remove(shop, size, index);
            TXToutput(shop, size, index);
            sort(size, index, choise);
            sortedOutput(size, index, choise);
            break;
        }
        case 0:
            return;
        }
    } while (true);
}

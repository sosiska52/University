#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

enum Section { Рыбный = 1, Мясной, Хлебный, Растительность, Напитки };

union Selfmade {
    bool itIs;
    char ch;
};

struct product {
    char name[100];
    int ammount;
    double price;
    string date;
    Section section;
    Selfmade smade;
};

void input(product *&shop, int& size) {
    int newSize;
    int choiseForSection;
    cout << "Сколько продуктов нужно добавить?" << endl;
    cin >> newSize;
    size += newSize;
    product* temp = new product[size];
    for (int i = 0; i < size - newSize; i++)
        temp[i] = shop[i];
    shop = new product[size];
    for (int i = 0; i < size - newSize; i++)
        shop[i] = temp[i];
    delete[]temp;
    for (int i = size - newSize; i < size; i++) {
        cout << "Введите название продукта " << endl;
        cin >> shop[i].name;
        cout << "Введите кол-во продукта" << endl;
        cin >> shop[i].ammount;
        cout << "Введите цену продукта" << endl;
        cin >> shop[i].price;
        cout << "Введите дату поступления продукта" << endl;
        cin >> shop[i].date;
        cout << "Введите номер раздела продукта (1 - Рыбный, 2 - Мясной, 3 - Хлебный, 4 - Растительность, 5 - Напитки)" << endl;
        cin >> choiseForSection;
        shop[i].section = (Section)choiseForSection;
        cout << "Произведен ли продукт в Беларуси? (1 - да, 0 - нет)" << endl;
        cin >> shop[i].smade.itIs;
        if (shop[i].smade.itIs)
            shop[i].smade.ch = '+';
        else shop[i].smade.ch = '-';
        system("cls");
    }
}

void view(product shop[], int size) {
    cout << "№" << setw(15);
    cout << "Название:" << setw(15);
    cout << "Кол-во:" << setw(15);
    cout << "Цена:" << setw(25);
    cout << "Дата поступления:" << setw(20);
    cout << "Раздел:" << setw(25);
    cout << "Сделано ли в Бел:"<< endl;
    for (int i = 0; i < size; i++) {
            cout << i + 1 << setw(15);
            cout << shop[i].name << setw(15);
            cout << shop[i].ammount << setw(15);
            cout << shop[i].price << setw(25);
            cout << shop[i].date << setw(20);
            switch (shop[i].section) {
            case Рыбный:
                cout << "Рыбный" << setw(25);
                break;
            case Мясной:
                cout << "Мясной" << setw(25);
                break;
            case Хлебный:
                cout << "Хлебный" << setw(25);
                break;
            case Растительность:
                cout << "Растительность" << setw(25);
                break;
            case Напитки:
                cout << "Напитки" << setw(25);
                break;
            }
            cout << shop[i].smade.ch;
            cout << endl;
        }
}

void sort(product shop[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i; j < size; j++) {
            if (strcmp(shop[j].name, shop[i].name) < 0)
                swap(shop[i], shop[j]);
        }
    }
    system("cls");
}

void remove(product shop[], int &size) {
    for (int i = 0; i < size; i++) {
        cout << i << ": ";
        cout << "Название продукта: " << shop[i].name << endl;
    }
    cout << "Введите номер продукта который хотите удалить: ";
    int num;
    cin >> num;
    for (int i = num; i < size - 1; i++)
        shop[i] = shop[i + 1];
    size--;
    system("cls");
}

void maxPrise(product shop[], int size) {
    cout << "№" << setw(15);
    cout << "Название:" << setw(15);
    cout << "Кол-во:" << setw(15);
    cout << "Цена:" << setw(25);
    cout << "Дата поступления:" << setw(20);
    cout << "Раздел:" << setw(25);
    cout << "Сделано ли в Бел:" << endl;
    for (int i = 0; i < size; i++) {
        if (shop[i].price >= 100000) {
            cout << i + 1 << setw(15);
            cout << shop[i].name << setw(15);
            cout << shop[i].ammount << setw(15);
            cout << shop[i].price << setw(25);
            cout << shop[i].date << setw(20);
            switch (shop[i].section) {
            case Рыбный:
                cout << "Рыбный" << setw(25);
                break;
            case Мясной:
                cout << "Мясной" << setw(25);
                break;
            case Хлебный:
                cout << "Хлебный" << setw(25);
                break;
            case Растительность:
                cout << "Растительность" << setw(25);
                break;
            case Напитки:
                cout << "Напитки" << setw(25);
                break;
            }
            cout << shop[i].smade.ch;
            cout << endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    short int menu;
    int size = 0;
    product* shop = new product[size];
    do {
        cout << endl << "Выберите действие: " << endl;
        cout << "1) Добавить продукт" << endl;
        cout << "2) Вывести весь список" << endl;
        cout << "3) Сортировка по алфавиту" << endl;
        cout << "4) Удаление поля или строки" << endl;
        cout << "5) Товары с ценой больше 100 тыс" << endl;
        cout << "6) Выход" << endl;
        cin >> menu;
        switch (menu) {
        case 1: {
            input(shop, size);
            break;
        }
        case 2: {
            view(shop, size);
            break;
        }
        case 3: {
            sort(shop, size);
            break;
        }
        case 4: {
            remove(shop, size);
            break;
        }
        case 5: {
            maxPrise(shop, size);
            break;
        }
        case 6:
            return 0;
        }
    } while (true);
}


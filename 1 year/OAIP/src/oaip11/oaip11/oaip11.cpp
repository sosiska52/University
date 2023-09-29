#include <iostream>
#include <string.h>
#include <fstream>
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
    char date[10];
    Section section;
    Selfmade smade;
};

void input(product*& shop, int& size) {
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

void TXTinput(product*& shop, int& size) {
    ifstream fin("outputTXT.txt");
    fin >> size;
    cout << "Добавлен список с " << size << " продуктами" << endl;
    char tempp[1024];
    fin.getline(tempp, 1024, '\n');
    char temp[1024];
    fin.getline(tempp, 1024, '\n');
    for (int i = 0; i < size; i++) {
        fin >> shop[i].name;
        fin >> shop[i].ammount;
        fin >> shop[i].price;
        fin >> shop[i].date;
        fin >> tempp;
        if (strcmp(tempp, "Рыбный") == NULL) {
            shop[i].section = Рыбный;
        }
        else if (strcmp(tempp, "Мясной") == NULL) {
            shop[i].section = Мясной;
        }
        else if (strcmp(tempp, "Хлебный") == NULL) {
            shop[i].section = Хлебный;
        }
        else if (strcmp(tempp, "Растительность") == NULL) {
            shop[i].section = Растительность;
        }
        else if (strcmp(tempp, "Напитки") == NULL) {
            shop[i].section = Напитки;
        }
        fin >> shop[i].smade.ch;
    }
    fin.close();
}

void BINinput(product*& shop, int& size) {
    ifstream fbin("outputBIN.bin", ios_base::binary);
    fbin.read((char*)&size, sizeof(size));
    cout << "Добавлен список с " << size << " продуктами"<<endl;
    for (int i = 0; i < size; i++) {
        fbin.read((char*)&shop[i], sizeof(shop[i]));
    }
    fbin.close();
}

void output(product shop[], int size) {
    cout << setw(15) << left;
    cout << "Название:" << setw(15) << left;
    cout << "Кол-во:" << setw(15) << left;
    cout << "Цена:" << setw(25) << left;
    cout << "Дата поступления:" << setw(20) << left;
    cout << "Раздел:" << setw(25) << left;
    cout << "Сделано ли в Бел:" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(15) << left;
        cout << shop[i].name << setw(15) << left;
        cout << shop[i].ammount << setw(15) << left;
        cout << shop[i].price << setw(25) << left;
        cout << shop[i].date << setw(20) << left;
        switch (shop[i].section) {
        case Рыбный:
            cout << "Рыбный" << setw(25) << left;
            break;
        case Мясной:
            cout << "Мясной" << setw(25) << left;
            break;
        case Хлебный:
            cout << "Хлебный" << setw(25) << left;
            break;
        case Растительность:
            cout << "Растительность" << setw(25) << left;
            break;
        case Напитки:
            cout << "Напитки" << setw(25) << left;
            break;
        }
        cout << shop[i].smade.ch;
        cout << endl;
    }
}

void TXToutput(product shop[], int size) {
    ofstream fout("outputTXT.txt");
    fout << size << " всего." << endl;
    fout << setw(15) << left;
    fout << "Название:" << setw(15) << left;
    fout << "Кол-во:" << setw(15) << left;
    fout << "Цена:" << setw(25) << left;
    fout << "Дата поступления:" << setw(20) << left;
    fout << "Раздел:" << setw(25) << left;
    fout << "Сделано ли в Бел:" << endl;
    for (int i = 0; i < size; i++) {
        fout << setw(15) << left;
        fout << shop[i].name << setw(15) << left;
        fout << shop[i].ammount << setw(15) << left;
        fout << shop[i].price << setw(25) << left;
        fout << shop[i].date << setw(20) << left;
        switch (shop[i].section) {
        case Рыбный:
            fout << "Рыбный" << setw(25) << left;
            break;
        case Мясной:
            fout << "Мясной" << setw(25) << left;
            break;
        case Хлебный:
            fout << "Хлебный" << setw(25) << left;
            break;
        case Растительность:
            fout << "Растительность" << setw(25) << left;
            break;
        case Напитки:
            fout << "Напитки" << setw(25) << left;
            break;
        }
        fout << shop[i].smade.ch;
        fout << endl;
    }
    fout.close();
}

void BINoutput(product shop[], int size) {
    ofstream fbin("outputBIN.bin", ios_base::binary);
    fbin.write((char*)&size, sizeof(size));
    for (int i = 0; i < size; i++) {
        fbin.write((char*)&shop[i], sizeof(shop[i]));
    }
    fbin.close();
}

void sort(product shop[], int size) {
    for (int i = 0; i < size - 1; i++) {
        cout << "";
        for (int j = i; j < size; j++) {
            if (strcmp(shop[j].name, shop[i].name) < 0)
                swap(shop[i], shop[j]);
        }
    }
}

void remove(product shop[], int& size) {
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
        cout << "1) Добавить продукт через консоль" << endl;
        cout << "2) Добавить продукт через текстовый файл" << endl;
        cout << "3) Добавить продукт через бинарный файл" << endl;
        cout << "4) Вывести весь список на консоль" << endl;
        cout << "5) Вывести весь список в текстовый файл" << endl;
        cout << "6) Вывести весь список в бинораный файл" << endl;
        cout << "7) Сортировка по алфавиту" << endl;
        cout << "8) Удаление продукта" << endl;
        cout << "9) Нахождение наибольшей цены" << endl;
        cout << "0) Выход" << endl;
        cin >> menu;
        switch (menu) {
        case 1: {
            system("cls");
            input(shop, size);
            break;
        }
        case 2: {
            system("cls");
            TXTinput(shop, size);
            break;
        }
        case 3: {
            system("cls");
            BINinput(shop, size);
            break;
        }
        case 4: {
            system("cls");
            output(shop, size);
            break;
        }
        case 5: {
            system("cls");
            TXToutput(shop, size);
            break;
        }
        case 6: {
            system("cls");
            BINoutput(shop, size);
            break;
        }
        case 7: {
            system("cls");
            sort(shop, size);
            output(shop, size);
            break;
        }
        case 8: {
            system("cls");
            remove(shop, size);
            break;
        }
        case 9: {
            system("cls");
            maxPrise(shop, size);
            break;
        }
        case 0:
            return 0;
        }
    } while (true);
}
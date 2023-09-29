#include "FileTXT.h"

void TXTinput(product*& shop, int& size, product**& index) {
    ifstream fin("outputTXT.txt");
    fin >> size;
    cout << "Добавлен список с " << size << " продуктами" << endl;
    char tempp[1024];
    fin.getline(tempp, 1024, '\n');
    fin.getline(tempp, 1024, '\n');
    for (int i = 0; i < size; i++) {
        fin >> shop[i].index;
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
        index[i] = &shop[shop[i].index];
    }
    fin.close();
}

void TXToutput(product shop[], int size, product**& index) {
    ofstream fout("outputTXT.txt");
    fout << size << " всего." << endl;
    fout << setw(5) << left;
    fout << "N" << setw(15) << left;
    fout << "Название:" << setw(15) << left;
    fout << "Кол-во:" << setw(15) << left;
    fout << "Цена:" << setw(25) << left;
    fout << "Дата поступления:" << setw(20) << left;
    fout << "Раздел:" << setw(25) << left;
    fout << "Сделано ли в Бел:" << endl;
    for (int i = 0; i < size; i++) {
        fout << setw(5) << left;
        fout << shop[i].index << setw(15) << left;
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

void sortedOutput(int size, product**& index, bool choise) {
    ofstream fout("sorted.txt");
    fout << size << " всего." << endl;
    fout << setw(5) << left;
    fout << "N" << setw(15) << left;
    if (!choise) {
        fout << "Название:" << setw(15) << left << endl;
    }
    else {
        fout << "Цена:" << setw(25) << left << endl;
    }
    for (int i = 0; i < size; i++) {
        fout << setw(5) << left;
        fout << index[i]->index << setw(15) << left;
        if (!choise) {
            fout << index[i]->name << setw(15) << left;
        }
        else {
            fout << index[i]->price << setw(25) << left;
        }
        fout << endl;
    }
    fout.close();
}

void sortedInput(product shop[], int size, product**& index) {
    ifstream fin("sorted.txt");
    fin >> size;
    cout << "Добавлен список с " << size << " продуктами" << endl;
    char tempp[1024];
    fin.getline(tempp, 1024, '\n');
    fin.getline(tempp, 1024, '\n');
    int tempInt;
    for (int i = 0; i < size; i++) {
        fin >> tempInt;
        index[i] = &shop[tempInt];
        fin >> tempp;
    }
    fin.close();
}

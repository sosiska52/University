#include "Functions.h"

void input(product*& shop, int& size, product**& index)
{
    int newSize;
    int choiseForSection;
    cout << "������� ��������� ����� ��������?" << endl;
    cin >> newSize;
    size += newSize;
    product* temp = new product[size];
    product** tempi = new product * [size];
    for (int i = 0; i < size - newSize; i++) {
        temp[i] = shop[i];
        tempi[i] = index[i];
    }
    shop = new product[size];
    index = new product * [size];
    for (int i = 0; i < size - newSize; i++) {
        shop[i] = temp[i];
        index[i] = tempi[i];
    }
    delete[]temp;
    delete[]tempi;
    for (int i = size - newSize; i < size; i++) {
        shop[i].index = i;
        cout << "������� �������� �������� " << endl;
        cin >> shop[i].name;
        cout << "������� ���-�� ��������" << endl;
        cin >> shop[i].ammount;
        cout << "������� ���� ��������" << endl;
        cin >> shop[i].price;
        cout << "������� ���� ����������� ��������" << endl;
        cin >> shop[i].date;
        cout << "������� ����� ������� �������� (1 - ������, 2 - ������, 3 - �������, 4 - ��������������, 5 - �������)" << endl;
        cin >> choiseForSection;
        shop[i].section = (Section)choiseForSection;
        cout << "���������� �� ������� � ��������? (1 - ��, 0 - ���)" << endl;
        cin >> shop[i].smade.itIs;
        if (shop[i].smade.itIs)
            shop[i].smade.ch = '+';
        else shop[i].smade.ch = '-';
        index[i] = &shop[i];
        system("cls");
    }
}

void output(int size, product**& index) {
    cout << setw(5) << left;
    cout << "N" << setw(15) << left;
    cout << "��������:" << setw(15) << left;
    cout << "���-��:" << setw(15) << left;
    cout << "����:" << setw(25) << left;
    cout << "���� �����������:" << setw(20) << left;
    cout << "������:" << setw(25) << left;
    cout << "������� �� � ���:" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(5) << left;
        cout << index[i]->index << setw(15) << left;
        cout << index[i]->name << setw(15) << left;
        cout << index[i]->ammount << setw(15) << left;
        cout << index[i]->price << setw(25) << left;
        cout << index[i]->date << setw(20) << left;
        switch (index[i]->section) {
        case ������:
            cout << "������" << setw(25) << left;
            break;
        case ������:
            cout << "������" << setw(25) << left;
            break;
        case �������:
            cout << "�������" << setw(25) << left;
            break;
        case ��������������:
            cout << "��������������" << setw(25) << left;
            break;
        case �������:
            cout << "�������" << setw(25) << left;
            break;
        }
        cout << index[i]->smade.ch;
        cout << endl;
    }
}

void sort(int size, product**& index, bool& choise) {
    if (choise) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = i; j < size; j++) {
                if (index[i]->price < index[j]->price) {
                    swap(index[i], index[j]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < size - 1; i++) {
            for (int j = i; j < size; j++) {
                if (strcmp(index[i]->name, index[j]->name) > 0) {
                    swap(index[i], index[j]);
                }
            }
        }
    }
}

void remove(product shop[], int& size, product**& index) {
    for (int i = 0; i < size; i++) {
        cout << i << ": ";
        cout << "�������� ��������: " << index[i]->name << endl;
    }
    cout << "������� ����� �������� ������� ������ �������: ";
    int num, inum;
    cin >> num;
    inum = shop[num].index;
    for (int i = num; i < size - 1; i++) {
        shop[i] = shop[i + 1];
        index[i] = &shop[i];
        if (shop[i].index > inum) {
            shop[i].index--;
        }
    }
    size--;
}

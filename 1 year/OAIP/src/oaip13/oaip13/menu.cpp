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
        cout << endl << "�������� ��������: " << endl;
        cout << "1) �������� ������� ����� �������" << endl;
        cout << "2) ��������� ������������ ������" << endl;
        cout << "3) ��������� ��������������� ������" << endl;
        cout << "4) ������� ���� ������ �� �������" << endl;
        cout << "5) ���������� �� ��������" << endl;
        cout << "6) ���������� �� ����" << endl;
        cout << "7) �������� ��������" << endl;
        cout << "0) �����" << endl;
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

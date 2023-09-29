#include <iostream>
#include "Func.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите Х0 и параметр b(2,10): " << endl;
    int a = 9; //Макаревич
    double x0, b;
    cin >> x0 >> b;
    while (true) {
        if (b >= 2 && b <= 10)
            break;
        else {
            cout << "Параметр b выходит за рамки, введите заново." << endl;
            cin >> b;
        }
    }
    cout << "Введите максимальное кол-во итераций: " << endl;
    int Nmax;
    cin >> Nmax;
    double res = threadsFunc(x0, a, b, Nmax);
    cout << "SOLUTION: " << res << endl;
    return 0;
    }
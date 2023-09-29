// TMOIS4_leetcode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
class Solution {
public:
    int maxArea(vector<int>& height) {
        int lInd = 0;
        int rtInd = height.size() - 1;
        int lHeight = height[lInd];
        int rHeight = height[rInd];
        int square = 0;
        while (rInd > lInd) {
            if (left < right) {
                if ((rInd - lInd) * lHeight > square) {
                    square = (rInd - lInd) * lHeight;
                }
                lInd++;
                lHeight = height[lInd];
            }
            else {
                if ((rInd - lInd) * right > square) {
                    square = (rInd - lInd) * right;
                }
                rInd--;
                right = height[rInd];
            }
        }
        return square;
    }
};
int main()
{
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <iostream>
#include <cmath>
using namespace std;

void boolean(int ar[], int size)
{
    int p = pow(2, size);
    cout << "B(A)={\n{ }\n ";
    for (int i = 1; i < p; i++)
    {
        cout << "{";
        for (int j = 0; j < size; j++)
        {
            if (i & (1 << j))
                cout << ar[j] << " ";
        }
        cout << "} \n";
    }
    cout << "}";
}

int main()
{
    int a[] = { 2,3,4,5 };
    int sizeA = 4;
    boolean(a, sizeA);
    return 0;
}

#include <iostream>
using namespace std;
int fact2(int num)
{
    if (num > 2)
        return num * fact2(num - 2);
    return 1;
}
int main()
{
    cout << "Enter number\n";
    int n;
    cin >> n;
    int res = fact2(n);
    cout << res;
}
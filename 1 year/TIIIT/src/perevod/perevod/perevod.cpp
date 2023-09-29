#include <iostream>
#include <stack>
#include <cmath>

int to_abc(int a)
{
    a -= 10;
    a += 'A';
        return a;
}

using namespace std;
int main()
{
    cout << "enter number and it's base:\n";
    int  base, ss;
    string num;
    cin >> num >> base;
    cout << "enter new base:\n";
    cin >> ss;
    if (base == ss)
        cout << num;
    else
    {       //перевод в 10
        int n = 0, inum, stepen = num.length();
        for (int i = 0; i < num.length(); i++)
        {
            inum = num[i] - '0';
            if (inum > 9)
                inum = num[i] - 'A' + 10;
            stepen--;
            n = n + (inum * pow(base, stepen));
        }
        if (ss == 10)
            cout << n << endl;
        else
        {
            int buf, i = 1;
            stack <char> steck;
            while (n * ss >= ss)    //из 10 в любую
            {
                buf = n;
                n /= ss;
                buf %= ss;
                if (buf > 9)    //проверка на букву
                {
                    buf = to_abc(buf);
                    steck.push(buf);
                }
                else
                {
                    buf += '0';
                    steck.push(buf);
                }
                i++;
            }
            for (i; i > 1; i--) //вывод
            {
                cout << steck.top();
                steck.pop();
            }
        }
    }
    return 0;
}
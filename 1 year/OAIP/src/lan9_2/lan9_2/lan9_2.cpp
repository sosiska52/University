#include <iostream>
#include <string>
using namespace std;

string fillString(string s, int n)
{
    string st;
    int cel = n / s.length();
    int ncel = n - cel * s.length();
    for (int i = 0; i < cel; i++)
        st += s;
    for (int i = 0; i < ncel; i++)
        st += s[i];
    return st;
}

int main()
{
    cout << "Enter string:\n";
    string str;
    cin >> str;
    cout << "Enter length:\n";
    int l;
    cin >> l;
    cout << fillString(str, l);
}
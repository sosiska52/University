#include <iostream>
using namespace std;

int NMax(int a[], int n)
{
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	 }
	return max;
}

int main()
{
	cout << "enter lengthes of arrays\n";
	int an,bn,cn;
	cin >> an >> bn >> cn;
	int* a = new int[an];
	int* b = new int[bn];
	int* c = new int[cn];
	cout << "enter A array\n";
	for (int i = 0; i < an; i++)
		cin >> a[i];
	cout << "enter B array\n";
	for (int i = 0; i < bn; i++)
		cin >> b[i];
	cout << "enter C array\n";
	for (int i = 0; i < cn; i++)
		cin >> c[i];
	int am, bm, cm;
	am = NMax(a, an);
	bm = NMax(b, bn);
	cm = NMax(c, cn);
	cout << "Max in A: " << am << endl;
	cout << "Max in B: " << bm << endl;
	cout << "Max in C: " << cm << endl;
	return 0;
}
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

void boolean(int ar[], int size)
{
	int p = pow(2, size);
	cout << "Bulian of a set of numbers:{\n{ }\n ";
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

void merge(int a[], int b[], int sa, int sb)
{
	int size = sa + sb;
	int* sorted = new int[size];
	int i = 0, j = 0, k = 0;
	while (i != sa && j != sb)
	{
		if (a[i] > b[j])
		{
			sorted[k] = b[j];
			k++;
			j++;
		}
		if (a[i] < b[j])
		{
			sorted[k] = a[i];
			k++;
			i++;
		}
		if (a[i] == b[j])
		{
			sorted[k] = a[i];
			k++;
			sorted[k] = b[j];
			k++;
			i++;
			j++;
		}
	}

	if (i + 1 == sa && j + 1 == sb);
	else
	{
		while (i < sa)
		{
			sorted[k] = a[i];
			k++;
			i++;
		}
		while (j < sa)
		{
			sorted[k] = b[j];
			k++;
			j++;
		}
	}
	cout << "Result of merging: ";
	for (int i = 0; i < size; i++)
		cout << sorted[i] << " ";
}

void combination(int a[], int b[], int u[], int sa, int sb, int su)
{
	queue<bool>comb;
	int check = 0;
	for (int i = 0; i < su; i++)
	{
		for (int j = 0; j < sa && j < sb; j++)
			if (u[i] == a[j] || u[i] == b[j])
				check++;
		if (check != 0)
			comb.push(true);
		else
			comb.push(false);
		check = 0;
	}
	for (int i = 0; i < su; i++)
	{
		if (comb.front())
			cout << u[i] << " ";
		comb.pop();
	}
}

void intersection(int a[], int b[], int sa, int sb)
{
	queue <int> inter;
	int size = 0;
	for (int i = 0; i < sb; i++)
	{
		for (int j = 0; j < sa; j++)
			if (a[j] == b[i])
			{
				inter.push(a[j]);
				size++;
			}
	}
	cout << "Result of intersection: ";
	for (int i = 0; i < size; i++)
	{
		cout << inter.front() << " ";
		inter.pop();
	}
}

void  difference(int a[], int b[], int sa, int sb)
{
	queue <int> diff;
	int size = 0;
	int check = 0;
	for (int i = 0; i < sa; i++)
	{
		for (int j = 0; j < sb; j++)
		{
			if (a[i] != b[j])
				check++;
		}
		if (check == sb)
		{
			diff.push(a[i]);
			size++;
		}
		check = 0;
	}

	cout << "Result of difference: ";
	for (int i = 0; i < size; i++)
	{
		cout << diff.front() << " ";
		diff.pop();
	}
}

void symdifference(int a[], int b[], int sa, int sb)
{
	queue <int> sdiff;
	int size = 0;
	int check = 0;
	for (int i = 0; i < sa; i++)
	{
		for (int j = 0; j < sb; j++)
		{
			if (a[i] != b[j])
				check++;
		}
		if (check == sb)
		{
			sdiff.push(a[i]);
			size++;
		}
		check = 0;
	}
	for (int i = 0; i < sb; i++)
	{
		for (int j = 0; j < sa; j++)
		{
			if (a[j] != b[i])
				check++;
		}
		if (check == sb)
		{
			sdiff.push(b[i]);
			size++;
		}
		check = 0;
	}

	cout << "Result of difference: ";
	for (int i = 0; i < size; i++)
	{
		cout << sdiff.front() << " ";
		sdiff.pop();
	}

}

void addition(int a[], int u[], int sa, int su)
{
	queue<int>add;
	int size = 0;
	int check = 0;
	for (int i = 0; i < su; i++)
	{
		for (int j = 0; j < sa; j++)
		{
			if (u[i] != a[j])
				check++;
		}
		if (check == sa)
		{
			size++;
			add.push(u[i]);
		}
		check = 0;
	}

	cout << "Result of difference: ";
	for (int i = 0; i < size; i++)
	{
		cout << add.front() << " ";
		add.pop();
	}

}

void expression()
{

}

int main()
{
	int U[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11 };
	int a[] = { 2,3,4,5 };
	int b[] = { 3,4,6,7 };
	int c[] = { 4,8,9 };
	int sizeA = 4;
	int sizeB = 4;
	int sizeC = 3;
	int sizeU = 11;
	cout << "////////////////////////////////////////\n";
	//boolean(a, sizeA);
	cout << "\n////////////////////////////////////////\n";
	//merge(a, b, sizeA, sizeB);
	cout << "\n////////////////////////////////////////\n";
	//combination(a, b, U, sizeA, sizeB, sizeU);
	cout << "\n////////////////////////////////////////\n";
	//intersection(a, b, sizeA, sizeB);
	cout << "\n////////////////////////////////////////\n";
	//difference(a, b, sizeA, sizeB);
	cout << "\n////////////////////////////////////////\n";
	//symdifference(a, b, sizeA, sizeB);
	cout << "\n////////////////////////////////////////\n";
	//addition(a, U, sizeA, sizeU);
	cout << "\n////////////////////////////////////////\n";
	cout<<"expression: "<<
	return 0;
}
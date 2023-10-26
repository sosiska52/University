#include <iostream>
#include <fstream>

using namespace std;

class Substitution {
private:
	int size = 6;
	int subs[6];
	int cycle[6];
public:
	Substitution(string name) {
		ifstream fin(name);
		for (int i = 0; i < size; i++) {
			fin >> subs[i];
			subs[i]--;
		}
		fin.close();
	}

	void makeCycle() {
		int ind = 0;
		for (int i = 0; i < size; i++) {
			cycle[i] = subs[ind];
			ind = cycle[i];
		}
	}

	void makeTransposition() {
		ofstream fout("Transposition.txt");
		fout << "( ";
		for (int i = 0; i < size; i++)
			fout << cycle[i] + 1 << " ";
		fout << ") = ";
		for (int i = 1; i < size; i++) {
			fout << "( " << cycle[0] + 1 << ", " << cycle[i] + 1 << " )";
		}
		fout.close();
	}

	int degree() {
		int res = 1;
		for (int i = 1; i <= size; i++)
			res = res * i;
		return res;
	}


};

int main() {
	Substitution task1("input.txt");
	task1.makeCycle();
	task1.makeTransposition();
	cout << task1.degree() << endl;
	return 0;
}
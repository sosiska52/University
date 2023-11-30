#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

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

	bool checkOdd() {
		int sum = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i < subs[j])
					sum++;
				else if (i == subs[j])
					break;
			}
		}
		if (sum % 2 == 0)
			return true;
		else return false;
	}
};

class Group {
private:
	vector <int> arr;

	bool is_cyclic;

	vector<vector <int>> subgroups;

	void makeKely(vector <int> arr) {
		ofstream fout("KelySub.txt");

		fout << "*(5)";
		for (int i = 0; i < arr.size(); i++)
			fout << "\t" << arr[i];
		fout << "\n";

		for (int i = 0; i < arr.size(); i++) {
			fout << arr[i];
			for (int j = 0; j < arr.size(); j++) {
				int prod = (arr[i] * arr[j]) % 5;
				fout << "\t" << prod;
			}
			fout << "\n";
		}

		fout.close();
	}

	int multiply(int a, int b){
		return (a * b) % 5;
	}

	vector<vector<int>> leftCosets(const vector<int>& subgroup) {
		vector<vector<int>> cosets;

		for (int element : arr) {
			vector<int> coset;

			for (int subgroupElement : subgroup) {
				int result = multiply(element, subgroupElement);
				coset.push_back(result);
			}
			cosets.push_back(coset);
		}
		return cosets;
	}

	vector<vector<int>> factorSet(const vector<vector<int>>& cosets) {
		vector<vector<int>> factorSet;

		for (const vector<int>& coset : cosets) {
			factorSet.push_back(coset);
		}
		return factorSet;
	}

	void printVecVec(vector<vector<int>> group, string filename, string message) {
		ofstream fout(filename, ios::app);
		fout << message;
		for (const vector<int>& vec : group){
			fout << "{ ";
			for (int element : vec){
				fout << element << " ";
			}
			fout << "} ";
		}
		fout << "\n";
		fout.close();
	}

public:
	Group(string name){
		is_cyclic = NULL;

		ifstream fin(name);
		int num;
		while (fin >> num) {
			arr.push_back(num);
		}
		fin.close();
	}

	void makeKely() {
		ofstream fout("Kely.txt");

		fout << "*(5)";
		for (int i = 0; i < arr.size(); i++)
			fout << "\t" << arr[i];
		fout << "\n";

		for (int i = 0; i < arr.size(); i++) {
			fout << arr[i];
			for (int j = 0; j < arr.size(); j++){
				int prod = (arr[i] * arr[j]) % 5;
				fout << "\t" << prod;
			}
			fout << "\n";
		}

		fout.close();
	}

	int findNeutral() {
		int check = 0;
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr.size(); j++) {
				if (arr[i] * arr[j] % 5 == arr[j])
					check++;
			}
			if (check == arr.size())
				return arr[i];
		}
		return -1;
	}

	void findInverse() {
		ofstream fout("Inverse.txt");
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr.size(); j++) {
				if ((arr[i] * arr[j]) % 5 == findNeutral()) {
					fout << arr[i] << "\t" << arr[j] << "\n";
				}
			}
		}
		fout.close();
	}

	void findSubgroups() {
		ofstream fout("Subgroups.txt");
		int neutral = findNeutral();
		for (int i = 0; i < arr.size(); i++) {
			vector <int> group;
			int current = arr[i];
			group.push_back(current);
			int order = 1;
			while (current != neutral) {
				order++;
				current = current * arr[i] % 5;
				group.push_back(current);
			}
			sort(group.begin(), group.end());

			subgroups.push_back(group);

			fout << "Element " << arr[i] << " generates ( ";
			for (int i = 0; i < group.size(); i++)
				fout << group[i] << " ";
			fout << ") subgroup with order = " << order << "\n";
			if (order == arr.size())
				is_cyclic = true;
			if (order == 2)
				makeKely(group);
		}
		fout.close();
	}

	bool isCyclic() {
		if (is_cyclic == NULL)
			findSubgroups();
		return is_cyclic;
	}

	void printCosetsFactorsets() {
		if (subgroups.empty())
			findSubgroups();

		for (int i = 0; i < subgroups.size(); i++) {
			vector<vector<int>> cosets = leftCosets(subgroups[i]);
			vector<vector<int>> factor = factorSet(cosets);

			string message = "Left cosets for ";
			message.append(to_string(i+1));
			message.append(" subgroup: ");
			printVecVec(cosets, "Cosets.txt", message);

			message = "Factor sets for ";
			message.append(to_string(i + 1));
			message.append(" subgroup: ");
			printVecVec(factor, "Factors.txt", message);
		}
	}
};

int main() {
	Substitution task1("substitution.txt");
	task1.makeCycle();
	task1.makeTransposition();
	cout << "Degree: " << task1.degree() << "\n";
	cout << "Is it odd: " << task1.checkOdd() << "\n\n";

	Group task2("group.txt");
	task2.makeKely();
	cout << "Neutral element: " << task2.findNeutral() << "\n";
	task2.findInverse();
	task2.findSubgroups();
	cout << "Is it cyclic: " << task2.isCyclic() << "\n";
	task2.printCosetsFactorsets();
	return 0;
}
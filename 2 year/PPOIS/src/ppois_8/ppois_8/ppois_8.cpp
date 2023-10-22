#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Grade {
private:
	string subject;
	char grade;

	void nullInitialization() {
		subject = "Unknown";
		grade = '-';
	}
public:
	Grade() {
		nullInitialization();
	}
	Grade(string subject, char grade) {
		this->subject = subject;
		this->grade = grade;
	}
	Grade(const Grade& temp) {
		this->subject = temp.subject;
		this->grade = temp.grade;
	}

	void fread(string name, int start) {
		ifstream fin(name);
		if (fin.is_open()) {
			for (int i = 0; i <= start; i++) {
				getline(fin, subject, '\t');
				grade = fin.get();
			}
		}
		else nullInitialization();
		fin.close();
	}

	void fwrite(string name) {
		ofstream fout(name, ios::app);
		fout << subject << "\t";
		fout.put(grade);
		fout.close();
	}
};

int main() {
	string str;
	cout << "Enter string: ";
	str = cin.get();
	cout << str << endl;
	getline(cin, str);
	cout << str << endl;

	char ch = 'W';
	cout.put(ch) << endl;

	ofstream fout("output1.txt");
	ifstream fin("input1.txt");
	str = fin.get();
	fout << str << endl;
	getline(fin, str);
	fout << str << endl;
	fin.close();
	fout.close();

	double num = 1.123456789;
	cout << setprecision(4) << num << endl;
	cout << setfill('-') << setw(20) << right << num << endl;
	bool flag = true;
	cout << flag << endl;
	cout << boolalpha << flag << endl;
	cout << noboolalpha << flag << endl;
	int num2 = 28;
	cout << hex << num2 << endl;
	cout << showbase << num2 << endl;

	Grade nikita[4];
	for (int i = 0; i < 4; i++)
		nikita[i].fread("input2.txt", i);
	for (int i = 0; i < 4; i++)
		nikita[i].fwrite("output2.txt");
	return 0;
}
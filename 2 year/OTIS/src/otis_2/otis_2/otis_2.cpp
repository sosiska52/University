#include <iostream>
#include <cmath>
#include <queue>
#include <fstream>

using namespace std;

class Function {
private:
	double a = 0.6;
	double b = 0.5;
	double c = 0.65;
	double d = 1.1;
	double u = 4.1;

	double k = 0.003;
	double t = 100;
	double td = 110;
	double t0 = 1;
	double w = 20;

	double y0;
	double y1;

	double e0;
	double e1;
	double e2;

	double u0;
	double u1;

	double q0 = k * (1 + td / t0);
	double q1 = -k * (1 + 2 * td / t0 - t0 / t);
	double q2 = k * td / t0;

	void shift(double a, double b, double c, double next) {
		a = b;
		b = c;
		c = next;
	}

	void shift(double a, double b, double next) {
		a = b;
		b = next;
	}

public:
	void func(double cur, double prev) {
		ofstream yfout;
		yfout.open("y.txt");
		ofstream ufout;
		yfout.open("u.txt");
		ofstream efout;
		yfout.open("e.txt");
		int i = 0;
		y0 = prev;
		y1 = cur;
		e0 = 0;
		e1 = 0;
		e2 = 0;
		u0 = 1;
		u1 = 1;
		while (abs(w - y1) > 0.5 && i < 20) {
			//cout << w - y1 << endl;
			cout << i << " " << e2 << endl;
			cout <<"::"<< e0 << " " << e1 << " " << e2 << endl;
			shift(e0, e1, e2, w - y1);
			cout <<"::"<< e0 << " " << e1 << " " << e2 << endl;
			u = u1 + q0 * e2 + q1 * e1 + q2 * e0;
			double next = a * y1 - b * y0 * y0 + c * u + d * sin(u1);
			cout << i << " " << y1 << endl;
			shift(y0, y1, next);
			cout << i << " " << u1 << endl;;
			shift(u0, u1, u);
			i++;
		}
		cout << i;
	}
};




int main()
{
	double cur = 0.6;
	double prev = 0.3;
	Function func;
	func.func(cur, prev);
	return 0;
}
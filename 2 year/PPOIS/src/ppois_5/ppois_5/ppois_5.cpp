#include <iostream>

using namespace std;

class MachineGun {
public:
	void fire() {
		cout << "RATATATATA" << endl;
	}
};

class Revolver {
public:
	void fire() {
		cout << "POW" << endl;
	}
};

class Glock : public MachineGun, public Revolver {
private:
	bool mode;
public:
	void changeMode() {
		mode = !mode;
	}

	void fire() {
		if (mode)
			Revolver::fire();
		else MachineGun::fire();
	}
};

int main() {
	Glock glock;
	glock.fire();
	glock.changeMode();
	glock.fire();
	return 0;
}
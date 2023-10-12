#include <iostream>

using namespace std;

class MachineGun {
private:
	int mag;
public:
	MachineGun(int temp) {
		this->mag = temp;
	}

	void fire() {
		cout << "RATATATATA" << endl;
	}
};

class Revolver {
private:
	string name;
public:
	Revolver(string name) {
		this->name = name;
	}

	void fire() {
		cout << "POW" << endl;
	}
};

class Glock : public MachineGun, public Revolver {
private:
	bool mode;
public:
	Glock(int temp, string name) : MachineGun(temp), Revolver(name) {
		mode = false;
	}
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
	Glock glock(12, "Pistol");
	glock.fire();
	glock.changeMode();
	glock.fire();
	return 0;
}
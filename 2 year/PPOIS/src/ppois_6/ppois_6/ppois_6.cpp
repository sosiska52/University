#include <iostream>

using namespace std;

class Weapon {
protected:
	string name;
	int maxCapacity;
	bool* magazine;
	int bulletsLeft;
	int ind;
public:
	int showRemainingBullets() { return bulletsLeft; }

	string showName() { return name; }

	void reload() {
		for (int i = 0; i < ind; i++)
			magazine[i] = true;
		bulletsLeft = maxCapacity;
		ind = 0;
		cout << "reloaded" << endl;
	}

	virtual void fire() {
		throw "Error";
	}
};

class MachineGun : virtual public Weapon {
public:
	MachineGun(string name) {
		this->name = name;
		maxCapacity = 150;
		bulletsLeft = 0;
		ind = 0;
		magazine = new bool[maxCapacity];
	}
	MachineGun() {
		this->name = "Unnamed";
		maxCapacity = 150;
		bulletsLeft = 0;
		ind = 0;
		magazine = new bool[maxCapacity];
	}

	void fire() {
		if (bulletsLeft >= 5) {
			cout << "RATATATATA" << endl;
			bulletsLeft -= 5;
			ind += 5;
			for (int i = 0; i < ind; i++)
				magazine[i] = false;
		}
		else {
			throw "Error: No ammo";
		}
	}
};

class Revolver :virtual public Weapon {
public:
	Revolver(string name) {
		this->name = name;
		maxCapacity = 6;
		bulletsLeft = 0;
		ind = 0;
		magazine = new bool[maxCapacity];
	}
	Revolver() {
		this->name = "Unnamed";
		maxCapacity = 6;
		bulletsLeft = 0;
		ind = 0;
		magazine = new bool[maxCapacity];
	}

	void fire() {
		if (bulletsLeft >= 1) {
			cout << "POW" << endl;
			bulletsLeft--;
			magazine[ind] = false;
			ind++;
		}
		else {
			throw "Error: No ammo";
		}
	}
};

class Glock :public Revolver, public MachineGun {
private:
	bool onBurstMode;
public:
	Glock(string name) {
		this->name = name;
		maxCapacity = 15;
		bulletsLeft = 0;
		ind = 0;
		magazine = new bool[maxCapacity];
		onBurstMode = false;
	}

	void changeMode() { 
		onBurstMode = !onBurstMode;
	}

	void fire();
};

void Glock::fire() {
	if (onBurstMode)
		MachineGun::fire();
	else Revolver::fire();
}

int main() {
	Glock glock("7");
	try {
		glock.fire();
	}
	catch (const char* str) {
		cout << str << endl;
		glock.reload();
	}
	try {
		glock.fire();
		glock.changeMode();
		glock.fire();
	}
	catch (const char* str) {
		cout << str << endl;
		glock.reload();
	}
	cout << glock.showRemainingBullets();
	return 0;
}
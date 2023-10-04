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
		cout << "ERROR" << endl;
	}
};

class MachineGun : public Weapon {
public:
	MachineGun(string name) {
		this->name = name;
		maxCapacity = 150;
		bulletsLeft = 0;
		ind = 0;
		magazine = new bool[maxCapacity];
	}

	void fire() {
		if(bulletsLeft >= 5){
			cout << "RATATATATA" << endl;
			bulletsLeft -= 5;
			ind += 5;
			for (int i = 0; i < ind; i++)
				magazine[i] = false;
		}
		else {
			cout << "NO AMMO" << endl;
		}
	}
};

class Revolver : public Weapon {
public:
	Revolver(string name) {
		this->name = name;
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
			ind ++;
		}
		else {
			cout << "NO AMMO" << endl;
		}
	}
};

int main() {
	Weapon* weapon = new Weapon;
	weapon->fire();
	MachineGun machineGun("Gatling");
	weapon = &machineGun;
	weapon->reload();
	weapon->fire();
	Revolver rev("Magnum");
	rev.reload();
	while(rev.showRemainingBullets() > 0)
		rev.fire();
	rev.fire();
	return 0;
}
#include <iostream>
#include "Fest.h"

int main() {
	int choise;
	std::string name = "";
	Fest festival(name);
	while (true) {
		system("cls");
		std::cout << "1. Set up festival\n";
		std::cout << "2. Add band\n";
		std::cout << "3. Start festival\n";
		std::cout << "4.Exit\n";
		std::cin >> choise;
		switch (choise)
		{
		case 1: 
			system("cls");
			std::cout << "Enter name: ";
			std::cin >> name;
			festival = Fest(name);
			break;
		case 2:
			system("cls");
			std::cout << "Enter name: ";
			std::cin >> name;
			festival.addBand(name);
			break;
		case 3:
			system("cls");
			festival.start();
			system("pause");
			break;
		case 4:
			return 0;
		default:
			std::cout << "Wrong option\n";
			break;
		}
	}
}
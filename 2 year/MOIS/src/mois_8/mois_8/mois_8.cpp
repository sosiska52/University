#include <iostream>
#include <fstream>
#include <vector>

void makeMagaradga(int length) {
	std::vector<std::vector<int>> matrix(length, std::vector<int>(length, 0));


}

void menu() {
	int choise;
	int length = NULL;
	while (true) {
		std::cout << "Menu\n";
		std::cout << "1)Make matrix\n";
		std::cout << "2)Exit\n";
		std::cin >> choise;
		switch (choise)
		{
		case 1:
			system("cls");
			std::cout << "Enter length: ";
			std::cin >> length;

		default:
			system("cls");
			std::cout << "Wrong choise\n";
			system("pause");
			system("cls");
			break;
		}
	}
}

int main()
{
	menu();
	return 0;
}
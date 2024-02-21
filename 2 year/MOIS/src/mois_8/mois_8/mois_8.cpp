#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <string>
#include <codecvt>
#include <windows.h>
#include <sstream>
#include <ctime>

std::wstring convertToWstring(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

void placeMagaradga(int i1, int j1, std::vector<std::vector<int>> &matrix, int length) {
	for (int i = 0; i < length; i++) {
		matrix[i1][i] = 1;
		matrix[i][j1] = 1;
		for (int j = 0; j < length; j++) {
			if (std::abs(i - i1) == std::abs(j - j1)) {
				matrix[i][j] = 1;
			}
			if ((std::abs(i - i1) == 2 && std::abs(j - j1) == 1) ||
				(std::abs(i - i1) == 1 && std::abs(j - j1) == 2)) {
				matrix[i][j] = 1;
			}
		}
	}

	matrix[i1][j1] = 2;
}

void tryMagaradga(int i1, int j1, std::vector<std::vector<int>> matrix, int length, const std::string folderPath) {
	placeMagaradga(i1, j1, matrix, length);
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (matrix[i][j] == 0)
				placeMagaradga(i, j, matrix, length);
		}
	}

	std::string fileName = std::to_string(i1) + "-" + std::to_string(j1) + ".txt";
	std::ofstream fout;
	fout.open(folderPath + "\\" + fileName);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (matrix[i][j] == 1)
				fout << "* ";
			else fout << "M ";
		}
		fout << "\n";
	}
	fout.close();
}

void makeMagaradga(int length) {
	std::vector<std::vector<int>> matrix(length, std::vector<int>(length, 0)); //matrix filled with 0

	//creating folder name
	std::string tempName = "E:\\otisGIT\\University\\2 year\\MOIS\\src\\mois_8\\mois_8\\Magaradga_" + std::to_string(length);
	const std::wstring folderPath = convertToWstring(tempName);

	//trying all starting possitions
	if (CreateDirectoryW(folderPath.c_str(), NULL)) {
		clock_t start = clock();

		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				tryMagaradga(i, j, matrix, length, tempName);
			}
		}

		clock_t end = clock();
		double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC; // Вычисляем прошедшее время в секундах

		std::cout << "Time passed: " << elapsedTime << " secconds.\n Created " << length * length << "files\n";
	}
	else {
		DWORD errorCode = GetLastError();
		if (errorCode == ERROR_ALREADY_EXISTS) {
			std::cout << "Folder already exist\n";
		}
		else {
			std::cout << "Didn't succesed. Error code: " << errorCode <<"\n";
		}
	}

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
			makeMagaradga(length);
			break;
		case 2:
			return;
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
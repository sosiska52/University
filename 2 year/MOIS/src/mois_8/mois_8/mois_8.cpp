#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <string>
#include <codecvt>
#include <windows.h>
#include <sstream>
#include <ctime>

void printBoard(std::vector <std::vector<int>> matrix) {
	std::ofstream fout;
	fout.open("Magaradga_" + std::to_string(matrix.size()) + ".txt");

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++)
			if (matrix[i][j])
				fout << "M ";
			else
				fout << "* ";
		fout << "\n";
	}
	fout.close();
}

bool isValid(std::vector<std::vector<int>> matrix, int row, int col) {
	for (int i = 0; i < col; i++) //check whether there is queen in the left or not
		if (matrix[row][i])
			return false;
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (matrix[i][j]) //check whether there is queen in the left upper diagonal or not
			return false;
	for (int i = row, j = col; j >= 0 && i < matrix.size(); i++, j--)
		if (matrix[i][j]) //check whether there is queen in the left lower diagonal or not
			return false;

	int size = matrix.size();

	// Позиции, на которых может находиться конь
	int knightRow[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int knightCol[] = { -1, 1, -2, 2, -2, 2, -1, 1 };

	for (int k = 0; k < 8; k++) {
		int nextRow = row + knightRow[k];
		int nextCol = col + knightCol[k];

		// Проверяем, что следующая позиция находится в пределах доски
		if (nextRow >= 0 && nextRow < size && nextCol >= 0 && nextCol < size) {
			// Проверяем, есть ли на следующей позиции конь
			if (matrix[nextRow][nextCol] == 1) {
				return false;
			}
		}
	}

	return true;
}

bool tryMagaradga( int j1, std::vector<std::vector<int>>& matrix, int length) {
	if (j1 >= length) //when N queens are placed successfully
		return true;
	for (int i = 0; i < length; i++) { //for each row, check placing of queen is possible or not
		if (isValid(matrix, i, j1)) {
			matrix[i][j1] = 1; //if validate, place the queen at place (i, col)
			if (tryMagaradga(j1 + 1, matrix, length)) //Go for the other columns recursively
				return true;
			matrix[i][j1] = 0;
		}
	}
	return false; //when no possible order is found
}

double makeMagaradga(int length) {
	std::vector<std::vector<int>> matrix(length, std::vector<int>(length, 0)); //matrix filled with 0

		clock_t start = clock();

		if (!tryMagaradga(0, matrix, length)) {
			std::cout << "Solution doesn't exist.\n";
			return 0;
		}
		//else std::cout << length << " DONE\n";
		else printBoard(matrix);

		clock_t end = clock();
		double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC; // Вычисляем прошедшее время в секундах

		std::cout << "Time passed: " << elapsedTime << " secconds.\n\n";

		return elapsedTime;
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
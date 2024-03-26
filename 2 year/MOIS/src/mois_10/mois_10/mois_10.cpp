#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void makeMatrix(std::string path, std::vector <std::vector <int>>& matrix) {
    std::ifstream fin;
    fin.open(path);

    for (int i = 0; i < matrix.size(); i++) 
        for (int j = 0; j < matrix.size(); j++) 
            fin >> matrix[i][j];

    fin.close();
}

std::pair <int, int> findMin(std::vector <int> vec, std::vector <bool> isVisited) {
    int minWeight = 999;
    int minId = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (!isVisited[i] && vec[i] < minWeight) {
            minWeight = vec[i];
            minId = i;
        }
    }
    return std::make_pair(minId,minWeight);
}

std::pair<std::vector<int>, int> findPath(std::vector <std::vector <int>>& matrix, int curNode) {
    std::vector <int> minPath;
    std::vector <bool> isVisited(matrix.size(), false);
    int minWeight = 0;
    std::pair <int, int> temp;

    //std::cout << "Min Path: ";
    for (int i = 0; i < matrix.size(); i++) {
        //std::cout << curNode << " ";
        isVisited[curNode] = true;
        minPath.push_back(curNode);
        temp = findMin(matrix[curNode], isVisited);
        minWeight += temp.second;
        curNode = temp.first;
    }
    //std::cout << "\nMin Weight: " << minWeight - 999 << "\n";
    return std::make_pair(minPath, minWeight - 999);
}

void finMinPath(std::vector <std::vector <int>>& matrix) {
    std::vector <int> minPath;
    int minWeight = 999;
    std::pair<std::vector<int>, int> temp;
    for (int i = 0; i < matrix.size(); i++) {
        temp = findPath(matrix, i);
        if (temp.second < minWeight) {
            minWeight = temp.second;
            minPath = temp.first;
        }
    }

    std::cout << "Min Path: ";
    for (int i = 0; i < minPath.size(); i++) {
        std::cout << minPath[i] << " ";
    }
    std::cout << "\nMin Weight: " << minWeight << "\n";
}

int main()
{
    int size = 6;
    std::vector <std::vector <int>> matrix(size, std::vector<int>(size));
    makeMatrix("graph.txt", matrix);
    finMinPath(matrix);
}
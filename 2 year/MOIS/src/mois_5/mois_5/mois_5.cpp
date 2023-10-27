#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Graph {
private:
    string name;
    int numOfVertex, numOfEdge;
    int** matrix;
public:
    Graph(string name) {
        this->name = name;
        ifstream fin;
        fin.open(name);
        fin >> numOfVertex >> numOfEdge;

        matrix = new int* [numOfVertex];
        for (int i = 0; i < numOfVertex; i++) {
            matrix[i] = new int[numOfVertex];
        }

        for (int i = 0; i < numOfVertex; i++) {
            for (int j = 0; j < numOfVertex; j++) {
                matrix[i][j] = 0;
            }
        }

        for (int i = 0; i < numOfEdge; i++) {
            int from, to, weight;
            fin >> from >> to >> weight;
            matrix[from - 1][to - 1] = weight;
            matrix[to - 1][from - 1] = weight;
        }

        ofstream fout;
        fout.open("Adjacency.txt");
        fout << "\t";
        for (int i = 1; i <= numOfVertex; i++)
            fout << i << "\t";
        fout << endl;
        for (int i = 0; i < numOfVertex; i++) {
            fout << i + 1 << "\t";
            for (int j = 0; j < numOfVertex; j++) {
                fout << matrix[i][j] << "\t";
            }
            fout << endl;
        }
        fin.close();
        fout.close();
    }

    void makePrima(){
        vector <bool> isVisited(numOfVertex, false);
        isVisited[0] = true;
        int counter = 1;
        while (counter < numOfVertex) {
            int min = 999999;
            int from = -1;
            int to = -1;
            for (int i = 0; i < numOfVertex; i++) {
                if (isVisited[i]) {
                    for (int j = 0; j < numOfVertex; j++) {
                        if (isVisited[i] && matrix[i][j]) {
                            if (min > matrix[i][j]) {
                                min = matrix[i][j];
                                from = i;
                                to = j;
                            }
                        }
                    }
                }
            }
            cout << from << "\t" << to << "\t" << matrix[from][to] << endl;
            counter++;
            isVisited[to] = true;
        }
    }
};

int main() {
    string name = "input.txt";
    Graph graph(name);
    graph.makePrima();
	return 0;
}
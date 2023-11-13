#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

template<typename T>
void printVector(vector <T> vec) {
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
}

class Graph {
private:
    string name;
    int numOfVertex, numOfEdge;
    int** matrix;

    struct Edge {
        int from;
        int to;
        int weight;
    };

    Edge findMinEdge(int** ost, bool** isVisited) {
        Edge res;
        int start = 0;
        int min = 999999;
        for (int i = 0; i < numOfVertex; i++) {
            for (int j = start; j < numOfVertex; j++) {
                if (ost[i][j] && !isVisited[i][j]) {
                    if (min > ost[i][j]) {
                        min = ost[i][j];
                        res.from = i;
                        res.to = j;
                        res.weight = min;
                    }
                }
            }
            start++;
        }
        return res;
    }

    bool BFScycle(int** ost) {
        vector<bool> isVisited(numOfVertex, false);
        vector<bool> inQueue(numOfVertex, false);
        queue<int> queue;

        isVisited[0] = true;

        int start = 0;
        for (int i = 0; i < numOfVertex; i++) {
            if (ost[0][i] > 0) {
                queue.push(i);
                inQueue[i] = true;
            }
        }

        while (!queue.empty()) {
            start = queue.front();
            queue.pop();
            isVisited[start] = true;
            inQueue[start] = false;
            for (int i = 0; i < numOfVertex; i++) {
                if (!isVisited[i] && ost[start][i]) {
                    if (inQueue[i])
                        return true;
                    queue.push(i);
                    inQueue[i] = true;
                }
            }
        }
        return false;
    }
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
        ofstream fout("Prim.txt");
        vector <bool> isVisited(numOfVertex, false);
        isVisited[0] = true;
        int counter = 0;
        int sum = 0;
        fout << "From\tTo\tWeight" << endl;
        while (counter < numOfVertex - 1) {
            int min = 999999;
            int from = -1;
            int to = -1;
            for (int i = 0; i < numOfVertex; i++) {
                if (isVisited[i]) {
                    for (int j = 0; j < numOfVertex; j++) {
                        if (!isVisited[j] && matrix[i][j]) {
                            if (min > matrix[i][j]) {
                                min = matrix[i][j];
                                from = i;
                                to = j;
                            }
                        }
                    }
                }
            }
            fout << from + 1 << "\t" << to + 1 << "\t" << matrix[from][to] << endl;
            sum += matrix[from][to];
            counter++;
            isVisited[to] = true;
        }
        fout << "Weight of a tree: " << sum;
        fout.close();
    }

    void makeKruskal() {
        ofstream fout("Kruskal.txt");
        int** ost = new int* [numOfVertex];
        bool** isVisited = new bool* [numOfVertex];
        for (int i = 0; i < numOfVertex; i++) {
            ost[i] = new int[numOfVertex];
            isVisited[i] = new bool[numOfVertex];
        }
        for (int i = 0; i < numOfVertex; i++)
            for (int j = 0; j < numOfVertex; j++) {
                isVisited[i][j] = false;
                ost[i][j] = 0;
            }

        fout << "From\tTo\tWeight" << endl;
        int sum = 0;
        int counter = 0;

        while (counter < numOfVertex - 1) {
            Edge minEdge = findMinEdge(matrix, isVisited);
            ost[minEdge.from][minEdge.to] = minEdge.weight;
            ost[minEdge.to][minEdge.from] = minEdge.weight;
            isVisited[minEdge.from][minEdge.to] = true;
            if (BFScycle(ost)) {
                ost[minEdge.from][minEdge.to] = 0;
                ost[minEdge.to][minEdge.from] = 0;
            }
            else {
                sum += minEdge.weight;
                fout << minEdge.from + 1 << "\t" << minEdge.to + 1 << "\t" << minEdge.weight << endl;
                counter++;
            }
        }
        fout << "Weight of a tree: " << sum;
        fout.close();
    }
};

int main() {
    string name;
    cout << "Enter file name: ";
    cin >> name;
    Graph graph(name);
    graph.makePrima();
    graph.makeKruskal();
	return 0;

}
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Graph {
private:
public:
    string name;
    int** matrix;
    int numOfVertex, numOfEdge;

    Graph(string name) {
        this->name = name;
        ifstream fin;
        fin.open(name);
        fin >> numOfVertex >> numOfEdge;
    }

    void createAdjacencyMatrix() {
        ifstream fin;
        fin.open(name);

        matrix = new int* [numOfVertex];
        for (int i = 0; i < numOfVertex; i++)
            matrix[i] = new int[numOfVertex];

        for (int i = 0; i < numOfVertex; i++) {
            for (int j = 0; j < numOfVertex; j++) {
                matrix[i][j] = 999999;
            }
        }

        int trash;
        fin >> trash >> trash;
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
        fout.close();
        fin.close();
    }

    void Dejkstra() {
        ofstream fout("Dejkstra.txt");
        vector <int> distance(numOfVertex, 10000);
        vector <bool> isVisited(numOfVertex, false);
        vector <int> prev(numOfVertex, -1);

        distance[0] = 0;
        isVisited[0] = true;
        prev[0] = 0;

        for (int i = 0; i < numOfVertex; i++)
            if (matrix[0][i] <= distance[i]) {
                distance[i] = matrix[0][i];
                prev[i] = 0;
            }

        for (int i = 0; i < numOfVertex - 1; i++) {
            int minInd = findSmalest(distance, isVisited);
            int minDist = distance[minInd];
            isVisited[minInd] = true;

            for (int i = 0; i < numOfVertex; i++) {
                if (!isVisited[i] &&  distance[i] > matrix[minInd][i] + minDist) {
                    distance[i] = matrix[minInd][i] + minDist;
                    prev[i] = minInd;
                }
            }
        }

        fout << "Vertex\tDist\tPrev" << endl;
        for (int i = 0; i < numOfVertex; i++) {
            fout << i + 1 << "\t" << distance[i] << "\t" << prev[i] + 1 << endl;
        }
        fout.close();
    }

    void Floyd() {
        ofstream fout;
        fout.open("Floyd.txt");
        ofstream ffout;
        ffout.open("FloydPath.txt");
        int** temp = matrix;
        int** path = new int*[numOfVertex];
        for (int i = 0; i < numOfVertex; i++)
            path[i] = new int[numOfVertex];

        for (int i = 0; i < numOfVertex; i++) {
            temp[i][i] = 0;
            for (int j = 0; j < numOfVertex; j++) {
                if (matrix[i][j] < 999999)
                    path[i][j] = j;
                else path[i][j] = -1;
            }
        }

        for(int k = 0; k < numOfVertex; k++)
            for(int i = 0; i < numOfVertex; i++)
                for (int j = 0; j < numOfVertex; j++) 
                    if (temp[i][k] + temp[k][j] < temp[i][j]) {
                        temp[i][j] = temp[i][k] + temp[k][j];
                        path[i][j] = path[i][k];
                    }

        fout << "\t";
        ffout << "\t";
        for (int i = 1; i <= numOfVertex; i++) {
            fout << i << "\t";
            ffout << i << "\t";
        }
        fout << endl;
        ffout << endl;
        for (int i = 0; i < numOfVertex; i++) {
            fout << i + 1 << "\t";
            ffout << i + 1 << "\t";
            for (int j = 0; j < numOfVertex; j++) {
                fout << temp[i][j] << "\t";
                ffout << path[i][j] + 1 << "\t";
            }
            fout << endl;
            ffout << endl;
        }
        fout.close();
        ffout.close();
    }
private:
    int findSmalest(vector <int> dist, vector <bool> isVisited) {
        int min = 999999;
        int res = 0;
        for(int i = 0; i < dist.size();i++){
            if (dist[i] < min && !isVisited[i]) {
                min = dist[i];
                res = i;
            }
        }
        return res;
    }

};

int main()
{
    string name;
    cout << "Enter name of the file: " << endl;
    cin >> name;
    Graph graph(name);
    graph.createAdjacencyMatrix();
    graph.Dejkstra();
    graph.Floyd();
}
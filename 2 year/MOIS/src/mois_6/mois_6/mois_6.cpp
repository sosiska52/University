#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

class Graph {
private:
    string name;
    int numOfEdge;
    int numOfVertex;
    int** matrix;

    bool checkForPath(int start, vector <bool> inPath) {
        int check = 0;
        for (int j = 0; j < numOfVertex; j++) {
            if (matrix[start][j] && !inPath[j]) {
                check++;
            }
        }
        if (check == 0)
            return false;
        return true;
    }

    void fillStack(stack <int>& mainStack) {
        stack <int> tempStack;
        vector <bool> isVisited(numOfVertex, false);
        vector <int> path;
        vector <bool> inPath(numOfVertex, false);

        tempStack.push(0);

        while (!tempStack.empty()) {
            int top = tempStack.top();
            path.push_back(top);
            tempStack.pop();
            if (!isVisited[top]) {
                isVisited[top] = true;
                int check = 0;
                for (int i = 0; i < numOfVertex; i++) {
                    if (matrix[top][i] && !isVisited[i]) {
                        tempStack.push(i);
                        check++;
                    }
                }

                if (check == 0) {
                    check = 0;
                    mainStack.push(top);
                    inPath[top] = true;

                    for (int i = 2; i < path.size() + 1; i++) {
                        int start = path[path.size() - i];
                        if (!inPath[start] && !checkForPath(start, inPath)) {
                            mainStack.push(start);
                            inPath[start] = true;
                        }
                    }
                }
            }
        }
    }

    void printSSCs(stack <int>& mainStack) {
        ofstream fout("SSCs.txt");
        vector<bool> isVisited(numOfVertex, false);
        while (!mainStack.empty()) {
            int top = mainStack.top();
            mainStack.pop();

            if (!isVisited[top]) {
                isVisited[top] = true;
                bool check = false;
                stack <int> tempStack;
                tempStack.push(top);

                while (!check && !tempStack.empty()) {
                    int ttop = tempStack.top();
                    tempStack.pop();
                    fout << ttop + 1 << " ";
                    for (int i = 0; i < numOfVertex; i++) {
                        if (matrix[i][ttop] && !isVisited[i]) {
                            tempStack.push(i);
                            isVisited[i] = true;
                        }
                        else if (matrix[i][ttop] && !isVisited[i]) {
                            check = true;
                            break;
                        }
                    }
                }
                fout << endl;
            } 
        }
        fout.close();
    }
public:
    Graph(string name, bool isOriented) {
        this->name = name;
        ifstream fin;
        fin.open(name);
        fin >> numOfVertex >> numOfEdge;

        matrix = new int* [numOfVertex];
        for (int i = 0; i < numOfVertex; i++)
            matrix[i] = new int[numOfVertex];

        for (int i = 0; i < numOfVertex; i++) {
            for (int j = 0; j < numOfVertex; j++) {
                matrix[i][j] = 0;
            }
        }

        for (int i = 0; i < numOfEdge; i++) {
            int from, to;
            fin >> from >> to;
            matrix[from - 1][to - 1] = 1;
            if(!isOriented)
                matrix[to - 1][from - 1] = 1;
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

    void createSSC() {

        stack <int> mainStack;

        fillStack(mainStack);

        printSSCs(mainStack);
    }
};

int main()
{
    string name;
    cout << "Enter name of the input file: ";
    cin >> name;
    cout << "Is this graph orinted? (1 or 0): ";
    bool isOriented;
    cin >> isOriented;
    Graph graph(name, isOriented);
    graph.createSSC();
    return 0;
}
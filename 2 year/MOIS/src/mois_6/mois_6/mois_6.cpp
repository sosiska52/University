#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

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

    void printSCCs(stack <int>& mainStack) {
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

    void TarjanDFS(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& articulationPoint, vector <pair<int, int>>& bridge)
    {
        static int time = 0;
        disc[u] = low[u] = time;
        time++; 
        int children = 0;

        for (int v = 0; v < numOfVertex; v++)
        {
            if (disc[v] == -1 && matrix[u][v])
            {
                children++;
                parent[v] = u;
                TarjanDFS(v, disc, low, parent, articulationPoint, bridge);
                low[u] = min(low[u], low[v]);

                if (parent[u] == -1 and children > 1)
                    articulationPoint[u] = true;

                if (parent[u] != -1 and low[v] >= disc[u])
                    articulationPoint[u] = true;

                if (low[v] > disc[u])
                    bridge.push_back({u, v});
            }
            else if (v != parent[u] && matrix[u][v])
                low[u] = min(low[u], disc[v]);
        }
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

        for (int i = 0; i < numOfVertex; i++)
            for (int j = 0; j < numOfVertex; j++) 
                matrix[i][j] = 0;

        for (int i = 0; i < numOfEdge; i++) {
            int from, to;
            fin >> from >> to;
            matrix[from - 1][to - 1] = 1;
            if (!isOriented)
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
            for (int j = 0; j < numOfVertex; j++) 
                fout << matrix[i][j] << "\t";
            fout << endl;
        }
        fout.close();
        fin.close();
    }

    void findSCC() {
        //сорямба за код лооол
        stack <int> mainStack;

        fillStack(mainStack);

        printSCCs(mainStack);
    }

    void findArtPointsAndBridges() {
        vector<int> disc(numOfVertex, -1), low(numOfVertex, -1), parent(numOfVertex, -1);
        vector<bool> articulationPoint(numOfVertex, false);
        vector <pair<int, int>> bridge;

        for (int i = 0; i < numOfVertex; i++)
            if (disc[i] == -1)
                TarjanDFS(i, disc, low, parent, articulationPoint, bridge);

        ofstream fout("ArticulationPointsAndBridges.txt");
        fout << "Articulation Points are: ";
        for (int i = 0; i < numOfVertex; i++)
            if (articulationPoint[i] == true)
                fout << i + 1 << " ";
        fout << "\nBridges are: ";
        for (int i = 0; i < bridge.size(); i++)
            fout << "(" << bridge[i].first + 1 << " , " << bridge[i].second + 1 << ") ";
        fout.close();
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
    graph.findSCC();
    graph.findArtPointsAndBridges();
    return 0;
}
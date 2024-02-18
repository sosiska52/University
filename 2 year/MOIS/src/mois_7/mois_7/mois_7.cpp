#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <stack>
#include <string>

class Tree {
private:
    struct vertex {
        int num;
        vertex* right;
        vertex* left;
    };

    int numOfEdges;
    int numOfVertexes;

    vertex createVertex() {
        vertex newv;
        newv.num = NULL;
        newv.left = NULL;
        newv.right = NULL;
        return newv;
    }

    vertex createVertex(int n) {
        vertex newv;
        newv.num = n;
        newv.left = NULL;
        newv.right = NULL;
        return newv;
    }

    int heigh(vertex* root) {
            if (root == NULL) {
                return 0;
            }
            else if (root->left == NULL && root->right == NULL) {
                return 0;
            }
            else if (heigh(root->left) > heigh(root->right))
                return heigh(root->left) + 1;
            else
                return heigh(root->right) + 1;
    }

    std::string getSubtreeString(vertex* node, std::string prefix = "") {
        if (node == NULL) {
            return "";
        }

        std::string result = "";

        if (prefix.empty()) {
            result += std::to_string(node->num);
        }
        else {
            result += prefix + "+-" + std::to_string(node->num);
        }

        std::string childPrefix = prefix.empty() ? "   " : prefix + "|  ";

        std::string leftSubtree = getSubtreeString(node->left, childPrefix + "+-");
        std::string rightSubtree = getSubtreeString(node->right, childPrefix + "`-");

        if (!leftSubtree.empty()) {
            result += "\n" + leftSubtree;
        }

        if (!rightSubtree.empty()) {
            result += "\n" + rightSubtree;
        }

        return result;
    }

public:
    std::vector <vertex> tree;

    vertex* root;

    Tree(std::string name) {
        std::ifstream fin;
        int from, to;
        fin.open(name);

        fin >> numOfVertexes;
        fin >> numOfEdges;

        for (int i = 0; i < numOfVertexes; i++) {
            tree.push_back(createVertex());
            tree[i].num = i;
        }

        for (int i = 0; i < numOfEdges; i++) {
            fin >> from;
            fin >> to;

            if (tree[from].left == NULL) {
                tree[from].left = &tree[to];
            }
            else {
                tree[from].right = &tree[to];
            }
        }

        root = &tree[0];
        fin.close();
    }

    int height() {
        int res = 0;
        res = heigh(&tree[0]);
        return res;
    }

    void printBinaryTree() {
        std::string treeString = getSubtreeString(root);
        std::cout << treeString << "\n";
    }

    bool isIsomorphic(vertex* root1, vertex* root2) {
        if (root1 == NULL && root2 == NULL)
            return true;
        if (root1 == NULL || root2 == NULL)
            return false;

        return
            (isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right, root2->right));
    }

    void deleteVertex1(int x, vertex* cur) {
        if (cur == NULL)
            return;

        if (cur->left->num == x) {
            cur->left = NULL;
            return;
        }
        if (cur->right->num == x) {
            cur->right = NULL;
            return;
        } 

        if (cur->right != NULL) {
            std::cout << "check1\n";
            deleteVertex1(x, cur->right);
        }
        if (cur->left != NULL) {
            std::cout << "check2\n";
            deleteVertex1(x, cur->left);
        }
    }

    void deleteVertex(int x) {
        std::stack <vertex*> st;
        st.push(root);

        while (!st.empty()) {
            std::cout << st.size() << "\n";
            if (st.top()->left->num == x) {
                st.top()->left = NULL;
                break;
            }
            if (st.top()->right->num == x) {
                st.top()->right = NULL;
                break;
            }

            if (st.top()->left != NULL) {
                st.push(st.top()->left);
                std::cout << "check1\n";
            }
            if (st.top()->right != NULL) {
                st.push(st.top()->right);
                std::cout << "check2\n";
            }

            st.pop();
        }
        std::cout << "done\n";
    }

    void addVertex(int target) {
        vertex* temp = new vertex;
        temp->num = numOfVertexes;
        //tree.push_back(createVertex(numOfVertexes));

        std::stack <vertex*> st;
        st.push(root);

        while (!st.empty()) {
            if (st.top() == NULL)
                st.pop();
            if (st.top() == NULL)
                st.pop();

            if (st.top()->num == target) {
                std::cout << "FOUND\n";
                if (st.top()->left != NULL)
                    st.top()->left = temp;
                else if (st.top()->right != NULL)
                    st.top()->right = temp;
                break;
            }
            st.push(st.top()->left);
            st.push(st.top()->right);
            st.pop();
        }
        
        numOfEdges++;
        numOfVertexes++;
    }
};

void menu() {
    std::string name;
    std::cout << "Enter name of the file1: ";
    //std::cin >> name;
    //Tree tree1(name);
    Tree tree1("input1.txt");
    std::cout << "\nEnter name of the file2: ";
    //std::cin >> name;
    //Tree tree2(name);
    Tree tree2("input2.txt");

    int choise;
    while (true) {
        std::cout << "\n\nMenu\n";
        std::cout << "1)Show tree\n";
        std::cout << "2)Check for isomorphism\n";
        std::cout << "3)Delete vertex from first tree\n";
        std::cout << "4)Add vertex to first tree\n";
        std::cout << "5)Exit\n";

        std::cin >> choise;
        switch (choise)
        {
        case 1:
            system("cls");
            int choise1;
            std::cout << "Which tree: ";
            std::cin >> choise1;
            if (choise1 == 1) {
                tree1.printBinaryTree();
            }
            else if (choise1 == 2) {
                tree2.printBinaryTree();
            }
            else {
                system("cls");
                std::cout << "Wrong option1\n";
            }
            break;
        case 2:
            system("cls");
            bool res;
            res = tree1.isIsomorphic(tree1.root, tree2.root);
            if (res)
                std::cout << "Yes";
            else
                std::cout << "No";
            break;
        case 3:
            system("cls");
            std::cout << "Choose leaf to delete in first tree:";
            int choise2;
            std::cin >> choise2;
            if (tree1.tree[choise2].left == NULL && tree1.tree[choise2].right == NULL) {
                tree1.deleteVertex(choise2);
                system("cls");
            }
            else std::cout << "This is not a leaf\n";
            break;
        case 4:
            system("cls");
            std::cout << "Choose vertex with free space: ";
            int choise3;
            std::cin >> choise3;
            if (tree1.tree[choise3].left == NULL) {
                tree1.addVertex(choise3);
                //system("cls");
            }
            else std::cout << "This vertex don't have free space\n";
            break;
        case 5:
            return;
        case 6:
            for (int i = 0; i < tree1.tree.size(); i++) {
                std::cout << tree1.tree[i].num << ": ";

                if (tree1.tree[i].left != NULL)
                    std::cout << tree1.tree[i].left->num << ", ";
                else std::cout << "n, ";

                if (tree1.tree[i].right != NULL)
                    std::cout << tree1.tree[i].right->num << "\n";
                else std::cout << "n\n";
                // << tree1.tree[i].left->num << ", " << tree1.tree[i].right->num << "\n";
            }
            break;
        default:
            system("cls");
            std::cout << "Wrong option2\n";
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}
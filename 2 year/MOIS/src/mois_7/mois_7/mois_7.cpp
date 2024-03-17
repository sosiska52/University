#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <stack>
#include <string>
#include <sstream>
#include <queue>

class Tree {
private:
    struct vertex {
        int num;
        vertex* right;
        vertex* left;
        vertex(int x) {
            this->num = x;
            this->left = NULL;
            this->right = NULL;
        }
    };

    int heigh(vertex* cur) {
            if (cur == NULL) {
                return 0;
            }
            else if (cur->left == NULL && cur->right == NULL) {
                return 0;
            }
            else if (heigh(cur->left) > heigh(cur->right))
                return heigh(cur->left) + 1;
            else
                return heigh(cur->right) + 1;
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
    vertex* root;

    int size;

    Tree() {
        root = NULL;
        size = 0;
    }

    void addVertex(vertex* root, int from, int to) {
        if (root == NULL)
            return;

        if (root->num == from) {
            if (root->left == NULL) {
                root->left = new vertex(to);
                size++;
                return;
            }

            if (root->right == NULL) {
                root->right = new vertex(to);
                size++;
                return;
            }
        }

        addVertex(root->left, from, to);
        addVertex(root->right, from, to);
    }

    void createBinaryTreeFromFile(const std::string& filename) {
        std::ifstream fin;
        fin.open(filename);
        std::string line;
        while (std::getline(fin, line)) {
            std::istringstream iss(line);
            int from, to;
            iss >> from >> to;

            if (root == NULL) {
                root = new vertex(from);
                size++;
            }

            addVertex(root, from, to);
        }
        fin.close();
    }

    int height() {
        int res = 0;
        res = heigh(root);
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

        bool isFlipped = (isIsomorphic(root1->left, root2->right) && isIsomorphic(root1->right, root2->left));
        bool isSymetric = (isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right, root2->right));
        return isSymetric || isFlipped;
    }

    void deleteVertex(int x) {
        if (root == NULL) {
            return;
        }

        std::stack <vertex*> st;
        st.push(root);

        while (!st.empty()) {
            vertex* currNode = st.top();
            st.pop();

            if (currNode->left != NULL) {
                if (currNode->left->num == x) {
                    delete currNode->left;
                    currNode->left = NULL;
                    return;
                } else
                st.push(currNode->left);
            }

            if (currNode->right != NULL) {
                if (currNode->right->num == x) {
                    delete currNode->right;
                    currNode->right = NULL;
                    return;
                } else
                st.push(currNode->right);
            }
        }

    }

    bool isBalanced(vertex* cur) {
        if (root == NULL)
            return true;

        int leftHeight = heigh(cur->left);
        int rightHeight = heigh(cur->right);

        if (abs(leftHeight - rightHeight) <= 1)
            return true;

        return false;
    }
};

void menu() {
    std::string name;
    std::cout << "Enter name of the file1: ";
    std::cin >> name;
    Tree tree1;
    tree1.createBinaryTreeFromFile(name);
    std::cout << "\nEnter name of the file2: ";
    std::cin >> name;
    Tree tree2;
    tree2.createBinaryTreeFromFile(name);

    int choise;
    while (true) {
        std::cout << "\n\nMenu\n";
        std::cout << "1)Show tree\n";
        std::cout << "2)Check for isomorphism\n";
        std::cout << "3)Delete vertex\n";
        std::cout << "4)Add vertex\n";
        std::cout << "5)Show height and check if balansed\n";
        std::cout << "6)Exit\n";

        std::cin >> choise;
        switch (choise)
        {
        case 1:
            system("cls");
            std::cout << "First tree:\n";
            tree1.printBinaryTree();
            std::cout << "Second tree:\n";
            tree2.printBinaryTree();
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
            std::cout << "Chose tree: ";
            int choise4;
            std::cin >> choise4;
            std::cout << "Choose leaf to delete in first tree:";
            int choise2;
            std::cin >> choise2;

            if (choise4 == 1) {
                tree1.deleteVertex(choise2);
                system("cls");
            }
            else if (choise4 == 2) {
                tree2.deleteVertex(choise2);
                system("cls");
            }

            break;
        case 4:
            system("cls");
            std::cout << "Chose tree: ";
            int choise5;
            std::cin >> choise5;
            std::cout << "Choose vertex with free space: ";
            int choise3;
            std::cin >> choise3;

            if (choise4 == 1) {
                tree1.addVertex(tree1.root, choise3, tree1.size);
                system("cls");
            }
            else if (choise4 == 2) {
                tree2.addVertex(tree2.root, choise3, tree2.size);
                system("cls");
            }

            break;
        case 5:
            system("cls");

            /*
            std::cout << tree1.height(tree1.root) << "\n";
            std::cout << tree1.height(tree1.root->left) << "\n";
            std::cout << tree1.height(tree1.root->right) << "\n";
            */

            std::cout << "Chose tree: ";
            int choise6;
            std::cin >> choise6;

            if (choise6 == 1) {
                system("cls");
                std::cout << "Height: " << tree1.height() << "\n";
                if (tree1.isBalanced(tree1.root))
                    std::cout << "The tree is balansed\n";
                else
                    std::cout << "The tree is not balansed\n";
            }
            else if (choise6 == 2) {
                system("cls");
                std::cout << "Height: " << tree2.height() << "\n";
                if (tree2.isBalanced(tree2.root))
                    std::cout << "The tree is balansed\n";
                else
                    std::cout << "The tree is not balansed\n";
            }
            break;
        case 6:
            return;
        default:
            system("cls");
            std::cout << "Wrong option\n";
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}
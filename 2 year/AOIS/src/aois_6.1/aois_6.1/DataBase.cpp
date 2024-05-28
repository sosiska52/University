#include "DataBase.h"

void DataBase::readDataBase(const std::string path) {
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "\nCant't open file\n";
        return;
    }

    int size;
    int maxLength;
    std::string temp;
    fin >> size >> maxLength;
    dataBase = std::vector<std::string>(size);
    mask = std::vector<bool>(maxLength, true);

    for (int i = 0; i < size; i++) {
        fin >> temp;
        if (temp.size() < maxLength)
            temp.append(maxLength - temp.size(), '.');
        dataBase[i] = temp;
        //std::cout << temp << "\n";
    }
    fin.close();
}

void DataBase::editMask() {
    std::cout << "Enter ind to consider(example: 1 0 1 1 0 0 0 0 0 0):";
    int i = 0;
    int n;
    while (i < 10) {
        std::cin >> n;
        if (n == 1 || n == 0) {
            mask[i] = n;
            i++;
        }
    }
}

void DataBase::show() {
    for (int i = 0; i < dataBase.size(); i++)
        std::cout << i << ". " << dataBase[i] << "\n";
}

std::vector<int> DataBase::findInd(std::string word, int op) {
    if (word.size() < dataBase[0].size())
        word.append(dataBase[0].size() - word.size(), '.');

    std::vector<bool> fits(dataBase.size(), true);

    for (int i = 0; i < word.size(); i++)
        if (mask[i] && word[i] != '.')
            for (int j = 0; j < dataBase.size(); j++) {
                switch (op)
                {
                case 0:
                    if (dataBase[j][i] != word[i])
                        fits[j] = false;
                    break;
                case 1:
                    if (dataBase[j][i] <= word[i])
                        fits[j] = false;
                    break;
                case 2:
                    if (dataBase[j][i] < word[i])
                        fits[j] = false;
                    break;
                case 3:
                    if (dataBase[j][i] >= word[i])
                        fits[j] = false;
                    break;
                case 4:
                    if (dataBase[j][i] > word[i])
                        fits[j] = false;
                    break;
                default:
                    break;
                }
            }

    std::vector<int> result;
    for (int i = 0; i < fits.size(); i++)
        if (fits[i])
            result.push_back(i);

    return result;
}

void DataBase::find(std::string word) {
    std::string op;
    for (int i = 0; i < 5; i++) {
        std::vector<int> result = findInd(word, i);
        
        switch (i)
        {
        case 0:
            op = "=";
            break;
        case 1:
            op = ">";
            break;
        case 2:
            op = ">=";
            break;
        case 3:
            op = "<";
            break;
        case 4:
            op = "<=";
            break;
        default:
            break;
        }
        if (result.empty()) {
            std::cout << op << " : NULL\n";
        }
        else {
            std::cout << op << ": \n";
            for (int i = 0; i < result.size(); i++)
                std::cout << result[i] << ". " << dataBase[result[i]] << "\n";
        }
        
    }
}

void DataBase::remove(std::string word) {
    std::vector<int> result = findInd(word, 0);
    if (result.empty()) {
        std::cout << "NULL\n";
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        dataBase[result[i]] = "";
        dataBase[result[i]].append(dataBase[0].size(), '.');
    }
}

void DataBase::add(std::string word) {
    bool isPlaced = false;
    for (int i = 0; i < dataBase.size(); i++) {
        if (dataBase[i][0] == '.') {
            word.append(dataBase[0].size() - word.size(), '.');
            dataBase[i] = word;
            isPlaced = true;
        }
    }
    if (!isPlaced)
        std::cout << "Not enough room\n";
}
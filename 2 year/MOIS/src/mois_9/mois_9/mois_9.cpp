#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <string>
#include <ctime>
#include <cmath>
#include <stack>

void removeElement(std::vector<int>& vec, int index) {
    if (index >= 0 && index < vec.size()) {
        if (index == 0) {
            vec.erase(vec.begin());
        }
        else if (index == vec.size() - 1) {
            vec.erase(vec.end() - 1);
        }
        else {
            vec.erase(vec.begin() + index);
        }
    }
}

unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}

std::vector <int> makePermutation(unsigned long long num, std::vector<int> radixes) {
    std::vector <int> permutation;
    for (int i = radixes.size() - 1; i >= 0; i--) {
        permutation.insert(permutation.begin(), num % radixes[i]);
        num = std::floor(num / radixes[i]);
    }
    return permutation;
}

std::vector <int> convert(std::vector <int> choises, std::vector <int> nums) {
    std::vector <int> res;
    for (int i = 0; i < choises.size(); i++) {
        int index = choises[i];
        res.push_back(nums[index]);
        removeElement(nums, index);
    }
    return res;
}

bool task2check(std::vector<int> permutation, int n) {
    int number = 0;
    for (int i = 0; i < permutation.size(); i++) {
        if (permutation[i] == 5)
            return false;
        else
            number = number * 10 + permutation[i];
    }
    if (number < n)
        return true;
    return false;
}

void task1and2(int N, int n) {
    std::string path = "E:\\otisGIT\\University\\2 year\\MOIS\\src\\mois_9\\mois_9\\Permutations";
    std::ofstream fout;
    fout.open(path + "\\Permutation_" + std::to_string(N) + ".txt");

    std::vector <int> radixes(N);
    std::vector <int> nums(N);
    for (int i = 0; i < N; i++) {
        radixes[i] = N - i;
        nums[i] = 1 + i;
    }


    unsigned long long numOfPermutations = factorial(N);
    std::vector <int> temp;
    std::vector <int> permutation;
    int counter = 0;
    for (unsigned long long i = 0; i < numOfPermutations; i++) {
        temp = makePermutation(i, radixes);
        permutation = convert(temp, nums);

        for (int j = 0; j < permutation.size(); j++) {
            fout << permutation[j] << " ";
        }
        fout << "\n";

        if (task2check(permutation, n))
            counter++;
    }
    fout.close();
    std::cout << "There are " << counter << " numbers less than " << n << "\n";
}

std::vector<int> inversion(std::vector <int>& cur) {
    std::vector <int> res(9);
    for (int i = 0; i < 9; i++) {
        int counter = 0;
        for (int j = 0; j < 9; j++) {
            if (cur[j] > i + 1) {
                counter++;
            }
            if (cur[j] == i + 1) {
                break;
            }
        }

        res[i] = counter;
    }
    return res;
}

void makeInversionFile() {
    std::ifstream fin;
    std::ofstream fout;
    fout.open("task3.txt");
    fin.open("task3test.txt");
    std::vector <int> cur(9);
    std::vector <int> res(9);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            fin >> cur[j];
        }
        res = inversion(cur);
        for (int k = 0; k < 9; k++) {
            fout << res[k] << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
}

std::vector <int> inversionToPermutation(std::vector <int>& inversion) {
    std::vector <int> res;
    res.push_back(inversion.size());
    for (int i = inversion.size() - 2; i >= 0; i--) {
        if (inversion[i] == 0)
            res.insert(res.begin(), i+1);
        else {
            res.insert(res.begin() + inversion[i], i+1);
        }
        for (int j = 0; j < res.size(); j++) {
            std::cout << res[j] << " ";
        }
        std::cout << "\n";
    }
    return res;
}

void transformInversion(std::vector <int>& inversion) {
    int size = inversion.size();
    for (int i = 0; i < size; i++) {
        inversion[i] = (size - i - 1) - inversion[i];
    }
}

void task3(int quantity, int size) {
    std::ofstream fout;
    std::ifstream fin;
    fout.open("New permutations.txt");
    fin.open("task3.txt");

    std::vector <int> cur(size);
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < size; j++) {
            fin >> cur[j];
        }

        transformInversion(cur);
        cur = inversionToPermutation(cur);
        for (int k = 0; k < 9; k++) {
            fout << cur[k] << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
}

int main()
{
    int N, n;
    std::cout << "Enter quantity of numbers: ";
    std::cin >> N;
    std::cout << "Enter number for 2 task: ";
    std::cin >> n;
    task1and2(N, n);
    task3(8,9);
 }
#include <iostream>
#include <vector>

using namespace std;

class Arif {
private:
    int a;
    int b;
    int c;
public:
    Arif() {
        a = NULL;
        b = NULL;
        c = NULL;
    }

    Arif (const Arif& temp) {
        a = temp.a;
        b = temp.b;
        c = temp.c;
    }

    Arif(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    int getA() {
        return a;
    }

    int getB() {
        return b;
    }

    int getC() {
        return c;
    }

    void setA(int x){
        a = x;
    }

    void setB(int x) {
        b = x;
    }

    void setC(int x) {
        c = x;
    }

    void printAll() {
        cout << a << " " << b << " " << c << endl;
    }

    Arif operator + (const Arif& temp) {
        return Arif{
            a + temp.a,
            b + temp.b,
            c + temp.c
        };
    }

    Arif operator = (const Arif& temp) {
        a = temp.a;
        b = temp.b;
        c = temp.c;
        return *this;
    }

    Arif operator ++ () {
        ++a;
        ++b;
        ++c;
        return *this;
    }
};

class Film {
private:
    string name;
    vector <string> actors;
    double length;
public:
    Film() { }

    Film(string name, vector <string> actors, int length) {
        this->name = name;
        this->length = length;
        this->actors = actors;
    }

    Film(const Film& temp) {
        this->name = temp.name;
        this->length = temp.length;
        this->actors = temp.actors;
    }

    void setLength(double temp) {
        length = temp;
    }

    void setName(string temp){
        name = temp;
    }

    void setActors(vector <string> temp) {
        actors = temp;
    }

    double getLength() {
        return length;
    }

    string getName() {
        return name;
    }

    void showAll() {
        cout << name << " " << length << endl;
        for (int i = 0; i < actors.size(); i++)
            cout << actors[i] << " ";
        cout << endl;
    }

    vector <string> getActors() {
        return actors;
    }

    Film operator = (const Film& temp) {
        name = temp.name;
        length = temp.length;
        actors = temp.actors;
        return *this;
    }

    Film operator + (const Film& temp) {
        length += temp.length;
        return *this;
    }

    Film operator --() {
        --length;
        return *this;
    }
};

int main()
{
    Arif A(1,2,3);
    Arif B(A);
    B.setA(10);
    Arif C = A + B;
    ++A;
    B = A;
    A.printAll();
    B.printAll();
    C.printAll();
    ////////////////////////
    vector <string> actors = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    Film sec("GodFather", actors, 1.35);
    Film third(sec);
    third.setName("Inception");
    Film fir = third;
    fir.setLength(0.35);
    fir = fir + sec;
    --fir;
    fir.showAll();
    sec.showAll();
    third.showAll();
    return 0;
}
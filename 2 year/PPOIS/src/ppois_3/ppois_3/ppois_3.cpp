#include <iostream>
#include <vector>

using namespace std;

class Arif {
private:
    int a;
    int b;
    int c;
public:
    Arif() { }

    Arif(const Arif& temp) {
        a = temp.a;
        b = temp.b;
        c = temp.c;
    }

    Arif(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    ~Arif() {
        cout << "Deleting Arif obj" << endl;
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

    void setA(int x) {
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

    void AddUp(int i) {
        a += i;
    }

    void AddUp(int i, int j) {
        a += i;
        b += j;
    }

    void AddUp(int i, int j, int k) {
        a += i;
        b += j;
        c += k;
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

    ~Film() {
        cout << "Deleting " << name << " Film" << endl;
    }

    void setLength(double temp) {
        length = temp;
    }

    void setName(string temp) {
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

    void AddActors(vector <string> newActors) {
        for (int i = 0; i < newActors.size(); i++) {
            actors.push_back(newActors[i]);
        }
    }

    void AddActors(string* newActors, int size) {
        for (int i = 0; i < size; i++) {
            actors.push_back(newActors[i]);
        }
    }

    void AddActors(string actor) {
        actors.push_back(actor);
    }
};

class Season {
private:
    Film* series;
    string name;
    int size;
    string& nameLink = name;

    void seriesInitialization(Film* tempSeries) {
        if (size > 0) {
            series = new Film[size];
            for (int i = 0; i < size; i++)
                series[i] = tempSeries[i];
        }
        else cout << "ERROR: size is unknown" << endl;
    }
public:
    Season() {
        name = "UNNAMED";
        size = 0;
    }

    Season(string tempName, int tempSize, Film* tempSeries) {
        name = tempName;
        size = tempSize;
        seriesInitialization(tempSeries);
    }

    Season(Season& temp) {
        name = temp.name;
        size = temp.size;
        seriesInitialization(temp.series);
    }

    ~Season() {
        cout << "Deleting " << name << " Season with " << size << " epizodes" << endl;
    }

    Film getEpizode(int num) { return series[num]; }

    void copySeries(Film*& temp, int& tempSize) {
        for (int i = 0; i < size; i++) {
            temp[i] = series[i];
        }
        if (tempSize > size)
            tempSize = size;
    }

    void addEpizode(Film newEp) {
        Film* temp = new Film[size];
        copySeries(temp, size);
        size++;
        series = new Film[size];
        for (int i = 0; i < size - 1; i++)
            series[i] = temp[i];
        series[size - 1] = newEp;
    }
};

int main()
{
    Arif* nums = new Arif(1, 1, 1);
    nums->printAll();
    delete nums;
    cout << endl;
    vector <string> temp1 = { "1", "2" };
    Film newSeason[2];
    newSeason[0] = Film("Batman", temp1, 1.23);
    newSeason[1] = Film("Spider Man", temp1, 2.03);
    Season* season1 = new Season("Introduction", 2, newSeason);
    Film epizode3 = newSeason[0];
    epizode3.AddActors("3");
    epizode3.setName("Hulk");
    season1->addEpizode(epizode3);
    cout << endl;
    delete season1;
    return 0;
}
#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    int size;
    int top;
    T* array;

    void arrayInitialization(int newSize) {
        T* temp = new T[newSize];
        for (int i = 0; i < size; i++)
            temp[i] = array[i];
        delete[] array;
        array = temp;
        size = newSize;
    }
public:
    Stack() {
        size = 8;
        top = 0;
        array = new T[size];
        array[0] = 0;
    }

    ~Stack() { delete[] array; }

    bool isEmpty() {
        if (size <= 0)
            return true;
        return false;
    }

    void push(T data) {
        if (top == size - 1) {
            arrayInitialization(size * 2);
        }
        top++;
        array[top] = data;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Empty" << endl;
        } else top--;
    }

    T get() {
        return array[top];
    }
};

template<typename T>
T summ(T a, T b, T c) {
    return a + b + c;
}

int main()
{
    Stack<int> temp;
    temp.push(1);
    cout << temp.get() << endl;
    for (int i = 0; i < 10; i++)
        temp.push(i);
    cout << temp.get() << endl;
    cout << summ(1, 2, 3) << " " << summ<double>(1, 2.3, 3.1) << endl;
    return 0;
}
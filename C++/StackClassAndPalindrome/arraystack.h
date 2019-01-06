#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

enum STACK_ERROR { FULL, EMPTY, BAD_SIZE };

template <typename T>
class ArrayStack {
    T* arr;
    size_t curPosition, startPosition, capacity;
    void eraseAll();
    void copy(const ArrayStack<T> &other);
public:
    ArrayStack(size_t size=10);
    ArrayStack(const ArrayStack<T> &rhs);
    ~ArrayStack();
    ArrayStack<T>& operator=(const ArrayStack<T> &rhs);

    void push(const T &data);
    T pop();
    T peek() const;
    bool full() const;
    bool empty() const;
    size_t size() const;
    size_t roomLeft();
    void resize(size_t size);
    void clear();

    ArrayStack<T>& operator<<(const T &data);
    ArrayStack<T>& operator>>(T &data);

    template <typename U>
    friend istream& operator>>(istream& in, ArrayStack<U> &stck);
    template <typename U>
    friend ostream& operator<<(ostream& out, const ArrayStack<U> &stck);
};

// Private
template <typename T>
void ArrayStack<T>::eraseAll() {
    startPosition = curPosition = capacity = 0;
    if(arr)
        delete[] arr;
}

template <typename T>
void ArrayStack<T>::copy(const ArrayStack<T> &other) {
    startPosition = other.startPosition;
    curPosition = other.curPosition;
    arr = new T[capacity = other.capacity];
    for(size_t i=startPosition; i<curPosition; ++i)
        arr[i] = other.arr[i];
}

// Public
template <typename T>
ArrayStack<T>::ArrayStack(size_t size) {
    if(size < 2)
        throw BAD_SIZE;
    arr = new T[capacity=size];
    for(size_t i=0; i<capacity; ++i)
        arr[i] = T();
    startPosition = curPosition = 0;
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &rhs) {
    eraseAll();
    copy(rhs);
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
    eraseAll();
}

template <>
ArrayStack<char*>::~ArrayStack() {
    for(size_t i=0; i<capacity; ++i)
        if(arr[i] || arr[i]=="\n")
            delete arr[i];
    eraseAll();
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T> &rhs) {
    if(this!=&rhs) {
        eraseAll();
        copy(rhs);
    }
    return *this;
}

template <typename T>
void ArrayStack<T>::push(const T &data) {
    if(full())
        throw FULL;
    arr[curPosition++] = data;
}

template <typename T>
T ArrayStack<T>::pop() {
    if(empty())
        throw EMPTY;
    return arr[--curPosition];
}

template <typename T>
T ArrayStack<T>::peek() const {
    if(empty())
        throw EMPTY;
    return arr[curPosition-1];
}

template <typename T>
bool ArrayStack<T>::full() const {
    return curPosition >= capacity;
}

template <typename T>
bool ArrayStack<T>::empty() const {
    return curPosition == startPosition;
}

template <typename T>
size_t ArrayStack<T>::size() const {
    return curPosition - startPosition;
}

template <typename T>
size_t ArrayStack<T>::roomLeft() {
    return capacity - curPosition;
}

template <typename T>
void ArrayStack<T>::resize(size_t size) { // reversed..?
    if(size < 2)
        throw BAD_SIZE;
    T* temp = new T[size];

    size_t newStartPos = size > curPosition-startPosition ? 0 : curPosition-size,
           index = 0;
    for(size_t i=newStartPos; i<curPosition; ++i)
        temp[index++] = arr[i];
    eraseAll();
    arr = temp;
    capacity = size;
    curPosition = index;
}

template <typename T>
void ArrayStack<T>::clear() {
    startPosition = curPosition = 0;
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator<<(const T &data) {
    push(data);
    return *this;
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator>>(T &data) {
    data = pop();
    return *this;
}

template <typename U>
istream& operator>>(istream& in, ArrayStack<U> &stck) {
    U data;
    string line;
    stck.eraseAll();
    if(&in==&cin) {
        cout << "Enter size: ";
        in >> stck.capacity;
        stck.arr = new U[stck.capacity];
        cout << "Enter data:" << endl;
        do {
            in >> data;
            stck << data;
        } while(!stck.full());
    } else {
        getline(in, line, ':');
        in >> stck.capacity;
        getline(in, line, ':');
        in >> stck.startPosition;
        getline(in, line, ':');
        in >> stck.curPosition;
        for(size_t i=0; i<stck.size(); ++i) {
            in >> data;
            stck << data;
        }
    }
    return in;
}

template <>
istream& operator>>(istream& in, ArrayStack<string> &stck) {
    string data, line;
    stck.eraseAll();
    if(&in==&cin) {
        cout << "Enter size: ";
        in >> stck.capacity;
        stck.arr = new string[stck.capacity];
        cout << "Enter data:" << endl;
        in.ignore(32767, '\n');
        do {
            getline(in, data);
            if(data.empty())
                break;
            stck << data;
        } while(!stck.full());
    } else {
        getline(in, line, ':');
        in >> stck.capacity;
        getline(in, line, ':');
        in >> stck.startPosition;
        getline(in, line, ':');
        in >> stck.curPosition;
        in.ignore(32767, '\n');
        for(size_t i=0; i<stck.size(); ++i) {
            getline(in, data);
            stck << data;
        }
    }
    return in;
}

template <>
istream& operator>>(istream& in, ArrayStack<char*> &stck) {
    string line;
    stck.eraseAll();
    if(&in==&cin) {
        cout << "Enter size: ";
        in >> stck.capacity;
        stck.arr = new char*[stck.capacity];
        cout << "Enter data:" << endl;
        in.ignore(32767, '\n');
        while(!stck.full()) {
            getline(in, line);
            if(line.empty())
                break;
            char* data = new char[line.length()];
            strcpy(data, line.c_str());
            stck<<data;
        }
    } else {
        getline(in, line, ':');
        in >> stck.capacity;
        getline(in, line, ':');
        in >> stck.startPosition;
        getline(in, line, ':');
        in >> stck.curPosition;
        in.ignore(32767, '\n');
        for(size_t i=0; i<stck.size(); ++i) {
            getline(in, line);
            char* data = new char[line.length()];
            strcpy(data, line.c_str());
            stck << data;
        }
    }
    return in;
}

template <typename U>
ostream& operator<<(ostream& out, const ArrayStack<U> &stck) {
    if(&out!=&cout) {
        out << "Stack capacity: " << stck.capacity << endl
            << "Stack startPosition: " << 0 << endl
            << "Stack currentPosition: " << stck.curPosition - stck.startPosition << endl;
    }
    int index = stck.curPosition;
    while(index > stck.startPosition)
        out << stck.arr[--index] << endl;
    return out;
}


#endif // ARRAYSTACK_H

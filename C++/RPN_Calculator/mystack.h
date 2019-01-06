#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "mynewtypes.h"

using namespace std;

template <typename T>
class myStack {

    T* arr;
    size_t curPosition, startPosition, capacity;
    void eraseAll();
    void copy(const myStack<T> &other);

public:
    myStack(size_t size=10);
    myStack(const myStack<T> &rhs);
    ~myStack();
    myStack<T>& operator=(const myStack<T> &rhs);

    void push(const T &data);
    void push(const char* &data);
    T pop();
    T peek() const;
    bool full() const;
    bool empty() const;
    size_t size() const;
    size_t roomLeft() const;
    void resize(size_t size);
    void clear();

    myStack<T>& operator<<(const T &data);
    myStack<T>& operator>>(T &data);

    template <typename U>
    friend istream& operator>>(istream& in, myStack<U> &stck);
    template <typename U>
    friend ostream& operator<<(ostream& out, const myStack<U> &stck);
};

#endif // MYSTACK_H

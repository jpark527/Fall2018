#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>
#include "mynewtypes.h"

using namespace std;

template<typename T>
class myQueue {
    T *que;
    size_t head, tail, mySize, capacity;

    void nukem();
    void copy(const myQueue<T> &other);

public:
    myQueue(size_t s = 10);
    ~myQueue();
    myQueue(const myQueue<T> &other);
    myQueue<T>& operator=(const myQueue<T> &other);

    bool full() const;
    bool empty() const;
    void clear();
    size_t size() const;
    size_t getCapacity() const;
    T peek() const;
    void resize(size_t s = 10);
    void enqueue(const T &d);
    void dequeue(T &d);
    myQueue<T>& operator<<(const T &d);
    myQueue<T>& operator>>(T &d);

    template<typename U>
    friend
    ostream& operator<<(ostream &out, const myQueue<U> &q);

    template<typename U>
    friend
    istream& operator>>(istream &in, myQueue<U> &q);
};

#endif // MYQUEUE_H

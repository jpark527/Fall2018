#ifndef MYHEAP_H
#define MYHEAP_H
#include <vector>
#include <cmath>
#include <bitset>
#include <iostream>

using namespace std;

enum HEAP_ERROR {EMPTY, FULL, BAD_SIZE};

template <typename T>
class myHeap {
    size_t mySize, myCapacity;
    vector<T> v;
    void copy(const myHeap<T> &other);
    bool autoResize(size_t s);
    void reheapifyUp(size_t ind);
    void reheapifyDown(size_t ind);
public:
    myHeap(size_t s=3);
    ~myHeap();
    myHeap(const myHeap<T> &other);
    myHeap<T>& operator=(const myHeap<T> &other);

    bool empty() const;
    bool full() const;
    size_t size() const;
    size_t capacity() const;

    void pop(T &data);
    void push(const T &data);

    myHeap<T>& operator>>(T &data);
    myHeap<T>& operator<<(const T &data);
};

// Private
template <typename T>
void myHeap<T>::copy(const myHeap<T> &other) {
    mySize = other.mySize;
    myCapacity = other.myCapacity;
    for(size_t i=0; i<mySize; ++i)
        v.push_back(other.v[i]);
}

template <typename T>
bool myHeap<T>::autoResize(size_t s) {
    myCapacity = (size_t) pow(2.,static_cast<int>(log2(s+1)+1))-1;
    v.resize(myCapacity);
    return true;
}

template <typename T>
void myHeap<T>::reheapifyUp(size_t ind) {
    if(ind < 1)
        return ;
    int child = static_cast<int>(ind), parent = (child-1) / 2;
    if(v[child] > v[parent]) {
        T temp;
        temp = v[child];
        v[child] = v[parent];
        v[parent] = temp;
        reheapifyUp(parent);
    } else
        return ;
}

template <typename T>
void myHeap<T>::reheapifyDown(size_t ind) {
    size_t lChild = ind * 2 + 1, rChild = lChild+1, bigger;
    if(rChild > mySize || !v[lChild])
        return ;
    bigger = v[rChild] && (v[rChild] > v[lChild]) ? rChild : lChild;

    if(v[bigger] > v[ind]) {
        T temp = v[ind];
        v[ind] = v[bigger];
        v[bigger] = temp;
        reheapifyDown(bigger);
    } else
        return ;
}

// Public
template <typename T>
myHeap<T>::myHeap(size_t s) {
    v = vector<T>(myCapacity=s, T());
    mySize = 0;
}

template <typename T>
myHeap<T>::~myHeap() {
    v.clear();
    mySize = myCapacity = 0;
}

template <typename T>
myHeap<T>::myHeap(const myHeap<T> &other) {
    copy(other);
}

template <typename T>
myHeap<T>& myHeap<T>::operator=(const myHeap<T> &other) {
    if(this != &other)
        copy(other);
    return *this;
}

template <typename T>
bool myHeap<T>::empty() const {
    return !mySize;
}

template <typename T>
bool myHeap<T>::full() const {
    return myCapacity-1 <= mySize;
}

template <typename T>
size_t myHeap<T>::size() const {
    return mySize;
}

template <typename T>
size_t myHeap<T>::capacity() const {
    return myCapacity;
}

template <typename T>
void myHeap<T>::pop(T &data) {
    if(empty())
        throw EMPTY;
    data = v[0];
    v[0] = v[--mySize];
    v[mySize] = T();
    reheapifyDown(0);
}

template <typename T>
void myHeap<T>::push(const T &data) {
    full() && autoResize(mySize);
    v[mySize] = data;
    reheapifyUp(mySize);
    ++mySize;
}

template <typename T>
myHeap<T>& myHeap<T>::operator>>(T &data) {
    pop(data);
    return *this;
}

template <typename T>
myHeap<T>& myHeap<T>::operator<<(const T &data) {
    push(data);
    return *this;
}

#endif // MYHEAP_H

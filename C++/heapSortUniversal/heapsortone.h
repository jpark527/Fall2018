#ifndef HEAPSORTONE_H
#define HEAPSORTONE_H
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

enum DIRECTION {MIN_SORT, MAX_SORT};

template <typename T>
class heapSortOne {
    vector<T> data;
    function<bool(heapSortOne<T>&, int, int)> *op;
    DIRECTION dir;
    bool lessThan(const T &x, const T &y);
    bool greaterThan(const T &x, const T &y);
    void bubbleUp(int lastEntered);
    void bubbleDown(int lastEntered);
    void swap(T &x, T &y);

public:
    heapSortOne(const vector<T> &v={}, DIRECTION dir=MIN_SORT);
    heapSortOne(const heapSortOne<T> &other);
    ~heapSortOne();
    heapSortOne<T>& operator=(const heapSortOne &other);
    void sort();
    void getData(vector<T> &v) const;

    void operator<<(const vector<T> &d);
    void operator>>(const vector<T> &d);
};

// Public
template <typename T>
heapSortOne<T>::heapSortOne(const vector<T> &v, DIRECTION dir) {
    copy(v.begin(), v.end(), back_inserter(data));
    this->dir = dir;
    op = new function<bool(heapSortOne<T>&, int, int)>[2];
    op[MIN_SORT] = &heapSortOne<T>::lessThan;
    op[MAX_SORT] = &heapSortOne<T>::greaterThan;
}

template <typename T>
heapSortOne<T>::heapSortOne(const heapSortOne<T> &other) {
    copy(other.data.begin(), other.data.end(), back_inserter(this->data));
    dir = other.dir;
    op = new function<bool(heapSortOne<T>&, int, int)>[2];
    op[MIN_SORT] = &heapSortOne<T>::lessThan;
    op[MAX_SORT] = &heapSortOne<T>::greaterThan;
}

template <typename T>
heapSortOne<T>::~heapSortOne() {
    delete[] op;
    data.clear();
    dir = MIN_SORT;
}

template <typename T>
heapSortOne<T>& heapSortOne<T>::operator=(const heapSortOne &other) {
    if(this != &other) {
        copy(other.data.begin(), other.data.end(), back_inserter(this->data));
        dir = other.dir;
    }
    return *this;
}

template <typename T>
void heapSortOne<T>::sort() {
    int size = data.size();
    for(int lastEntered = 0; lastEntered < size; ++lastEntered)
        bubbleUp(lastEntered);
    for(int lastEntered = size-1; lastEntered >= 0; --lastEntered) {
        swap(data[lastEntered], data[0]);
        bubbleDown(lastEntered);
    }
}

template <typename T>
void heapSortOne<T>::getData(vector<T>& d) const {
    d.clear();
    copy(data.begin(), data.end(), back_inserter(d));
}

template <typename T>
void heapSortOne<T>::operator<<(const vector<T> &d) {
    copy(d.begin(), d.end(), back_inserter(this->data));
    dir = MIN_SORT;
    sort();
}

template <typename T>
void heapSortOne<T>::operator>>(const vector<T> &d) {
    copy(d.begin(), d.end(), back_inserter(this->data));
    dir = MAX_SORT;
    sort();
}

// Private
template <typename T>
bool heapSortOne<T>::lessThan(const T &x, const T &y) {
    return x < y;
}

template <typename T>
bool heapSortOne<T>::greaterThan(const T &x, const T &y) {
    return x > y;
}

template <typename T>
void heapSortOne<T>::bubbleUp(int lastEntered) {
    int child = lastEntered, parent = (child - 1) / 2;
    while(child && (op[dir](*this, data[child], data[parent]))) {
        swap(data[child], data[parent]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

template <typename T>
void heapSortOne<T>::swap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
}

template <typename T>
void heapSortOne<T>::bubbleDown(int lastEntered) {
    int parent = 0, lChild, rChild, toSwap;
    bool done = false;
    while(!done && ((lChild = 2*parent + 1) <= lastEntered - 1)) {
        rChild = 2*parent + 2;
        if(rChild > lastEntered - 1)
            toSwap = lChild;
        else
            toSwap = op[dir](*this, data[lChild], data[rChild]) ? lChild : rChild;
        if(op[!dir](*this, data[parent] , data[toSwap])) {
            swap(data[parent], data[toSwap]);
            parent = toSwap;
        }
        else
            done = true;
    }
}

#endif // HEAPSORTONE_H

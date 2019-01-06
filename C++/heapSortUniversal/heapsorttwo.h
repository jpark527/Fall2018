#ifndef HEAPSORTTWO_H
#define HEAPSORTTWO_H
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

enum DIRECTION2 {MIN_SORT2, MAX_SORT2};

template <typename T>
class heapSortTwo {
    vector<T> data, orig;
    function<bool(heapSortTwo<T>&, int, int)> *op;
    DIRECTION2 dir;
    bool lessThan(const T &x, const T &y);
    bool greaterThan(const T &x, const T &y);
    void bubbleUp(int lastEntered);
    void bubbleDown(int lastEntered);
    void swap(T &x, T &y);

public:
    heapSortTwo(const vector<T> &v={}, DIRECTION2 dir=MIN_SORT2);
    heapSortTwo(const heapSortTwo<T> &other);
    ~heapSortTwo();
    heapSortTwo<T>& operator=(const heapSortTwo<T> &other);
    void sort();
    void getData(vector<int> &v);
    DIRECTION2& direction();

    void operator<<(const vector<T> &d);
    void operator>>(vector<int> &d);
};

// Public
template <typename T>
heapSortTwo<T>::heapSortTwo(const vector<T> &v, DIRECTION2 dir) {
    copy(v.begin(), v.end(), back_inserter(data));
    copy(v.begin(), v.end(), back_inserter(orig));
    this->dir = dir;
    op = new function<bool(heapSortTwo<T>&, int, int)>[2];
    op[MIN_SORT2] = &heapSortTwo<T>::lessThan;
    op[MAX_SORT2] = &heapSortTwo<T>::greaterThan;
}

template <typename T>
heapSortTwo<T>::heapSortTwo(const heapSortTwo<T> &other) {
    copy(other.data.begin(), other.data.end(), back_inserter(this->data));
    copy(other.orig.begin(), other.orig.end(), back_inserter(orig));
    dir = other.dir;
    op = new function<bool(heapSortTwo<T>&, int, int)>[2];
    op[MIN_SORT2] = &heapSortTwo<T>::lessThan;
    op[MAX_SORT2] = &heapSortTwo<T>::greaterThan;
}

template <typename T>
heapSortTwo<T>::~heapSortTwo() {
    delete[] op;
    data.clear();
    orig.clear();
    dir = MIN_SORT2;
}

template <typename T>
heapSortTwo<T>& heapSortTwo<T>::operator=(const heapSortTwo<T> &other) {
    if(this != &other) {
        copy(other.data.begin(), other.data.end(), back_inserter(data));
        copy(other.orig.begin(), other.orig.end(), back_inserter(orig));
        dir = other.dir;
    }
    return *this;
}

template <typename T>
void heapSortTwo<T>::sort() {
    int size = data.size();
    for(int lastEntered = 0; lastEntered < size; ++lastEntered)
        bubbleUp(lastEntered);
    for(int lastEntered = size-1; lastEntered >= 0; --lastEntered) {
        swap(data[lastEntered], data[0]);
        bubbleDown(lastEntered);
    }
}

template <typename T>
void heapSortTwo<T>::getData(vector<int>& d) {
    d.clear();
    sort();
    for(size_t i=0; i<orig.size(); ++i) {
        for(size_t j=0; j<data.size(); ++j)
            if(orig[i] == data[j]) {
                d.push_back(j);
                break;
            }
    }
    for(size_t i=0; i<d.size()-1; ++i)
        for(size_t j=i+1; j<d.size(); ++j)
            if(d[i] == d[j])
                d[j] += 1;
}

template <typename T>
DIRECTION2& heapSortTwo<T>::direction() {
    return dir;
}

template <typename T>
void heapSortTwo<T>::operator<<(const vector<T> &d) {
    data.clear();
    orig.clear();
    copy(d.begin(), d.end(), back_inserter(data));
    copy(d.begin(), d.end(), back_inserter(orig));
}

template <typename T>
void heapSortTwo<T>::operator>>(vector<int> &d) {
    getData(d);
}

// Private
template <typename T>
bool heapSortTwo<T>::lessThan(const T &x, const T &y) {
    return x < y;
}

template <typename T>
bool heapSortTwo<T>::greaterThan(const T &x, const T &y) {
    return x > y;
}

template <typename T>
void heapSortTwo<T>::bubbleUp(int lastEntered) {
    int child = lastEntered, parent = (child - 1) / 2;
    while(child && (op[dir](*this, data[child], data[parent]))) {
        swap(data[child], data[parent]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

template <typename T>
void heapSortTwo<T>::swap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
}

template <typename T>
void heapSortTwo<T>::bubbleDown(int lastEntered) {
    int parent = 0, lChild, rChild, toSwap;
    bool done = false;
    while(!done && ((lChild = 2*parent + 1) <= lastEntered - 1)) {
        rChild = 2*parent + 2;
        if(rChild > lastEntered - 1 )
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
#endif // HEAPSORTTWO_H

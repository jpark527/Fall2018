#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

enum BINARY_TREE_ERROR {EMPTY, FULL, BAD_SIZE, BAD_INPUT};

// Node
template <typename D>
struct Node {
    D data;
    int count;
    Node(const D &d=D(), int c=0);
    ~Node();
    Node(const Node<D> &other);
    Node<D> operator=(const Node<D> &other);
};

template <typename D>
Node<D>::Node(const D &d, int c) {
    data = d;
    count = c;
}

template <typename D>
Node<D>::~Node() {
    data = D();
    count = 0;
}

template <typename D>
Node<D>::Node(const Node<D> &other) {
    data = other.data;
    count = other.count;
}

template <typename D>
Node<D> Node<D>::operator=(const Node<D> &other) {
    if(this != &other) {
        data = other.data;
        count = other.count;
    }
    return *this;
}

// Comparator
template <typename C>
struct myComparator {
    bool operator()(const Node<C> *l, const Node<C> *r);
};

template <typename C>
bool myComparator<C>::operator()(const Node<C> *l, const Node<C> *r) {
    return l->data > r->data;           // change DIR here #1
}

// Binary Tree
template <typename T>
class myBinaryTree {
    int totalCount, myCapacity;
    vector<Node<T>*> v, sorted;
    void copyBT(const myBinaryTree<T> &other);
    void initialize(size_t s);
    void deleteAll();
    void rebalance(bool must=false);
    int exists(const T &data) const;
    bool autoResize(size_t s);
    int height(const int &index) const;
    bool full() const;
    int setIndex(const T &data);
    void reInsert(int start, int end, int ind);

public:
    myBinaryTree(size_t s=3);
    ~myBinaryTree();
    myBinaryTree(const myBinaryTree<T> &other);
    myBinaryTree<T>& operator=(const myBinaryTree<T> &other);

    bool empty() const;
    void insertData(const T &d, int c = 1);
    myBinaryTree<T>& operator<<(const T &d);
    myBinaryTree<T>& operator>>(Node<T> &d);
    bool deleteData(const T &d, int c = 1);
    int dataCount() const;
    int nodeCount() const;
    int height() const;

    void print(ostream &out, const size_t &index) const;
};

// Public
template <typename T>
myBinaryTree<T>::myBinaryTree(size_t s) {
    v = vector<Node<T>*>(myCapacity=s, nullptr);
    totalCount = 0;
}

template <typename T>
myBinaryTree<T>::~myBinaryTree() {
    deleteAll();
}

template <typename T>
myBinaryTree<T>::myBinaryTree(const myBinaryTree<T> &other) {
    copyBT(other);
}

template <typename T>
myBinaryTree<T>& myBinaryTree<T>::operator=(const myBinaryTree<T> &other) {
    if(this != &other) {
        deleteAll();
        copyBT(other);
    }
    return *this;
}

template <typename T>
bool myBinaryTree<T>::empty() const {
    return sorted.empty();
}

template <typename T>
void myBinaryTree<T>::insertData(const T &d, int c) {
    int ind = exists(d);
    totalCount += c;
    if(ind != -1) {
        v[ind]->count += c;
    } else {
        ind = setIndex(d);
        v[ind] = new Node<T>(d,c);
        sorted.push_back(v[ind]);
        rebalance();
    }
}

template <typename T>
myBinaryTree<T>& myBinaryTree<T>::operator<<(const T &d) {
    insertData(d);
    return *this;
}

template <typename T>
myBinaryTree<T>& myBinaryTree<T>::operator>>(Node<T> &d) {
    if(empty())
        throw EMPTY;
    size_t index=0;
    while(v[index] && v[2*index+1] && index<v.size())
        index=2*index+1;
    d = *(v[index]);
    deleteData(v[index]->data, v[index]->count);
    return *this;
}

template <typename T>
bool myBinaryTree<T>::deleteData(const T &d, int c) {
    if(empty())
        throw EMPTY;
    int index = exists(d);
    for(size_t i=0; i<sorted.size(); ++i)
        if(sorted[i]->data==d) {
            if(sorted[i]->count==c) {
                swap(sorted[i], sorted[sorted.size()-1]);
                sorted.erase(sorted.end()-1);
            } else
                sorted[i]->count -= c;
            break;
        }
    rebalance(true);
    return index+1;
}

template <typename T>
int myBinaryTree<T>::dataCount() const {
    return totalCount;
}

template <typename T>
int myBinaryTree<T>::nodeCount() const {
    return sorted.size();
}

template <typename T>
int myBinaryTree<T>::height() const {
    return height(0);
}

template <typename T>
void myBinaryTree<T>::print(ostream &out, const size_t &index) const {
    if(v[index] && index < v.size()) {
        print(out, index*2+1);
        out << "v[" << index << "] = (" << v[index]->data << ", " << v[index]->count << ")" << endl;
        print(out, index*2+2);
    }
}

// Private
template <typename T>
void myBinaryTree<T>::copyBT(const myBinaryTree<T> &other) {
    copy(other.v.begin(), other.v.end(), back_inserter(v));
    copy(other.sorted.begin(), other.sorted.end(), back_inserter(sorted));
    totalCount = other.totalCount;
    myCapacity = other.myCapacity;
}

template <typename T>
void myBinaryTree<T>::deleteAll() {
    for(size_t i=0; i<sorted.size(); ++i)
        if(sorted[i]) {
            cout << "Deleting sorted[" << i << "].." << endl;
            delete sorted[i];
        }
    v.clear();
    sorted.clear();
    totalCount = myCapacity = 0;
}

template <typename T>
void myBinaryTree<T>::rebalance(bool must) {
    if(!must && abs(static_cast<double>(height(1) - height(2))) <= 1)
        return ;
    myComparator<T> compare;
    sort(sorted.begin(), sorted.end(), compare);
    v.clear();
    v.resize(myCapacity);
    reInsert(0, sorted.size(), 0);
}

template <typename T>
void myBinaryTree<T>::reInsert(int start, int end, int ind) {
    int mid = (start+end)/2;
    if(find(v.begin(), v.end(), sorted[mid]) != v.end())
        return ;
    else {
        v[ind] = sorted[mid];
        reInsert(start, mid, 2*ind+1);
        reInsert(mid, end, 2*ind+2);
    }
}

template <typename T>
int myBinaryTree<T>::exists(const T &data) const {
    for(size_t i=0; i<v.size(); ++i)
        if(v[i] && v[i]->data == data)
            return i;
    return -1;
}

template <typename T>
bool myBinaryTree<T>::autoResize(size_t s) {
    size_t prev = myCapacity;
    myCapacity = (int) (1.34 * s);
    v.resize(myCapacity);
    for(size_t i=prev; i<v.size(); ++i)
        v[i] = nullptr;
    return true;
}

template <typename T>
int myBinaryTree<T>::height(const int &index) const {
    return (index < myCapacity) && v[index] ? 1 + max(height(2*index+1), height(2*index+2)) : 0;
}

template <typename T>
bool myBinaryTree<T>::full() const {
    return myCapacity-1 <= sorted.size();
}

template <typename T>
int myBinaryTree<T>::setIndex(const T &data) {
    if(empty())
        return 0;
    int child=0, parent=0;
    while(1) {
        if(v[parent]) {
            child = v[parent]->data >= data ? 2*parent+2 : 2*parent+1; // change DIR here #2
            (child >= myCapacity) && autoResize(child);
            parent = child;
        } else
            break;
    }    
    return child;
}

#endif // MYBINARYTREE_H

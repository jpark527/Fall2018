#ifndef MYHEAP_H
#define MYHEAP_H
#include <vector>
#define getParent(i) (i - 1)/2
#define rChild(i) ((2*i) + 1)
#define lChild(i) ((2*i) + 2)

using namespace std;

enum MYHEAP_ERRORS {MYHEAP_EMPTY};

template<typename Data>
class myHeap {
    vector<Data*> tree;
    void copy(const myHeap<Data> &other);
    void heapifyUp(int index);
    void heapifyDown();
    void swap(Data *&x, Data *&y);

public:
    myHeap();
    ~myHeap();
    myHeap(const myHeap<Data> &other);
    myHeap<Data>& operator=(const myHeap<Data> &other);
    myHeap<Data>& operator<<(const Data &d);
    myHeap<Data>& operator>>(Data &d);
    void push(const Data &d);
    void pop(Data &d);
    bool empty() const;
    unsigned int size() const;
};

// Public
template<typename Data>
myHeap<Data>::myHeap() {
    tree.clear();
}

template<typename Data>
myHeap<Data>::~myHeap() {
    for(size_t i=0; i<tree.size(); ++i)
        if(tree[i])
            delete tree[i];
    tree.clear();
}

template<typename Data>
myHeap<Data>::myHeap(const myHeap<Data> &other) {
    copy(other);
}

template<typename Data>
myHeap<Data>& myHeap<Data>::operator=(const myHeap<Data> &other) {
    if(this != &other)
        copy(other);
    return *this;
}

template<typename Data>
myHeap<Data>& myHeap<Data>::operator<<(const Data &d) {
    push(d);
    return *this;
}

template<typename Data>
myHeap<Data>& myHeap<Data>::operator>>(Data &d) {
    pop(d);
    return *this;
}

template<typename Data>
void myHeap<Data>::push(const Data &d) {
    tree.push_back(new Data(d));
    if(tree.size() - 1)
        heapifyUp(tree.size() - 1);
}

template<typename Data>
void myHeap<Data>::pop(Data &d) {
    if(!tree.size())
        throw MYHEAP_EMPTY;
    d = *(tree[0]);
    swap(tree[0], tree[tree.size() - 1]);
    delete tree[tree.size()-1];
    tree[tree.size()-1] = nullptr;
    tree.pop_back();
    if(tree.size() > 2)
        heapifyDown();
    if(tree.size() == 2)
        if(*(tree[0]) < *(tree[tree.size() - 1]))
            swap(tree[0],tree[tree.size() - 1]);
}

template<typename Data>
bool myHeap<Data>::empty() const {
    return tree.empty();
}

template<typename Data>
unsigned int myHeap<Data>::size() const {
    return tree.size();
}

// Private
template<typename Data>
void myHeap<Data>::copy(const myHeap<Data> &other) {
    for(size_t i=0; i<tree.size(); ++i)
        if(tree[i]) {
            delete tree[i];
            tree[i] = nullptr;
        }
    tree.clear();
    for(size_t i=0; i<other.tree.size(); ++i)
        tree.push_back(new Data(*other.tree[i]));
}

template<typename Data>
void myHeap<Data>::heapifyUp(int index) {
    int parent = getParent(index);
    while(index && *(tree[index]) > *(tree[parent])) {
        swap(tree[index], tree[parent]);
        index = parent;
        parent = getParent(index);
    }
}

template<typename Data>
void myHeap<Data>::heapifyDown() {
    int index = 0, move = 0;
    while(1) {
        if(lChild(index) > tree.size() - 1)
            break;
        else {
            if(rChild(index) > tree.size() - 1)
                index = lChild(index);
            else
                index = *(tree[lChild(index)]) >= *(tree[rChild(index)]) ?
                            lChild(index) : rChild(index);
            if(*(tree[index]) > *(tree[move])) {
                swap(tree[move],tree[index]);
                move = index;
            }
            else
                break;
        }
    }
}

template<typename Data>
void myHeap<Data>::swap(Data *&x, Data *&y) {
    Data *temp = x;
    x = y;
    y = temp;
}

#endif // MYHEAP_H

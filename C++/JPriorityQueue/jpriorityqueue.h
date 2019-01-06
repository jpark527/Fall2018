#ifndef JPRIORITYQUEUE_H
#define JPRIORITYQUEUE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "node.h"

using namespace std;

enum P_QUE_ERROR { EMPTY, FULL, BAD_SIZE };

template <typename D, typename P>
class JPriorityQueue {
    Node<D,P> *arr;
    size_t head, tail, myCapacity, mySize;
    void sort();
    void copy(const JPriorityQueue<D,P> &cpy);
    void eraseAll();
public:
    JPriorityQueue(size_t s = 10);
    ~JPriorityQueue();
    JPriorityQueue(const JPriorityQueue &rhs);
    JPriorityQueue<D,P>& operator=(const JPriorityQueue<D,P> &rhs);

    void peek(D &d) const;
    void enqueue(const D &d, const P &p);
    void dequeue(D &d);
    bool empty() const;
    bool full() const;
    size_t size() const;
    size_t capacity() const;
    void resize(size_t s);
    JPriorityQueue<D,P>& operator>>(D &data);

    template <typename Data, typename Priority>
    friend ostream& operator<<(ostream &out, const JPriorityQueue<Data, Priority> &pQue);

    template <typename Data, typename Priority>
    friend istream& operator>>(istream &in, JPriorityQueue<Data, Priority> &pQue);
};

// Private
template <typename D, typename P>
void JPriorityQueue<D,P>::sort() {
    if(mySize < 2)
        return;
    for(size_t i=head, j=0; j<mySize-1; ++j, i=(i+1)%myCapacity)
        if(arr[tail] > arr[i]) {
            Node<D,P> temp(arr[i]);
            arr[i] = arr[tail];
            arr[tail] = temp;
        }
}

template <typename D, typename P>
void JPriorityQueue<D,P>::copy(const JPriorityQueue<D,P> &cpy) {
    arr = new Node<D,P>[this->myCapacity = cpy.myCapacity];
    this->head = cpy.head;
    this->tail = cpy.tail;
    this->mySize = cpy.mySize;
    for(size_t i=0; i<myCapacity; ++i)
        arr[i] = cpy.arr[i];
}

template <typename D, typename P>
void JPriorityQueue<D,P>::eraseAll() {
    myCapacity = mySize = head = tail = 0;
    delete[] arr;
}

// Public
template <typename D, typename P>
JPriorityQueue<D,P>::JPriorityQueue(size_t s) {
    if(s < 2)
        throw BAD_SIZE;
    arr = new Node<D,P>[myCapacity = s];
    head = tail = mySize = 0;
}

template <typename D, typename P>
JPriorityQueue<D,P>::~JPriorityQueue() {
    eraseAll();
}

template <typename D, typename P>
JPriorityQueue<D,P>::JPriorityQueue(const JPriorityQueue &rhs) {
    copy(rhs);
}

template <typename D, typename P>
JPriorityQueue<D,P>& JPriorityQueue<D,P>::operator=(const JPriorityQueue<D,P> &rhs) {
    if(this != &rhs) {
        eraseAll();
        copy(rhs);
    }
    return *this;
}

template <typename D, typename P>
void JPriorityQueue<D,P>::peek(D &d) const {
    if(empty())
        throw EMPTY;
    d = arr[head].data;
}

template <typename D, typename P>
void JPriorityQueue<D,P>::enqueue(const D &d, const P &p) {
    if(full())
        throw FULL;
    if(empty())
        arr[head].data = d,
        arr[head].priority = p;
    else
        tail = (tail + 1) % myCapacity;
        arr[tail].data = d,
        arr[tail].priority = p;
    ++mySize;
    sort();
}

template <typename D, typename P>
void JPriorityQueue<D,P>::dequeue(D &d) {
    if(empty())
        throw EMPTY;
    d = arr[head].data;
    head = (head+1) % myCapacity;
    --mySize;
}

template <typename D, typename P>
bool JPriorityQueue<D,P>::empty() const {
    return !mySize;
}

template <typename D, typename P>
bool JPriorityQueue<D,P>::full() const {
    return mySize == myCapacity;
}

template <typename D, typename P>
size_t JPriorityQueue<D,P>::size() const {
    return mySize;
}

template <typename D, typename P>
size_t JPriorityQueue<D,P>::capacity() const {
    return myCapacity;
}

template <typename D, typename P>
void JPriorityQueue<D,P>::resize(size_t s) {
    if(s < 2)
        throw BAD_SIZE;
    if(s < myCapacity) {
        Node<D,P> *newArr = new Node<D,P>[s];
        size_t newSize = s > mySize ? mySize : s;
        for(size_t i=0; i<newSize; ++i, ++head)
            newArr[i] = arr[head % myCapacity];
        mySize = newSize;
        head = 0;
        tail = mySize - 1;
        delete[] arr;
        arr = newArr;
    }
    myCapacity = s;
}

template <typename D, typename P>
JPriorityQueue<D,P>& JPriorityQueue<D,P>::operator>>(D &data) {
    dequeue(data);
    return *this;
}

// Friends
template <typename Data, typename Priority>
ostream& operator<<(ostream &out, const JPriorityQueue<Data, Priority> &pQue) {
    if(&out != &cout)
        out << "PriorityQueue capacity: " << pQue.myCapacity << endl;
    for(size_t i=pQue.head, j=0; j<pQue.mySize; ++j, i=(i+1)%pQue.myCapacity)
        out << pQue.arr[i];
    return out;
}

template <typename Data, typename Priority>
istream& operator>>(istream &in, JPriorityQueue<Data, Priority> &pQue) {
    Node<Data, Priority> myNode;
    if(&in != &cin) {
        string line("");
        getline(in, line, ':');        
    } else
        cout << "Enter size: ";
    in >> pQue.myCapacity;
    while(!pQue.full() && in >> myNode)
        pQue.enqueue(myNode.data, myNode.priority);
    return in;
}

#endif // JPRIORITYQUEUE_H

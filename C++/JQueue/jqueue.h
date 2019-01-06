#ifndef JQUEUE_H
#define JQUEUE_H
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

enum JQUEUE_ERROR { FULL, EMPTY, BAD_SIZE };

template <typename T>
struct Node {
    Node *next;
    T data;

    Node(const T &d = T());
    ~Node();
    Node(const Node<T> &rhs);
    Node& operator=(const Node<T> &rhs);
};

template <typename T>
Node<T>::Node(const T &d) {
    data = d;
    next = nullptr;
}

template <typename T>
Node<T>::~Node() {
    data = T();
    next = nullptr;
}

template <>
Node<char*>::~Node() {
    if(data && data!="\n")
        delete data;
    next = nullptr;
}

template <typename T>
Node<T>::Node(const Node<T> &rhs) {
    data = rhs.data;
    next = nullptr;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T> &rhs) {
    if(this != &rhs) {
        data = rhs.data;
        next = nullptr;
    }
    return *this;
}

template <typename T>
class JQueue {
    Node<T> *first, *last;
    size_t mySize, myCapacity;
    void copy(const JQueue<T> &rhs);
    void eraseAll();

public:
    JQueue(size_t s = 10);
    ~JQueue();
    JQueue(const JQueue<T> &rhs);
    JQueue<T>& operator=(const JQueue<T> &rhs);

    bool empty() const;
    bool full() const;
    size_t size() const;
    size_t capacity() const;
    void resize(size_t s);
    void clear();
    void enqueue(const T &data);
    void dequeue(T &data);

    JQueue<T>& operator<<(const T &data);
    JQueue<T>& operator>>(T &data);

    template <typename S>
    friend istream& operator>>(istream& in, JQueue<S> &que);

    template <typename S>
    friend ostream& operator<<(ostream& out, const JQueue<S> &que);
};

// Private
template <typename T>
void JQueue<T>::copy(const JQueue<T> &rhs) {
    Node<T> *me, *you;
    first = last = nullptr;
    mySize = rhs.mySize;
    myCapacity = rhs.myCapacity;
    if(rhs.empty())
        return;
    first = new Node<T>(rhs.first->data);
    me = first, you = rhs.first;
    while(you) {
        me->next = new Node<T>(you->next->data);
        me = me->next;
        you = you->next;
    }
    last = me;
}

template <typename T>
void JQueue<T>::eraseAll() {
    for(size_t i=0; first && i<mySize; ++i) {
        Node<T> *bye;
        bye = first;
        first = first->next;
        delete bye;
    }
    mySize = myCapacity = 0;
}

// Public
template <typename T>
JQueue<T>::JQueue(size_t s) {
    myCapacity = s;
    mySize = 0;
}

template <typename T>
JQueue<T>::~JQueue() {
    eraseAll();
}

template <typename T>
JQueue<T>::JQueue(const JQueue<T> &rhs) {
    copy(rhs);
}

template <typename T>
JQueue<T>& JQueue<T>::operator=(const JQueue<T> &rhs) {
    if(this != &rhs) {
        eraseAll();
        copy(rhs);
    }
    return *this;
}

template <typename T>
bool JQueue<T>::empty() const {
    return !mySize;
}

template <typename T>
bool JQueue<T>::full() const {
    return mySize == myCapacity;
}

template <typename T>
size_t JQueue<T>::size() const {
    return mySize;
}

template <typename T>
size_t JQueue<T>::capacity() const {
    return myCapacity;
}

template <typename T>
void JQueue<T>::resize(size_t s) {
    if(s < mySize) {
        Node<T> *me;
        me = first;
        for(size_t i=1; i<s; ++i)
            me = me->next;
        last = me;
        me = me->next;
        while(me) {
            Node<T> *bye;
            bye = me;
            me = me->next;
            delete bye;
        }
        mySize = s;
    }
    myCapacity = s;
}

template <typename T>
void JQueue<T>::clear() {
    size_t temp = myCapacity;
    eraseAll();
    myCapacity = temp;
}

template <typename T>
void JQueue<T>::enqueue(const T &data) {
    if(full())
        throw FULL;
    if(empty()) {
        first = new Node<T>(data);
        last = first;
    } else {
        Node<T> *newNode = new Node<T>(data);
        last->next = newNode;
        last = last->next;
    }
    ++mySize;
}

template <typename T>
void JQueue<T>::dequeue(T &data) {
    if(empty())
        throw EMPTY;
    data = first->data;
    Node<T> *bye;
    bye = first;
    first = first->next;
    delete bye;
    --mySize;
}

template <typename T>
JQueue<T>& JQueue<T>::operator<<(const T &data) {
    enqueue(data);
    return *this;
}

template <typename T>
JQueue<T>& JQueue<T>::operator>>(T &data) {
    dequeue(data);
    return *this;
}

// Friends
template <typename S>
istream& operator>>(istream& in, JQueue<S> &que) {
    if(&in != &cin) {
        string line;
        getline(cin, line, ':');
        in >> que.myCapacity;
        getline(cin, line);
    } else {
        cout << "Enter size: ";
        in >> que.myCapacity;
    }
    S data;
    while(!que.full() && in >> data)
        que << data;
    return in;
}

template <>
istream& operator>>(istream& in, JQueue<string> &que) {
    string line("");
    if(&in != &cin) {
        getline(in, line, ':');
        in >> que.myCapacity;
        getline(in, line);
    } else {
        cout << "Enter size: ";
        in >> que.myCapacity;
        cout << "Enter data:\n";
    }
    if(in.peek()=='\n')
        in.ignore(32767, '\n');
    do {
        getline(in, line);
        que << line;
    } while(!que.full() && !line.empty());
    return in;
}

template <>
istream& operator>>(istream& in, JQueue<char*> &que) {
    string line("");
    if(&in != &cin) {
        getline(cin, line, ':');
        in >> que.myCapacity;
        getline(cin, line);
    } else {
        cout << "Enter size: ";
        in >> que.myCapacity;
        cout << "Enter data:\n";
    }
    if(in.peek()=='\n')
        in.ignore(32767, '\n');
    do {
        getline(in, line);
        char *data = new char[line.length()];
        strcpy(data, line.c_str());
        que << data;
    } while(!que.full() && !line.empty());
    return in;
}

template <typename S>
ostream& operator<<(ostream& out, const JQueue<S> &que) {
    Node<S> *temp;
    temp = que.first;
    if(&out != &cout) {
        out << "Queue capacity: " << que.myCapacity << endl
            << "Queue size: " << que.mySize << endl;
    }
    for(size_t i=0; temp && i<que.mySize; ++i) {
        out << temp->data << endl;
        temp = temp->next;
    }
    return out;
}

#endif // JQUEUE_H

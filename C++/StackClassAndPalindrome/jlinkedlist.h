#ifndef JLINKEDLIST_H
#define JLINKEDLIST_H
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

enum LINKED_LIST_ERROR { LL_EMPTY, LL_BAD_SIZE };

template <typename S>
struct Node {
    S data;
    Node* next;

    Node(const S &data);
    Node(const Node<S> &rhs);
    Node<S>& operator=(const Node<S> &rhs);
    ~Node();
};

template <typename S>
Node<S>::Node(const S &data) {
    this->data = data;
    next = NULL;
}

template <typename S>
Node<S>::Node(const Node<S> &rhs) {
    data = rhs.data;
    next = NULL;
}

template <typename S>
Node<S>& Node<S>::operator=(const Node<S> &rhs) {
    if(this != &rhs) {
        data = rhs.data;
        next = NULL;
    }
    return *this;
}

template <typename S>
Node<S>::~Node() {
    data = S();
    next = NULL;
}

template <typename T>
class JLinkedList {
    Node<T>* head; // Head all the way in.
    size_t length;
    void copy(const JLinkedList<T> &rhs);
protected:
    void eraseAll();
    T pop();
public:
    JLinkedList(size_t size=0, const T &value=T()); // Notice: null of char* will NOT print!!!
    JLinkedList(const JLinkedList<T> &rhs);
    ~JLinkedList();
    JLinkedList<T>& operator=(const JLinkedList<T> &rhs);

    size_t size() const;
    void pushFront(const T& value);         // Puts value from the head  - for STACK!
    T get(size_t index) const;              // Gives value from the head
    T operator[](size_t index) const;       // This NEVER gets called!
    T& operator[](size_t index);            // index [0] = tail ... index [size()-1] = head
    JLinkedList<T>& operator<<(const T &value); // Puts value from the head - for STACK!

    template <typename U>
    friend istream& operator>>(istream& in, JLinkedList<U> &list);

    template <typename U>
    friend ostream& operator<<(ostream& out, const JLinkedList<U> &list);
};

// Private
template <typename T>
void JLinkedList<T>::copy(const JLinkedList<T> &rhs) {
    Node<T> *mine, *yours;
    head = NULL;
    length = rhs.length;
    if(!rhs.head)
        return;
    head = new Node<T>(rhs.head->data);
    mine = head;
    yours = rhs.head;
    while(yours->next) {
        mine->next = new Node<T>(yours->next->data);
        mine = mine->next;
        yours = yours->next;
    }
}

// Protected
template <typename T>
void JLinkedList<T>::eraseAll() {
    length = 0;
    while(head) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

template <>
void JLinkedList<char*>::eraseAll() {
    length = 0;
    while(head) {
        Node<char*> *temp = head;
        head = head->next;
        delete[] temp->data;
        delete temp;
    }
}

template <typename T>
T JLinkedList<T>::pop() {
    if(!head)
        throw LL_EMPTY;
    Node<T> *mine = head;
    head = head->next;
    T value = mine->data;
    delete mine;
    --length;
    return value;
}

// Public
template <typename T>
JLinkedList<T>::JLinkedList(size_t size, const T &value) {
    head = NULL;
    length = 0;
    for(size_t i=0; i<size; ++i)
        pushFront(value);
}

template <typename T>
JLinkedList<T>::JLinkedList(const JLinkedList<T> &rhs) {
    eraseAll();
    copy(rhs);
}

template <typename T>
JLinkedList<T>::~JLinkedList() {
    eraseAll();
}

template <typename T>
JLinkedList<T>& JLinkedList<T>::operator=(const JLinkedList<T> &rhs) {
    if(this != &rhs) {
        eraseAll();
        copy(rhs);
    }
    return *this;
}

template <typename T>
size_t JLinkedList<T>::size() const {
    return length;
}

template <typename T>
void JLinkedList<T>::pushFront(const T& value) {
    Node<T> *newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    ++length;
}

template <typename T>
T JLinkedList<T>::get(size_t index) const {
    if(length < index+1)
        throw LL_BAD_SIZE;
    if(!head)
        throw LL_EMPTY;
    Node<T> *mine = head;
    for(size_t i=index; i; --i)
        mine = mine->next;
    return mine->data;
}

template <typename T>
T JLinkedList<T>::operator[](size_t index) const {     // This NEVER gets called!
    return get(index);
}

template <typename T>
T& JLinkedList<T>::operator[](size_t index) {
    if(length < index+1)
        throw LL_BAD_SIZE;
    if(!head)
        throw LL_EMPTY;
    Node<T> *mine = head;
    int count = length-index-1;
    while(count) {
        mine = mine->next;
        --count;
    }
    return mine->data;
}

template <typename T>
JLinkedList<T>& JLinkedList<T>::operator<<(const T &value) {
    pushFront(value);
    return *this;
}

template <typename U>
istream& operator>>(istream& in, JLinkedList<U> &list) {
    size_t size = 0;
    list.eraseAll();
    list.head = NULL;
    if(&in != &cin) {
        string line;
        getline(cin, line, ':');
        in >> size;
    } else {
        cout << "Enter size: ";
        in >> size;
        for(size_t i=0; i<size; ++i)
            list.pushFront(U());
        cout << "Enter data:" << endl;
    }
    U value = U();
    for(int i=size-1; i>=0; --i) {
        in >> value;
        list[i] = value;
    }
    return in;
}

template <>
istream& operator>>(istream& in, JLinkedList<char*> &list) {
    size_t size = 0;
    string line("");
    list.eraseAll();
    list.head = NULL;
    if(&in != &cin) {
        getline(cin, line, ':');
        in >> size;
    } else {
        cout << "Enter size: ";
        in >> size;
        for(size_t i=0; i<size; ++i)
            list.pushFront(NULL);
        cout << "Enter data:" << endl;
    }
    in.ignore(32767, '\n');
    for(int i=size-1; i>=0; --i) {
        getline(in, line);
        char* value = new char[line.length()];
        strcpy(value, line.c_str());
        list[i] = value;
    }
    return in;
}

template <>
istream& operator>>(istream& in, JLinkedList<string> &list) {
    size_t size = 0;
    list.eraseAll();
    list.head = NULL;
    if(&in != &cin) {
        string line;
        getline(cin, line, ':');
        in >> size;
    } else {
        cout << "Enter size: ";
        in >> size;
        for(size_t i=0; i<size; ++i)
            list.pushFront("");
        cout << "Enter data:" << endl;
    }
    in.ignore(32767, '\n');
    string value("");
    for(int i=size-1; i>=0; --i) {
        getline(in, value);
        if(value.empty())
            break;
        list[i] = value;
    }
    return in;
}

template <typename U>
ostream& operator<<(ostream& out, const JLinkedList<U> &list) {
    if(&out != &cout)
        out << "List length: " << list.length << endl;
    for(int i=0; i<list.size(); ++i)
        out << "list[" << i << "] = " << list[i] << endl;
    return out;
}

#endif // JLINKEDLIST_H

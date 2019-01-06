#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>

using namespace std;

template <typename D, typename P>
struct Node {
    D data;
    P priority;
    Node(D data = D(), P priority = P());
    ~Node();
    Node(const Node<D,P> &rhs);
    Node<D,P>& operator=(const Node<D,P> &rhs);

    template <typename Data, typename Priority>
    friend bool operator>(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs);

    template <typename Data, typename Priority>
    friend bool operator>=(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs);

    template <typename Data, typename Priority>
    friend bool operator<(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs);

    template <typename Data, typename Priority>
    friend bool operator<=(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs);

    template <typename Data, typename Priority>
    friend bool operator==(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs);

    template <typename Data, typename Priority>
    friend ostream& operator<<(ostream &out, const Node &n);

    template <typename Data, typename Priority>
    friend istream& operator>>(istream &in, Node &n);
};

template <typename D, typename P>
Node<D,P>::Node(D data, P priority) {
    this->data = data;
    this->priority = priority;
}

template <typename D, typename P>
Node<D,P>::~Node() {
    this->data = D();
    this->priority = P();
}

template <typename D, typename P>
Node<D,P>::Node(const Node<D,P> &rhs) {
    this->data = rhs.data;
    this->priority = rhs.priority;
}

template <typename D, typename P>
Node<D,P>& Node<D,P>::operator=(const Node<D,P> &rhs) {
    if(this != &rhs)
        this->data = rhs.data,
        this->priority = rhs.priority;
    return *this;
}

// Friends
template <typename Data, typename Priority>
bool operator>(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs) {
    return lhs.priority > rhs.priority;
}

template <typename Data, typename Priority>
bool operator>=(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs) {
    return lhs.priority >= rhs.priority;
}

template <typename Data, typename Priority>
bool operator<(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs) {
    return lhs.priority < rhs.priority;
}

template <typename Data, typename Priority>
bool operator<=(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs) {
    return lhs.priority <= rhs.priority;
}

template <typename Data, typename Priority>
bool operator==(const Node<Data, Priority> &lhs, const Node<Data, Priority> &rhs) {
    return lhs.priority == rhs.priority;
}

template <typename Data, typename Priority>
ostream& operator<<(ostream &out, const Node<Data, Priority> &n) {
    if(&out != &cout)
        out << n.data << '\007' << n.priority << endl;
    else
        out << n.data << " : " << n.priority << endl;
    return out;
}

template <typename Data, typename Priority>
istream& operator>>(istream &in, Node<Data, Priority> &n) {
    char trash;
    if(&in != &cin)
        in >> n.data >> trash >> n.priority;
    else {
        cout << "Enter data: ";
        in >> n.data;
        cout << "Enter priority: ";
        in >> n.priority;
    }
    return in;
}

template <>
istream& operator>>(istream &in, Node<string, int> &n) {
    string line("");
    if(in.peek()=='\n')
        in.ignore(32767, '\n');
    if(&in != &cin) {
        getline(in, line);
        n.data = line.substr(0, line.find_first_of('\007'));
        n.priority = line[line.length()-1] - 48;
    } else {
        cout << "Enter data: ";
        getline(in, n.data);
        cout << "Enter priority: ";
        in >> n.priority;
    }
    return in;
}


#endif // NODE_H

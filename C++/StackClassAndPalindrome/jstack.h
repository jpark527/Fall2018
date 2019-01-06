#ifndef JSTACK_H
#define JSTACK_H
#include "jlinkedlist.h"
#include <fstream>

template <typename T>
class JStack : public JLinkedList<T> {
public:
    JStack();
    JStack(const JStack<T> &rhs);
    ~JStack();
    JStack<T>& operator=(const JStack<T> &rhs);

    bool empty() const;
    T peek() const;
    void push(const T &value);
    T pop();

    JStack<T>& operator>>(T &value);
};

template <typename T>
JStack<T>::JStack() : JLinkedList<T>(0, T()) { }

template <typename T>
JStack<T>::JStack(const JStack<T> &rhs) {
    (*this) = rhs;
}

template <typename T>
JStack<T>::~JStack() { }

template <typename T>
JStack<T>& JStack<T>::operator=(const JStack<T> &rhs) {
    if(this != &rhs) {
        (*this) = rhs;
    }
    return *this;
}

template <typename T>
bool JStack<T>::empty() const {
    return !JLinkedList<T>::size();
}

template <typename T>
T JStack<T>::peek() const {
    return JLinkedList<T>::get(0);
}

template <typename T>
void JStack<T>::push(const T &value) {
    JLinkedList<T>::operator<<(value);
}

template <typename T>
T JStack<T>::pop() {
    return JLinkedList<T>::pop();
}

template <typename T>
JStack<T>& JStack<T>::operator>>(T &value) {
    value = pop();
    return *this;
}

#endif // JSTACK_H

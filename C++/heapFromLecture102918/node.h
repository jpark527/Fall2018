#ifndef NODE_H
#define NODE_H
#include <cstdlib>

enum NODE_CHILD {LEFT_CHILD, RIGHT_CHILD};

template<typename T>
struct node
{
    node(const T &d = T());
    ~node();
    node(const node<T> &other);
    node<T>& operator=(const node<T> &other);
    void swap(node<T> &other);

    T data;
    node<T> *child[2];

    template<typename U>
    friend
    bool operator<(const node<U> & x, const node<U> &y);

    template<typename U>
    friend
    bool operator>(const node<U> & x, const node<U> &y);
};

template<typename T>
node<T>::node(const T &d) :
    data(d)
{
    child[0] = child[1] = nullptr;
}

template<typename T>
node<T>::~node()
{
    data = T();
    child[0] = child[1] = nullptr;
}

template<typename T>
node<T>::node(const node<T> &other)
{
    data = other.data;
    child[0] = child[1] = nullptr;
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        data = other.data;
        child[0] = child[1] = nullptr;
    }
    return *this;
}

template<typename T>
void node<T>::swap(node<T> &other)
{
    T temp = data;
    data = other.data;
    other.data = temp;
}

template<typename U>
bool operator<(const node<U> & x, const node<U> &y)
{
    return x.data < y.data;
}

template<typename U>
bool operator>(const node<U> & x, const node<U> &y)
{
    return x.data > y.data;
}

#endif // NODE_H

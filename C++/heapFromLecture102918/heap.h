#ifndef HEAP_H
#define HEAP_H
#include <bitset>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "node.h"

enum HEAP_ERRORS {HEAP_EMPTY, HEAP_FULL, HEAP_BAD_SIZE};

template<typename T>
class heap
{
public:
    heap();
    ~heap();
    heap(const heap<T> &other);
    heap<T>& operator=(const heap<T> &other);

    heap<T>& operator<<(const T &data);
    heap<T>& operator>>(T &data);

    void pop(T &data);
    void push(const T &data);
    bool empty();
    bool full();

private:
    node<T> *root;
    unsigned int lastEntered;

    void copy(const heap<T> &other);
    void copy(node<T> *&me, const node<T> *you);
    bool deleteAll(node<T> *&r);

    void reheapifyDown();
    void reheapifyUp();
    node<T>* parentOfNewLastEntered(int where);

};


template<typename T>
heap<T>::heap() :
    root(nullptr),
    lastEntered(0)
{

}

template<typename T>
heap<T>::~heap()
{
    root && deleteAll(root);
    /*
     * if(root)
     *    deleteAll(root);
     */
}

template<typename T>
heap<T>::heap(const heap<T> &other)
{
    copy(other);
}

template<typename T>
heap<T>& heap<T>::operator=(const heap<T> &other)
{
    if(this != &other)
    {
        root && deleteAll(root);
        copy(other);
    }
    return *this;
}

template<typename T>
heap<T>& heap<T>::operator<<(const T &data)
{
    push(data);
    return *this;
}

template<typename T>
heap<T>& heap<T>::operator>>(T &data)
{
    pop(data);
    return *this;
}


template<typename T>
void heap<T>::pop(T &data)
{
    node<T> *parent;
    if(empty())
        throw HEAP_EMPTY;
    data = root->data;
    parent = parentOfNewLastEntered(lastEntered);
    if(lastEntered == 1)
    {
        delete root;
        root = nullptr;
    }
    else
    {
        root->swap(*parent->child[lastEntered%2]);
        delete parent->child[lastEntered%2];
        parent->child[lastEntered%2] = nullptr;
    }
    --lastEntered;
    reheapifyDown();
}

template<typename T>
void heap<T>::push(const T &data)
{
    if(full())
        throw HEAP_FULL;
    ++lastEntered;
    node<T> *newNode = new node<T>(data), *parent;
    if(!root)
        root = newNode;
    else
    {
        parent = parentOfNewLastEntered(lastEntered);
        parent->child[lastEntered%2] = newNode;
        reheapifyUp();
    }
}

template<typename T>
node<T>* heap<T>::parentOfNewLastEntered(int where)
{
    node<T> *movement = root;
    std::bitset<32> path(where);
    int firstOne = static_cast<int>(log2(where));
    for(int i = firstOne-1; i > 0; --i)
        movement = movement->child[path[i]];
    return movement;
}

template<typename T>
bool heap<T>::empty()
{
    return !root;
}

template<typename T>
bool heap<T>::full()
{
    return false;
}

template<typename T>
void heap<T>::copy(const heap<T> &other)
{
    root = new node<T>(other.root->data);
    lastEntered = other.lastEntered;
    copy(root, other.root);
}

template<typename T>
bool heap<T>::deleteAll(node<T>* &r)
{
    //    if(!r)
    //        return;
    for(unsigned int i = 0; i < 2; ++i)
        if(r->child[i])
            deleteAll(r->child[i]);
    delete r;
    r = nullptr;
    return true;
}

template<typename T>
void heap<T>::copy(node<T>* &me, const node<T> *you)
{
    if(you)
    {
        if(you->child[LEFT_CHILD]) {
            me->child[LEFT_CHILD] = new node<T>(you->child[LEFT_CHILD]->data);
            copy(me->child[LEFT_CHILD], you->child[LEFT_CHILD]);
        }
        if(you->child[RIGHT_CHILD]) {
            me->child[RIGHT_CHILD] = new node<T>(you->child[RIGHT_CHILD]->data);
            copy(me->child[RIGHT_CHILD], you->child[RIGHT_CHILD]);
        }
    }
}

template<typename T>
void heap<T>::reheapifyDown()
{
    bool done = lastEntered <= 1;
    node<T> *move = root, *possiblySwap;
    while(!done)
    {
        if(!move->child[LEFT_CHILD])
            done = true;
        else
        {
            if(!move->child[RIGHT_CHILD])
                possiblySwap = move->child[LEFT_CHILD];
            else
            {
                possiblySwap = move->child[LEFT_CHILD]->data >= move->child[RIGHT_CHILD]->data ?
                            move->child[LEFT_CHILD] : move->child[RIGHT_CHILD];
            }
            if(*possiblySwap > *move)
            {
                move->swap(*possiblySwap);
                move = possiblySwap;
            }
            else
                done = true;
        }

    }
}

template<typename T>
void heap<T>::reheapifyUp()
{
    int child = lastEntered, parent = child / 2;
    node<T> *parentNode;
    while(child > 1)
    {
        parentNode = parentOfNewLastEntered(child);
        if(*parentNode->child[child % 2] > *parentNode)
        {
            parentNode->swap(*parentNode->child[child%2]);
            child = parent;
            parent = child / 2;
        }
        else
            break;
    }
}

#endif // HEAP_H

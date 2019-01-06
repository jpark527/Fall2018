#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
#include <fstream>
#include "node.h"

enum PQUEUE_ERRORS {EMPTY, FULL, BAD_SIZE};

template<typename Data, typename Priority>
class priorityQueue
{
    public:
        priorityQueue(unsigned int s = 10);
        ~priorityQueue();
        priorityQueue(const priorityQueue<Data,Priority> &other);
        priorityQueue<Data,Priority>& operator=(const priorityQueue<Data,Priority> &other);

        void  peek(Data &d, Priority &p) const;
        void enqueue(const Data &d, const Priority &p);
        void dequeue(Data &d, Priority &p);
        bool empty() const;
        bool full() const;
        unsigned int size() const;
        unsigned int capacity() const;
        void resize(unsigned int s = 10);

        template<typename D, typename P>
        friend
        std::ostream& operator<<(std::ostream &out, const priorityQueue<D,P> &pQueue);

        template<typename D, typename P>
        friend
        std::istream& operator>>(std::istream &in, priorityQueue<D,P> &pQueue);

    private:
        node<Data, Priority> *front, *rear;
        unsigned int mySize, myCapacity;

        void copy(const priorityQueue<Data,Priority> &other);
        void deleteAllNodes();
};


template<typename Data, typename Priority>
priorityQueue<Data,Priority>::priorityQueue(unsigned int cap)
{
    front = rear = nullptr;
    myCapacity = cap;
    mySize = 0;
}

template<typename Data, typename Priority>
priorityQueue<Data,Priority>::~priorityQueue()
{
    deleteAllNodes();
}

template<typename Data, typename Priority>
priorityQueue<Data,Priority>::priorityQueue(const priorityQueue<Data,Priority> &other)
{
    copy(other);
}

template<typename Data, typename Priority>
priorityQueue<Data,Priority>& priorityQueue<Data,Priority>::operator=(const priorityQueue<Data,Priority> &other)
{
    if(this != &other)
    {
        deleteAllNodes();
        copy(other);
    }
    return *this;
}


template<typename Data, typename Priority>
void  priorityQueue<Data,Priority>::peek(Data &d, Priority &p) const
{
    if(empty())
        throw EMPTY;
    d = front->data;
    p = front->priority;
}

template<typename Data, typename Priority>
void priorityQueue<Data,Priority>::enqueue(const Data &d, const Priority &p)
{
    if(full())
        throw FULL;
    ++mySize;
    node<Data,Priority> *newNode = new node<Data,Priority>(d,p);
    if(!(front && rear))
        front = rear = newNode;


    if(*newNode <= *rear)
    {
        rear->lower = newNode;
        newNode->higher = rear;
        rear = newNode;
    }
    else
        if(*newNode > *front)
        {
                newNode->lower = front;
                front->higher = newNode;
                front = front->higher;
        }
        else
        {
            node<Data,Priority> *where = rear;
            while(*newNode > *(where->higher))
                where = where->higher;
            newNode->lower = where;
            newNode->higher = where->higher;
            where->higher->lower = newNode;
            where->higher = newNode;
        }
}

template<typename Data, typename Priority>
void priorityQueue<Data,Priority>::dequeue(Data &d, Priority &p)
{
    if(empty())
        throw EMPTY;
    d = front->data;
    p = front->priority;
    --mySize;

    if(front->lower)
    {
        front = front->lower;
        delete front->higher;
        front->higher = nullptr;
    }
    else
    {
        delete front;
        front = rear = nullptr;
    }
}

template<typename Data, typename Priority>
bool priorityQueue<Data,Priority>::empty() const
{
    return mySize == 0;
}

template<typename Data, typename Priority>
bool priorityQueue<Data,Priority>::full() const
{
    return mySize == myCapacity;
}

template<typename Data, typename Priority>
unsigned int priorityQueue<Data,Priority>::size() const
{
    return mySize;
}

template<typename Data, typename Priority>
unsigned int priorityQueue<Data,Priority>::capacity() const
{
    return myCapacity;
}

template<typename Data, typename Priority>
void priorityQueue<Data,Priority>::resize(unsigned int s)
{
    if(s < 1)
        throw BAD_SIZE;
    if(s >= myCapacity)
        myCapacity = s;
    else
    {
        myCapacity = s;
        node<Data,Priority> *byebye;
        while(mySize > myCapacity)
        {
            byebye = rear;
            rear = rear->higher;
            rear->lower = nullptr;
            delete byebye;
            --mySize;
        };
    }
}

template<typename Data, typename Priority>
void priorityQueue<Data,Priority>::copy(const priorityQueue<Data,Priority> &other)
{

    myCapacity = other.myCapacity;
    mySize = other.mySize;
    rear = nullptr;
    if(!other.front)
        front = nullptr;
    else
    {
        front = rear = new node<Data,Priority>(*other.front);
        for(node<Data,Priority> *next = front->lower; next; next = next->lower)
        {
            rear->lower = new node<Data,Priority>(*next);
            next->higher = rear;
            rear = rear->lower;
        }
    }
}

template<typename Data, typename Priority>
void priorityQueue<Data,Priority>::deleteAllNodes()
{
    node<Data, Priority> *bye;
    while(front)
    {
        bye = front;
        front = front->lower;
        delete bye;
    }
    front = rear = nullptr;
    mySize = 0;
    myCapacity = 0;
}


template<typename D, typename P>
std::ostream& operator<<(std::ostream &out, const priorityQueue<D,P> &pQueue)
{
    if(&out != &std::cout)
        out << "PriorityQueue capacity: " << pQueue.myCapacity << std::endl;
    for(node<D,P> *output = pQueue.front; output; output = output->lower)
        out<<*output;
    return out;
}

template<typename D, typename P>
std::istream& operator>>(std::istream &in, priorityQueue<D,P> &pQueue)
{
    pQueue.deleteAllNodes();
    node<D,P> input;
    if(&in != &std::cin) {
        std::string line("");
        std::getline(in, line, ':');
    } else
        std::cout << "Enter size: ";
    in >> pQueue.myCapacity;
    while(!pQueue.full() && in>>input)
        pQueue.enqueue(input.data,input.priority);
    return in;
}

#endif // PRIORITYQUEUE_H

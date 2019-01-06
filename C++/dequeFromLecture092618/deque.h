#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include <fstream>
#include "node.h"

enum DEQUE_ERRORS {DEQUE_EMPTY, DEQUE_FULL, DEQUE_BAD_SIZE};
enum DEQUE_DIRECTION {DEQUE_FRONT, DEQUE_REAR};

template<typename Data>
class deque
{
    public:
        deque(size_t c = 10);
        ~deque();
        deque(const deque<Data> &other);
        deque<Data>& operator=(const deque<Data> &other);

        bool empty() const;
        bool full() const;
        size_t size() const;
        size_t capacity() const;
        void resize(size_t c = 10);

        Data dequeue(DEQUE_DIRECTION  d = DEQUE_FRONT);
        void enqueue(const Data &d, DEQUE_DIRECTION dir = DEQUE_REAR);
        Data peek(DEQUE_DIRECTION  d = DEQUE_FRONT);

        template<typename D>
        friend
        std::ostream& operator<<(std::ostream& out, const deque<D> &dq);

        template<typename D>
        friend
        std::istream& operator>>(std::istream& in, deque<D> &dq);

    private:
        node<Data> *front,*rear;
        unsigned int mySize, myCapacity;

        void copy(const deque<Data> &other);
        void deleteAllNodes();
};

template<typename Data>
deque<Data>::deque(size_t c)
{
    myCapacity = c;
    mySize = 0;
    front = rear = nullptr;
}

template<typename Data>
deque<Data>::~deque()
{
    deleteAllNodes();
}

template<typename Data>
deque<Data>::deque(const deque<Data> &other)
{
    copy(other);
}

template<typename Data>
deque<Data>& deque<Data>::operator=(const deque<Data> &other)
{
    if(this != &other)
    {
        deleteAllNodes();
        copy(other);
    }
    return *this;
}

template<typename Data>
Data deque<Data>::peek(DEQUE_DIRECTION d)
{
    if(empty())
        throw DEQUE_EMPTY;
    return d ? rear->data : front->data;
}

template<typename Data>
bool deque<Data>::empty() const
{
    return !mySize;
}

template<typename Data>
bool deque<Data>::full() const
{
    return mySize == myCapacity;
}

template<typename Data>
Data deque<Data>::dequeue(DEQUE_DIRECTION d)
{
    Data myData;
    if(empty())
        throw DEQUE_EMPTY;
    --mySize;
    myData = (d ? rear : front)->data;
    if(!mySize) {
        delete front;
        front = rear = nullptr;
    } else {
        if(d) {
            rear = rear->higher;
            delete rear->lower;
            rear->lower = nullptr;
        } else {
            front = front->lower;
            delete front->higher;
            front->higher = nullptr;
        }
    }
    return myData;
}

template<typename Data>
void deque<Data>::enqueue(const Data &data, DEQUE_DIRECTION dir)
{
    if(full())
        throw DEQUE_FULL;
    node<Data> *newNode = new node<Data>(data);
    if(!mySize)
        front = rear = newNode;
    else {
        if(dir)
            rear->lower = newNode,
            newNode->higher = rear,
            rear = rear->lower;
        else
            front->higher = newNode,
            newNode->lower = front,
            front = front->higher;
    }
    ++mySize;
}


template<typename Data>
size_t deque<Data>::size() const
{
    return mySize;
}

template<typename Data>
size_t deque<Data>::capacity() const
{
    return myCapacity;
}

template<typename Data>
void deque<Data>::resize(size_t s)
{
    if(s < 1)
        throw DEQUE_BAD_SIZE;   
    if(s < myCapacity)
    {
        node<Data> *byebye;
        while(mySize > s)
        {
            byebye = rear;
            rear = rear->higher;
            rear->lower = nullptr;
            delete byebye;
            --mySize;
        }
    }
    myCapacity = s;
}

template<typename Data>
void deque<Data>::copy(const deque<Data> &other)
{
    myCapacity = other.myCapacity;
    mySize = other.mySize;
    front = rear = nullptr;
    if(other.front)
    {
        front = rear = new node<Data>(*(other.front));
        for(node<Data> *next = other.front->lower; next; next = next->lower)
        {
            rear->lower = new node<Data>(*next);
            rear->lower->higher = rear;
            rear = rear->lower;
        }
    }
}

template<typename Data>
void deque<Data>::deleteAllNodes()
{
    node<Data> *bye;
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


template<typename D>
std::ostream& operator<<(std::ostream &out, const deque<D> &dq)
{
    if(&out != &std::cout)
        out << "Deque capacity: " << dq.myCapacity << std::endl;
    for(node<D> *output = dq.front; output; output = output->lower)
        out<<*output;
    return out;
}

template<typename D>
std::istream& operator>>(std::istream &in, deque<D> &dq)
{
    node<D> input;
    if(&in != &std::cin) {
        std::string line("");
        std::getline(in, line, ':');
    } else
        std::cout << "Enter size: ";
    in >> dq.myCapacity;
    while(!dq.full() && in>>input)
        dq.enqueue(input.data);
    return in;
}

template<>
std::istream& operator>>(std::istream &in, deque<std::string> &dq)
{
    std::string line("");
    if(&in != &std::cin) {
        std::getline(in, line, ':');
    } else
        std::cout << "Enter size: ";
    in >> dq.myCapacity;
    in.ignore(32767, '\n');
    while(!dq.full()) {
        if(&in == &std::cin)
            std::cout << "Data: ";
        std::getline(in, line);
        if(line.empty())
            break;
        line = line.substr(0, line.find_last_of('\007'));
        dq.enqueue(line);
    }
    return in;
}
#endif // DEQUE_H

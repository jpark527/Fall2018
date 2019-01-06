#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>


template<typename Data, typename Priority>
struct node
{
    Data data;
    Priority priority;
    node<Data, Priority> *higher, *lower;

    node(Data d = Data(), Priority p = Priority());
    ~node();
    node(const node<Data,Priority> &other);
    node<Data, Priority>& operator=(const node<Data, Priority> &other);

    template<typename D, typename P>
    friend
    std::ostream& operator<<( std::ostream &out, const node<D,P> &n);

    template<typename D, typename P>
    friend
    std::istream& operator>>( std::istream &in, node<D,P> &n);

    template<typename D, typename P>
    friend
    bool operator>(const node<D,P> &x, const node<D,P> &y);

    template<typename D, typename P>
    friend
    bool operator<=(const node<D,P> &x, const node<D,P> &y);


};

template<typename Data, typename Priority>
node<Data, Priority>::node(Data d , Priority p)
{
    data = d;
    priority = p;
    higher = lower = nullptr;
}

template<typename Data, typename Priority>
node<Data, Priority>::~node()
{
    data = Data();
    priority = Priority();
    higher = lower = nullptr;
}

template<typename Data, typename Priority>
node<Data, Priority>::node(const node<Data,Priority> &other)
{
    data = other.data;
    priority = other.priority;
    higher = lower = nullptr;
}

template<typename Data, typename Priority>
node<Data, Priority>& node<Data, Priority>::operator=(const node<Data, Priority> &other)
{
    if(this != &other)
    {
        data = other.data;
        priority = other.priority;
        higher = lower = nullptr;
    }
    return *this;
}

template<typename D, typename P>
std::ostream& operator<<( std::ostream &out, const node<D,P> &n)
{
    if(&out == &std::cout)
        out<<n.data<<" has priority of "<<n.priority<<std::endl;
    else
        out<<n.data<<"\007"<<n.priority<<std::endl;
    return out;
}

template<typename D, typename P>
std::istream& operator>>( std::istream &in, node<D,P> &n)
{
    char junk;
    if(&in == &std::cin)
    {
        std::cout<<"Data: ";
        in>>n.data;
        std::cout<<"Priority: ";
        in>>n.priority;
    }
    else
        in>>n.data>>junk>>n.priority;
    return in;
}

template<>
std::istream& operator>>( std::istream &in, node<std::string,int> &n)
{
    std::string line;
    if(&in == &std::cin)
    {
        in.ignore(32767, '\n');
        std::cout<<"Data: ";
        std::getline(in, n.data);
        std::cout<<"Priority: ";
        in>>n.priority;
    }
    else
    {
        if(in.peek() == '\n')
            in.ignore(32767, '\n');
        std::getline(in, line);
        n.data = line.substr(0, line.find_last_of('\007'));
        n.priority = line[line.length()-1] - 48;
    }
    return in;
}

template<typename D, typename P>
bool operator>(const node<D,P> &x, const node<D,P> &y)
{
    return x.priority > y.priority;
}

template<typename D, typename P>
bool operator<=(const node<D,P> &x, const node<D,P> &y)
{
    return x.priority <= y.priority;
}

#endif // NODE_H

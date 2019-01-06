#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

enum MYSTACK_ERRORS { FULL, EMPTY, BAD_SIZE };

using namespace std;

template<typename T>
struct node
{
    T data;
    node* next;

    node(const T &d);
    ~node();
    node(const node<T> &other);
    node<T>& operator=(const node<T> &other);
};


template<typename T>
node<T>::node(const T &d)
{
    data = d;
    next = NULL;
}

template<typename T>
node<T>::~node()
{
    data = T();
    next = NULL;
}

template<typename T>
node<T>::node(const node<T> &other)
{
    data = other.data;
    next = NULL;
}

template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this != &other)
    {
        data = other.data;
        next = NULL;
    }
    return *this;
}

template<typename T>
class myStack
{
   public:
      myStack(int s = 10);
      ~myStack();
      myStack(const myStack<T> &other);
      myStack<T> operator=(const myStack<T> &other);

      void push(const T &data);
      T pop();
      T peek() const;
      bool full() const;
      bool empty() const;
      int size() const;
      int roomLeft() const;
      void resize(int s);

      myStack<T>& operator<<(const T &data);
      myStack<T>& operator>>(T &data);

      template<typename U>
      friend
      ostream& operator<<(ostream &out, const myStack<U> &stck);

      template<typename U>
      friend
      istream& operator>>(istream &in, myStack<U> &stck);

   private:
      node<T> *tos;
      int mySize, capacity;

      void copy(const myStack<T> &other);
      void nukem(node<T> *top);
};



template<typename T>
myStack<T>::myStack(int s)
{
    if((capacity = s) < 1)
        throw BAD_SIZE;
    tos = NULL;
    mySize = 0;
}

template<typename T>
myStack<T>::~myStack()
{
    nukem(tos);
}

template<typename T>
myStack<T>::myStack(const myStack<T> &other)
{
    copy(other);
}

template<typename T>
myStack<T> myStack<T>::operator=(const myStack<T> &other)
{
    if(this != &other)
    {
        nukem(tos);
        copy(other);
    }
    return *this;
}


template<typename T>
void myStack<T>::push(const T &data)
{
    if(full())
        throw FULL;
    node<T> *newNode = new node<T>(data);
    newNode->next = tos;
    tos = newNode;
    ++mySize;
}

template<typename T>
T myStack<T>::pop()
{
    if(empty())
        throw EMPTY;
    T data = tos->data;
    node<T> *bye = tos;
    tos = tos->next;
    delete bye;
    --mySize;
    return data;
}

template<typename T>
T myStack<T>::peek() const
{
    if(empty())
        throw EMPTY;
    return tos->data;
}

template<typename T>
bool myStack<T>::full() const
{
    return mySize == capacity;
}

template<typename T>
bool myStack<T>::empty() const
{
    return !tos;
}

template<typename T>
int myStack<T>::size() const
{
    return capacity;
}

template<typename T>
int myStack<T>::roomLeft() const
{
    return capacity - mySize;
}

template<typename T>
void myStack<T>::resize(int s)
{
    if(s < 1)
        throw BAD_SIZE;
    if(s < capacity) {
        node<T> *temp;
        for(int i=0; i<capacity - s; ++i) {
            temp = tos;
            tos = tos->next;
            delete temp;
        }
    }
    capacity = s;
}

template<>
void myStack<char*>::resize(int s)
{
    if(s < 1)
        throw BAD_SIZE;
    if(s < capacity) {
        node<char*> *temp;
        for(int i=0; i<capacity - s; ++i) {
            temp = tos;
            tos = tos->next;
            if(temp->data)
                delete[] temp->data;
            delete temp;
        }
    }
    capacity = s;
}


template<typename T>
myStack<T>& myStack<T>::operator<<(const T &data)
{
    push(data);
    return *this;
}

template<typename T>
myStack<T>& myStack<T>::operator>>(T &data)
{
    data = pop();
    return *this;
}


template<typename T>
void myStack<T>::copy(const myStack<T> &other)
{
    node<T> *me, *you;
    nukem(tos);
    tos = NULL;
    mySize = other.mySize;
    capacity = other.capacity;
    if(other.empty())
        return;
    tos = new node<T>(other.tos->data);
    me = tos, you = other.tos;
    while(you)
    {
        me->next = new node<T>(you->next->data);
        me = me->next;
        you = you->next;
    }
}

template<typename T>
void myStack<T>::nukem(node<T> *top)
{
    if(!top)
        return;
    for(node<T> *bye = top; bye; bye = top)
    {
        top = top->next;
        delete bye;
    }
}

template<>
void myStack<char*>::nukem(node<char*> *top)
{
    if(!top)
        return;
    for(node<char*> *bye = top; bye; bye = top)
    {
        top = top->next;
        if(bye->data)
            delete[] bye->data;
        delete bye;
    }
}

template<typename U>
ostream& operator<<(ostream &out, const myStack<U> &stck)
{
    node<U> *tos = stck.tos;
    if(&out != &cout)
    {
        out<<"Stack size: "<<stck.mySize<<endl
           <<"Stack capacity: "<<stck.capacity<<endl;
    }
    while(tos)
    {
        out<<tos->data<<endl;
        tos = tos->next;
    }
    return out;
}


template<typename U>
istream& operator>>(istream &in, myStack<U> &stck)
{
    string line;
    U data;
    stck.nukem(stck.tos);
    if(&in == &cin)
    {
        cout<<"Stack size: ";
        in>>stck.capacity;
        cout<<"Enter data: "<<endl;
        while(!stck.full() && in>>data)
            stck<<data;
    }
    else
    {
        myStack<U> temp;
        getline(in, line, ':');
        in>>stck.mySize;
        getline(in, line, ':');
        in>>stck.capacity;
        for(unsigned int i = 0; i < stck.mySize; ++i)
        {
            in>>data;
            temp<<data;
        }
        for(unsigned int i = 0; i < stck.mySize; ++i)
            stck<<temp.pop();
    }
    return in;
}

template<>
istream& operator>>(istream &in, myStack<string> &stck)
{
    string line;
    string data;
    stck.nukem(stck.tos);
    if(&in == &cin)
    {
        cout<<"Stack size: ";
        in>>stck.capacity;
        cout<<"Enter data: "<<endl;
        in.ignore(32767, '\n');
        while(!stck.full()) {
            getline(in, data);
            if(data.empty())
                break;
            stck<<data;
        }
    }
    else
    {
        myStack<string> temp;
        getline(in, line, ':');
        in>>stck.mySize;
        getline(in, line, ':');
        in>>stck.capacity;
        for(unsigned int i = 0; i < stck.mySize; ++i)
        {
            in>>data;
            temp<<data;
        }
        for(unsigned int i = 0; i < stck.mySize; ++i)
            stck<<temp.pop();
    }
    return in;
}

template<>
istream& operator>>(istream &in, myStack<char*> &stck)
{
    string line;
    stck.nukem(stck.tos);
    if(&in == &cin)
    {
        cout<<"Stack size: ";
        in>>stck.capacity;
        cout<<"Enter data: "<<endl;
        in.ignore(32767, '\n');
        while(!stck.full()) {
            getline(in, line);
            if(line.empty())
                break;
            char* data = new char[line.length()];
            strcpy(data, line.c_str());
            stck<<data;
        }
    }
    else
    {
        myStack<char*> temp;
        getline(in, line, ':');
        in>>stck.mySize;
        getline(in, line, ':');
        in>>stck.capacity;
        for(unsigned int i = 0; i < stck.mySize; ++i)
        {
            in.ignore(32767, '\n');
            getline(in, line);
            char* data = new char[line.length()];
            strcpy(data, line.c_str());
            temp<<data;
        }
        for(unsigned int i = 0; i < stck.mySize; ++i)
            stck<<temp.pop();
    }
    return in;
}

#endif // STACK_H

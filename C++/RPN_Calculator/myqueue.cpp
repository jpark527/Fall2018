#include "myqueue.h"

template<typename T>
myQueue<T>::myQueue(size_t s) {
    if(s + 1 < 3)
        throw BAD_SIZE;
    que = new T[(capacity = s) + 1];
    for(size_t i=0; i<capacity+1; ++i)
        que[i] = T();
    mySize = head = tail = 0;
}

template<typename T>
myQueue<T>::~myQueue() {
    nukem();
    capacity = mySize = head = tail = 0;
}

template<>
myQueue<char*>::~myQueue() {
    for(size_t i = 0; i < capacity+1; ++i)
        if(que[i] && que[i][0])
            delete[] que[i];
    delete [] que;
    que = NULL;
    capacity = mySize = head = tail = 0;
}

template<typename T>
myQueue<T>::myQueue(const myQueue<T> &other) {
    nukem();
    copy(other);
}

template<typename T>
myQueue<T>& myQueue<T>::operator=(const myQueue<T> &other) {
    if(this != &other) {
        nukem();
        copy(other);
    }
    return *this;
}

template<typename T>
bool myQueue<T>::full() const {
    return mySize == capacity;
}

template<typename T>
bool myQueue<T>::empty() const {
    return !mySize;
}

template<typename T>
T myQueue<T>::peek() const {
    return que[head];
}

template<typename T>
void myQueue<T>::clear() {
    tail = head = mySize = 0;
}

template<typename T>
size_t myQueue<T>::size() const {
    return mySize;
}

template<typename T>
size_t myQueue<T>::getCapacity() const {
    return capacity;
}

template<typename T>
void myQueue<T>::resize(size_t s) {
    bool over = (s >= capacity);
    size_t j = 0, endingCondition = over ? head + mySize : s + head;
    T *temp = new T[s + 1];
    for(size_t i = head; i < endingCondition; ++i, ++j) {
        temp[j] = que[i%(capacity+1)];
        que[i%(capacity+1)] = T();
    }
    delete [] que;
    que = temp;
    mySize = tail = over ? mySize : s;
    head = 0;
    capacity = s;
}

template<>
void myQueue<char*>::resize(size_t s) {
    bool over = (s >= capacity);
    size_t j = 0, endingCondition = over ? head + mySize : s + head;
    char **temp = new char*[s + 1];
    for(size_t i=0; i<s+1; ++i)
        temp[i] = nullptr;
    for(size_t i = head; i < endingCondition; ++i, ++j) {
        size_t len = strlen(que[i%(capacity+1)]);
        temp[j] = new char[len];
        strncpy(temp[j], que[i%(capacity+1)], len);
    }
    for(size_t i = 0; i < capacity+1; ++i)
        if(que[i] && que[i][0])
            delete[] que[i];
    delete [] que;
    que = temp;
    mySize = tail = over ? mySize : s;
    head = 0;
    capacity = s;
}

template<typename T>
void myQueue<T>::enqueue(const T &d) {
    if(full())
        throw FULL;
    que[tail] = d;
    tail = (tail+1) % (capacity+1);
    ++mySize;
}

template<typename T>
void myQueue<T>::dequeue(T &d) {
    if(empty())
        throw EMPTY;
    d = que[head];
    head = (head+1) % (capacity+1);
    --mySize;
}

template<typename T>
myQueue<T>& myQueue<T>::operator<<(const T &d) {
    enqueue(d);
    return *this;
}

template<typename T>
myQueue<T>& myQueue<T>::operator>>(T &d) {
    dequeue(d);
    return *this;
}

template<typename T>
void myQueue<T>::nukem() {
    for(size_t i = 0; i < capacity+1; ++i)
        que[i] = T();
    delete [] que;
    que = NULL;
}

template<typename T>
void myQueue<T>::copy(const myQueue<T> &other) {
    mySize = other.mySize;
    capacity = other.capacity;
    head = other.head;
    tail = other.tail;
    que = new T[capacity + 1];
    for(size_t i =  0; i < capacity + 1; ++i)
        que[i] = other.que[i];
}

template<>
void myQueue<char*>::copy(const myQueue<char*> &other) {
    mySize = other.mySize;
    capacity = other.capacity;
    head = other.head;
    tail = other.tail;
    que = new char*[capacity + 1];
    for(size_t i =  0; i < capacity + 1; ++i) {
        que[i] = new char[strlen(other.que[i])];
        strncpy(que[i], other.que[i], strlen(other.que[i]));
    }
}

template<typename  U>
ostream& operator<<(ostream& out, const myQueue<U> &q) {
    if(&out != &cout) {
        out << "Queue capacity: " << q.capacity << endl
            << "Queue size: " << q.mySize << endl;
    }
    for(size_t i=q.head; i<q.mySize+q.head; ++i)
        out << q.que[i%(q.capacity+1)] << endl;
    return out;
}

template<typename U>
istream& operator>>(istream& in, myQueue<U> &q) {
    q.nukem();
    q.capacity = q.mySize = q.head = q.tail = 0;
    if(&in != &cin) {
        string line;
        if(in.peek() == '\n')
            in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> q.capacity;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> q.mySize;
        q.que = new U[q.capacity+1];
        for(size_t i=0; i<q.mySize; ++i, ++q.tail)
            in >> q.que[i];
    } else {
        cout << "Enter size: ";
        in >> q.capacity;
        cout << "Enter data: " << endl;
        q.que = new U[q.capacity+1];
        U data;
        while(!q.full() && in >> data)
            q << data;
    }
    return in;
}

template<>
istream& operator>>(istream& in, myQueue<string> &q) {
    q.nukem();
    q.capacity = q.mySize = q.head = q.tail = 0;
    bool isCin = (&in == &cin);
    if(!isCin) {
        string line;
        if(in.peek() == '\n')
            in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> q.capacity;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> q.mySize;
    } else {
        cout << "Enter size: ";
        in >> q.capacity;
        cout << "Enter data: " << endl;
    }
    in.ignore(32767, '\n');
    q.que = new string[q.capacity+1];
    string data;
    size_t len = q.mySize;
    q.mySize = 0;
    do {
        getline(in, data);
        if(data.empty() && isCin)
            break;
        q << data;
    } while(!q.full() && len != q.mySize);
    return in;
}

template<>
istream& operator>>(istream& in, myQueue<char*> &q) {
    string line;
    for(size_t i = 0; i < q.capacity+1; ++i)
        if(q.que[i] && q.que[i][0])
            delete[] q.que[i];
    delete [] q.que;
    q.que = NULL;
    q.capacity = q.mySize = q.head = q.tail = 0;
    bool isCin = (&in == &cin);
    if(!isCin) {
        if(in.peek() == '\n')
            in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> q.capacity;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> q.mySize;
    } else {
        cout << "Enter size: ";
        in >> q.capacity;
        cout << "Enter data: " << endl;
    }
    in.ignore(32767, '\n');
    q.que = new char*[q.capacity+1];
    for(size_t i=0; i<q.capacity+1; ++i)
        q.que[i] = nullptr;
    size_t len = q.mySize;
    q.mySize = 0;
    do {
        getline(in, line);
        if(line.empty() && isCin)
            break;
        q.que[q.tail] = new char[strlen(line.c_str())];
        strncpy(q.que[q.tail], line.c_str(), strlen(line.c_str()));
        q.tail = (q.tail+1) % (q.capacity+1);
        ++q.mySize;
    } while(!q.full() && len != q.mySize);

    return in;
}

template class myQueue<char>;
template class myQueue<myPair>;

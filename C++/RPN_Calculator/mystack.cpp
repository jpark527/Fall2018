#include "mystack.h"

// Private
template <typename T>
void myStack<T>::eraseAll() {
    startPosition = curPosition = capacity = 0;
    if(arr) {
        for(size_t i=0; i<size(); ++i)
            arr[i] = T();
        delete[] arr;
    }
}

template <typename T>
void myStack<T>::copy(const myStack<T> &other) {
    startPosition = other.startPosition;
    curPosition = other.curPosition;
    arr = new T[capacity = other.capacity];
    for(size_t i=startPosition; i<curPosition; ++i)
        arr[i] = other.arr[i];
}

template <>
void myStack<char*>::copy(const myStack<char*> &other) {
    if(!other.size())
        return;
    startPosition = other.startPosition;
    curPosition = other.curPosition;
    arr = new char*[capacity = other.capacity];
    for(size_t i=0; i<capacity; ++i)
        arr[i] = nullptr;
    for(size_t i=startPosition; i<curPosition; ++i) {
        arr[i] = new char[strlen(other.arr[i])];
        strcpy(arr[i], other.arr[i]);
    }
}

// Public
template <typename T>
myStack<T>::myStack(size_t size) {
    if(size < 2)
        throw BAD_SIZE;
    arr = new T[capacity=size];
    for(size_t i=0; i<capacity; ++i)
        arr[i] = T();
    startPosition = curPosition = 0;
}

template <typename T>
myStack<T>::myStack(const myStack<T> &rhs) {
    eraseAll();
    copy(rhs);
}

template <>
myStack<char*>::myStack(const myStack<char*> &rhs) {
    for(size_t i=0; i<capacity; ++i)
        if(arr[i] && !arr[i][0])
            delete arr[i];
    eraseAll();
    copy(rhs);
}

template <typename T>
myStack<T>::~myStack() {
    eraseAll();
}

template <>
myStack<char*>::~myStack() {
    for(size_t i=0; i<capacity; ++i)
        if(arr[i] && !arr[i][0])
            delete arr[i];
    eraseAll();
}

template <typename T>
myStack<T>& myStack<T>::operator=(const myStack<T> &rhs) {
    if(this!=&rhs) {
        eraseAll();
        copy(rhs);
    }
    return *this;
}

template <>
myStack<char*>& myStack<char*>::operator=(const myStack<char*> &rhs) {
    if(this!=&rhs) {
        for(size_t i=0; i<capacity; ++i)
            if(arr[i] && !arr[i][0])
                delete arr[i];
        eraseAll();
        copy(rhs);
    }
    return *this;
}

template <typename T>
void myStack<T>::push(const T &data) {
    if(full())
        throw FULL;
    arr[curPosition++] = data;
}

template <>
void myStack<char*>::push(const char* &data) {
    if(full())
        throw FULL;
    char* newData = new char[strlen(data)];
    strcpy(newData, data);
    if(arr[curPosition+1] && !arr[curPosition+1][0])
        delete[] arr[curPosition+1];
    arr[curPosition++] = newData;
}

template <typename T>
T myStack<T>::pop() {
    if(empty())
        throw EMPTY;
    return arr[--curPosition];
}

template <typename T>
T myStack<T>::peek() const {
    if(empty())
        throw EMPTY;
    return arr[curPosition-1];
}

template <typename T>
bool myStack<T>::full() const {
    return curPosition >= capacity;
}

template <typename T>
bool myStack<T>::empty() const {
    return curPosition == startPosition;
}

template <typename T>
size_t myStack<T>::size() const {
    return curPosition - startPosition;
}

template <typename T>
size_t myStack<T>::roomLeft() const {
    return capacity - curPosition;
}

template <typename T>
void myStack<T>::resize(size_t size) {
    if(size < 2)
        throw BAD_SIZE;
    T* temp = new T[size];

    size_t newStartPos = size > curPosition-startPosition ? 0 : curPosition-size,
           index = 0;
    for(size_t i=newStartPos; i<curPosition; ++i)
        temp[index++] = arr[i];
    eraseAll();
    arr = temp;
    capacity = size;
    curPosition = index;
}

template <>
void myStack<char*>::resize(size_t size) {
    if(size < 2)
        throw BAD_SIZE;
    char** temp = new char*[size];
    for(size_t i=0; i<size; ++i)
        temp[i] = nullptr;
    size_t newStartPos = size > curPosition-startPosition ? 0 : curPosition-size,
           index = 0;
    for(size_t i=newStartPos; i<curPosition; ++i) {
        temp[index] = new char[strlen(arr[i])];
        strcpy(temp[index], arr[i]);
        ++index;
    }
    for(size_t i=0; i<capacity; ++i)
        if(arr[i] && !arr[i][0])
            delete arr[i];
    eraseAll();
    arr = temp;
    capacity = size;
    curPosition = index;
}

template <typename T>
void myStack<T>::clear() {
    startPosition = curPosition = 0;
}

template <typename T>
myStack<T>& myStack<T>::operator<<(const T &data) {
    push(data);
    return *this;
}

template <typename T>
myStack<T>& myStack<T>::operator>>(T &data) {
    data = pop();
    return *this;
}

template <typename U>
istream& operator>>(istream& in, myStack<U> &stck) {
    U data;
    string line;
    stck.eraseAll();
    if(&in==&cin) {
        cout << "Enter size: ";
        in >> stck.capacity;
        cout << "Enter data:" << endl;
    } else {
        if(in.peek()=='\n')
            in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.capacity;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.startPosition;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.curPosition;
    }
    in.ignore(32767, '\n');
    stck.arr = new U[stck.capacity];
    size_t len = stck.curPosition - stck.startPosition;
    stck.clear();
    do {
        in >> data;
        stck << data;
    } while(!stck.full() && len != stck.size());

    return in;
}

template <>
istream& operator>>(istream& in, myStack<string> &stck) {
    string line;
    stck.eraseAll();
    bool isCin = (&in==&cin);
    if(isCin) {
        cout << "Enter size: ";
        in >> stck.capacity;
        cout << "Enter data:" << endl;
    } else {
        if(in.peek()=='\n')
            in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.capacity;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.startPosition;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.curPosition;
    }
    stck.arr = new string[stck.capacity];
    size_t len = stck.curPosition - stck.startPosition;
    stck.clear();
    in.ignore(32767, '\n');
    do {
        getline(in, line);
        if(line.empty() && isCin)
            break;
        stck << line;
    } while(!stck.full() && len != stck.size());

    return in;
}

template <>
istream& operator>>(istream& in, myStack<char*> &stck) {
    string line;
    stck.eraseAll();
    bool isCin = (&in==&cin);
    if(isCin) {
        cout << "Enter size: ";
        in >> stck.capacity;
        cout << "Enter data:" << endl;
    } else {
        if(in.peek()=='\n')
            in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.capacity;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.startPosition;
        in.ignore(32767, '\n');
        getline(in, line, ':');
        in >> stck.curPosition;
    }
    stck.arr = new char*[stck.capacity];
    for(size_t i=0; i<stck.capacity; ++i)
        stck.arr[i] = nullptr;
    size_t len = stck.curPosition - stck.startPosition;
    stck.clear();
    in.ignore(32767, '\n');
    do {
        getline(in, line);
        if(line.empty() && isCin)
            break;
        char* data = new char[line.length()];
        strcpy(data, line.c_str());
        stck.arr[stck.curPosition++] = data;
    } while(!stck.full() && len != stck.size());

    return in;
}

template <typename U>
ostream& operator<<(ostream& out, const myStack<U> &stck) {
    if(&out!=&cout) {
        out << "Stack capacity: " << stck.capacity << endl
            << "Stack startPosition: " << stck.startPosition << endl
            << "Stack currentPosition: " << stck.curPosition << endl;
        for(size_t i=stck.startPosition; i<stck.curPosition; ++i) {
            out << stck.arr[i] << endl;
        }
    } else {
        int index = stck.curPosition;
        do {
            out << stck.arr[--index] << endl;
        } while(index);
    }
    return out;
}

template class myStack<char>;
template class myStack<double>;

#ifndef MYSWITCH_H
#define MYSWITCH_H
#include <iostream>
#include <cstdarg>
#include <vector>
#include <map>

typedef void (*fptr)();

enum ERROR {NO_SUCH_ELEMENT};

using namespace std;

template <typename K, typename V>
class mySwitch {
    K key;
    map<K, V> data;
    void copy(const mySwitch& rhs);
    void setData(vector<K> &kData, vector<V> &vData);
    void setKey(const vector<K> &kData);
public:
    mySwitch(const char* fmt...);
    mySwitch(const mySwitch &rhs);
    ~mySwitch();
    mySwitch& operator=(const mySwitch& rhs);
    bool operator()(K& k);
    V getValue();
};

// public
template <typename K, typename V>
mySwitch<K, V>::mySwitch(const char* fmt...) {
    va_list args;
    va_start(args, fmt);
    vector<K> kData;
    vector<V> vData;
    while (*fmt != '\0') {
        if(*fmt == 'k')
            kData.push_back(va_arg(args, K));
        if(*fmt == 'v')
            vData.push_back(va_arg(args, V));
        ++fmt;
    }
    va_end(args);

    setKey(kData);
    setData(kData, vData);
}

template <typename K, typename V>
mySwitch<K, V>::mySwitch(const mySwitch<K, V> &rhs) {
    copy(rhs);
}

template <typename K, typename V>
mySwitch<K, V>::~mySwitch() {
    data.clear();
}

template <typename K, typename V>
mySwitch<K, V>& mySwitch<K, V>::operator=(const mySwitch<K, V>& rhs) {
    if(this != &rhs)
        copy(rhs);
    return *this;
}

template <typename K, typename V>
bool mySwitch<K, V>::operator()(K& k) {
    return data.count(k);
}

template <typename K, typename V>
V mySwitch<K, V>::getValue() {
    if(this->operator ()(key))
        return data[key];
    throw NO_SUCH_ELEMENT;
}

// private
template <typename K, typename V>
void mySwitch<K, V>::copy(const mySwitch<K, V>& rhs) {
    key = rhs.key;
    data = rhs.data;
}

template <typename K, typename V>
void mySwitch<K, V>::setData(vector<K> &kData, vector<V> &vData) {
    size_t size = kData.size()-1 > vData.size() ? vData.size() : kData.size()-1;
    for(size_t i=0; i<size; ++i)
        data[kData[i]] = vData[i];
}

template <typename K, typename V>
void mySwitch<K, V>::setKey(const vector<K> &kData) {
    key = kData[kData.size()-1];
}

#endif // MYSWITCH_H

#ifndef MYSWITCH_H
#define MYSWITCH_H
#include <map>

using namespace std;

typedef void (*fptr)();

enum ERROR {NO_SUCH_ELEMENT};

template<typename K, typename V>
class mySwitch {
    K key;
    map<K, V> condition;
    void copy(const mySwitch<K, V>& rhs);
public:
    mySwitch(const map<K, V> &condition, K key);
    mySwitch(const mySwitch<K, V> &rhs);
    ~mySwitch();
    mySwitch& operator=(const mySwitch<K, V>& rhs);
    bool operator()(K &k);
    V getValue();
};

// public
template<typename K, typename V>
mySwitch<K, V>::mySwitch(const map<K, V> &condition, K key) {
    this->condition=condition;
    this->key=key;
}

template<typename K, typename V>
mySwitch<K, V>::mySwitch(const mySwitch<K, V>& rhs) {
    copy(rhs);
}

template<typename K, typename V>
mySwitch<K, V>::~mySwitch() {
    condition.clear();
}

template<typename K, typename V>
mySwitch<K, V>& mySwitch<K, V>::operator=(const mySwitch<K, V>& rhs) {
    copy(rhs);
    return *this;
}

template<typename K, typename V>
bool mySwitch<K, V>::operator()(K &k) {
    return condition.count(k);
}

template<typename K, typename V>
V mySwitch<K, V>::getValue() {
    if(this->operator ()(key))
        return condition[key];
    throw NO_SUCH_ELEMENT;
}

// private
template<typename K, typename V>
void mySwitch<K, V>::copy(const mySwitch<K, V> &rhs) {
    if(this!=&rhs) {
        condition = rhs.condition;
        key = rhs.key;
    }
}

#endif // MYSWITCH_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "heapsortone.h"
#include "heapsorttwo.h"

using namespace std;

template <typename T>
void addData(vector<T> &v);

template <typename T>
void insertDataToSort(heapSortOne<T> &h1, heapSortTwo<T> &h2, const vector<T> &v);

template <typename T>
void goHeapSort(heapSortOne<T> &h1, heapSortTwo<T> &h2);

void setType(char &type);
void run(char type);
bool again();

int main() {
    char type = '\0';
    do {
        setType(type);
        run(type);
    } while(again());

    return 0;
}

template <typename T>
void addData(vector<T> &v) {
    int len;
    T data;
    cout << "Enter the number of elements to add: ";
    cin >> len;
    for(int i=0; i<len; ++i) {
        cin >> data;
        v.push_back(data);
    }
}

template <typename T>
void insertDataToSort(heapSortOne<T> &h1, heapSortTwo<T> &h2, const vector<T> &v) {
    char order;
    while(1) {
        cout << "Assending or Descending?[A/D] ";
        cin >> order;
        order = tolower(order);
        if(order=='a') {
            h1 << v;
            h2 << v;
            h2.direction() = MIN_SORT2;
            break;
        } else if(order=='d') {
            h1 >> v;
            h2 << v;
            h2.direction() = MAX_SORT2;
            break;
        }
    }
}

template <typename T>
void goHeapSort(heapSortOne<T> &h1, heapSortTwo<T> &h2) {
    vector<T> v, vSorted;
    vector<int> vSortIndex;
    addData<T>(v);
    insertDataToSort<T>(h1, h2, v);
    h1.getData(vSorted);
    h2 >> vSortIndex;
    cout << "----------------------------\nOriginal Data:" << endl;
    for(size_t i=0; i<v.size(); ++i)
        cout << v[i] << endl;
    cout << "----------------------------\nSorted Data:" << endl;
    for(size_t i=0; i<vSorted.size(); ++i)
        cout << vSorted[i] << endl;
    cout << "----------------------------\nIndices in order to be sorted:" << endl;
    for(size_t i=0; i<vSortIndex.size(); ++i)
        cout << vSortIndex[i] << endl;
}

void setType(char &type) {
    while(1) {
        cout << "Enter 'i' for int, 'c' for char, and 'd' for double: ";
        cin >> type;
        type = tolower(type);
        if(type=='i' || type=='c' || type=='d')
            break;
    }
}

void run(char type) {
    heapSortOne<int> h1i;
    heapSortTwo<int> h2i;
    heapSortOne<char> h1c;
    heapSortTwo<char> h2c;
    heapSortOne<double> h1d;
    heapSortTwo<double> h2d;
    switch(type) {
        case 'i':
            goHeapSort<int>(h1i, h2i);
            break;
        case 'd':
            goHeapSort<double>(h1d, h2d);
            break;
        default:
            goHeapSort<char>(h1c, h2c);
    }
}

bool again() {
    char ans;
    cout << "Again?[Y/N] ";
    cin >> ans;
    ans = tolower(ans);
    return ans == 'y';
}


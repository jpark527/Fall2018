#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

template <typename T>
void printMyStack(myStack<T> &stck);
void myStackTest();
bool again();

int main() {
    do {
        myStackTest();
    } while(again());
    return 0;
}

template <typename T>
void printMyStack(myStack<T> &stck) {
    char ans;
    cin >> stck;
    cout << "myStack.peek() = " << stck.peek() << endl
         << "myStack.size() = " << stck.size() << endl
         << "myStack.roomLeft() = " << stck.roomLeft() << endl << endl
         << "test resize()? [Y/N] ";
    cin >> ans;
    if(ans=='y' || ans=='Y') {
        int s;
        cout << "Enter new size: ";
        cin >> s;
        stck.resize(s);
    }
    cout << "Poping out all data...\n" << stck << endl;
}

void myStackTest() {
    myStack<int> intStack;
    myStack<double> doubleStack;
    myStack<char> charStack;
    myStack<string> stringStack;
    myStack<char*> cStrStack;
    char type;
    cout << "********************* Function Test ************************\n"
         << "Enter int for 'i', double for 'd', char for 'c', \n      "
            "string for 's', and c_string for 'C': ";
    cin >> type;
    switch(type) {
        case 'i': printMyStack(intStack);
            break;
        case 'd': printMyStack(doubleStack);
            break;
        case 'c': printMyStack(charStack);
            break;
        case 's': printMyStack(stringStack);
            break;
        case 'C': printMyStack(cStrStack);
            break;
        default: cout << "Invalid Input. Please try again." << endl;
    }
}

bool again() {
    char c;
    cout << "Again?[Y/N] ";
    cin >> c;
    return c=='y' || c=='Y';
}

#include <iostream>
#include <string>
#include "arraystack.h"
#include "jstack.h"

using namespace std;

bool getInput(string &data);
bool isPalindrome(const string& data);

void arrayStackDemo();
void JLinkedListDemo();
void palindromeJStackDemo();

template <typename T>
void printArrayStack(ArrayStack<T> &stck);

template <typename T>
void printJLinkedList(JLinkedList<T> &list);

int main() {
    arrayStackDemo();
    JLinkedListDemo();
//    palindromeJStackDemo();
    return 0;
}

bool getInput(string &data) {
    cout << "Enter whatever you think is palindrome: ";
    getline(cin, data);
    return !data.empty();
}

bool isPalindrome(const string& data) {
    int len = data.length() / 2;
    JStack<char> reverse;
    string palindrome("");
    for(int i=0; i<len; ++i) {
        palindrome += data[i];
        reverse << data[i];
    }
    if(data.length()%2)
        palindrome += data[len];
    while(!reverse.empty())
        palindrome += reverse.pop();
    return data == palindrome;
}

void arrayStackDemo() {
    char type;
    ArrayStack<char> charStack;
    ArrayStack<char*> cStrStack;
    ArrayStack<string> stringStack;
    cout << "******************** TESTING ArrayStack *********************\n"
         << "Enter 'c' for charactor, 'C' for cString , and 's' for string: ";
    cin >> type;
    switch(type) {
        case 'c': printArrayStack(charStack);
            break;
        case 'C': printArrayStack(cStrStack);
            break;
        case 's': printArrayStack(stringStack);
            break;
        default : cout << "Input Invalid. Please try again." << endl;
    }
}

template <typename T>
void printArrayStack(ArrayStack<T> &stck) {
    cin >> stck;
    cout << "Size of ArrayStack: " << stck.size() << endl
         << "ArrayStack.peek() = " << stck.peek() << endl
         << "Poping out all data...\n" << stck << endl;
}

void JLinkedListDemo() {
    char type;
    JLinkedList<char> charList;
    JLinkedList<char*> cStrList;
    JLinkedList<string> stringList;
    cout << "******************** TESTING JLinkedList ********************\n"
         << "Enter 'c' for charactor, 'C' for cString , and 's' for string: ";
    cin >> type;
    switch(type) {
    case 'c': printJLinkedList(charList);
        break;
    case 'C': printJLinkedList(cStrList);
        break;
    case 's': printJLinkedList(stringList);
        break;
    default : cout << "Input Invalid. Please try again." << endl;
    }
}

template <typename T>
void printJLinkedList(JLinkedList<T> &list) {
    cin >> list;
    cout << "Size of JLinkedList: " << list.size() << endl
         << "Printing all data...\n"<< list << endl;
}

void palindromeJStackDemo() {
    string word("");
    while(getInput(word)) {
        string check(isPalindrome(word) ? " is palindrome.\n" : " is NOT palindrome.\n");
        cout << word << check;
    }
}

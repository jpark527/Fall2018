#include <iostream>
#include "deque.h"

using namespace std;

template <typename T>
void dequeUp(bool input, bool output, deque<T> &dq);

template <typename T>
void resizeOrDequeue(deque<T> &dq, char &dequeue);

void generateOutput(char type, bool fInput, bool fOutput) ;
void getInput(char &type, string &fileIO);
void dequeDemo();
bool again();

int main() {
    do {
        dequeDemo();
    } while(again());
    return 0;
}

template <typename T>
void dequeUp(bool input, bool output, deque<T> &dq) {
    string path;
    char dequeue;
    if(input || output) {
        cout << "Enter file path: ";
        getline(cin, path);
    }
    if(input) {
        ifstream in(path);
        in >> dq;
        in.close();
    } else
        cin >> dq;
    resizeOrDequeue(dq, dequeue);
    if(output) {
        ofstream out(path);
        out << dq;
        out.close();
    }
    if(dequeue=='y' || dequeue=='Y') {
        int dir;
        cout << "Choose direction(0 for front, 1 for rear): ";
        cin >> dir;
        cout << "Start dequeuing.." << endl;
        T data;
        while(!dq.empty()) {
            data = dq.dequeue(dir ? DEQUE_REAR : DEQUE_FRONT);
            cout << data << endl;
        }
    } else
        cout << "Your deque has " << dq.size() << " items:\n" << dq;
}

template <typename T>
void resizeOrDequeue(deque<T> &dq, char &dequeue) {
    char resize;
    cout << "Do you want to resize?[Y/N] ";
    cin >> resize;
    if(resize=='y' || resize=='Y') {
        size_t s;
        cout << "Enter size: ";
        cin >> s;
        dq.resize(s);
    }
    cout << "Do you want to dequeue?[Y/N] ";
    cin >> dequeue;
}

void generateOutput(char type, bool fInput, bool fOutput) {
    deque<int> intDq;
    deque<double> doubleDq;
    deque<char> charDq;
    deque<string> strDq;
    switch (type) {
        case 'i': dequeUp(fInput, fOutput, intDq);
            break;
        case 'd': dequeUp(fInput, fOutput, doubleDq);
            break;
        case 'c': dequeUp(fInput, fOutput, charDq);
            break;
        case 's': dequeUp(fInput, fOutput, strDq);
            break;
        default: cout << "Input NOT valid. Please try again." << endl;
    }
}

void getInput(char &type, string &fileIO) {
    cout << "Enter type 'i' for int, 'd' for double, "
         << "\n       'c' for char, and 's' for string: ";
    cin >> type;
    cout << "Enter 'i' for getting input from a file, 'o' for outputing to a file,\n"
         << "and any other key to just continue: ";
    cin.ignore(32767,'\n');
    getline(cin, fileIO);
}

void dequeDemo() {
    char type;
    string fileIO("");
    bool fInput, fOutput;
    cout << "\n************************** Deque Demo ******************************\n";
    getInput(type, fileIO);
    fInput = (fileIO.find_first_of('i') < fileIO.length());
    fOutput = (fileIO.find_first_of('o') < fileIO.length());
    generateOutput(type, fInput, fOutput);
}

bool again() {
    string line("");
    cout << "Again?[Y/N] ";
    if(cin.peek()=='\n')
        cin.ignore(32767, '\n');
    getline(cin, line);
    return line[0] == 'y' || line[0] == 'Y';
}

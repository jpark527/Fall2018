#include <iostream>
#include "myqueue.h"

using namespace std;

template <typename T>
void queueUp(const bool &input, const bool &output, myQueue<T> &que);

template <typename T>
void resizeQue(myQueue<T> &que);

void choose(const bool &input, const bool &output, myQueue<int> &intQ, myQueue<double> &doubleQ,
            myQueue<char> &charQ, myQueue<string> &strQ, myQueue<char*> &cStrQ, char type);
void getInput(char &type, string &line);
void myQueueDemo();
bool again();

int main() {
    do {
        myQueueDemo();
    } while(again());
    return 0;
}

template <typename T>
void queueUp(const bool &input, const bool &output, myQueue<T> &que) {
    string path;
    if(input || output) {
        cout << "Enter file path: ";
        getline(cin, path);
    }
    if(input) {
        ifstream in(path);
        in >> que;
        in.close();
    } else
        cin >> que;
    resizeQue(que);
    cout << "Your Queue has " << que.size() << " items:\n" << que;
    if(output) {
        ofstream out(path);
        out << que;
        out.close();
    }
}

template <typename T>
void resizeQue(myQueue<T> &que) {
    char resize;
    cout << "Do you want to resize?[Y/N] ";
    cin >> resize;
    if(resize=='y' || resize=='Y') {
        size_t s;
        cout << "Enter size: ";
        cin >> s;
        que.resize(s);
    }
}

void choose(const bool &input, const bool &output, myQueue<int> &intQ, myQueue<double> &doubleQ,
            myQueue<char> &charQ, myQueue<string> &strQ, myQueue<char*> &cStrQ, char type) {
    switch (type) {
    case 'i': queueUp(input, output, intQ);
        break;
    case 'd': queueUp(input, output, doubleQ);
        break;
    case 'c': queueUp(input, output, charQ);
        break;
    case 's': queueUp(input, output, strQ);
        break;
    case 'C': queueUp(input, output, cStrQ);
        break;
    default: cout << "Invalid Input!" << endl;
    }
}

void getInput(char &type, string &line) {
    cout << "Enter 'i' for int, 'd' for double, 'c' for char,\n"
         << "'s' for string, and 'C' for c_string: ";
    cin >> type;
    cout << "Enter 'i' for getting input from a file, 'o' for outputing to a file,\n"
         << "and any other key to just continue: ";
    cin.ignore(32767, '\n');
    getline(cin, line);
}

void myQueueDemo() {
    char type;
    string line;
    bool input, output;
    myQueue<int> intQ;
    myQueue<double> doubleQ;
    myQueue<char> charQ;
    myQueue<string> strQ;
    myQueue<char*> cStrQ;
    cout << "\n************************** myQueue Demo ******************************\n";
    getInput(type, line);
    input = (line.find_first_of('i') < line.length());
    output = (line.find_first_of('o') < line.length());
    choose(input, output, intQ, doubleQ, charQ, strQ, cStrQ, type);
}

bool again() {
    string line;
    cout << "Again?[Y/N] ";
    cin.ignore(32767, '\n');
    getline(cin, line);
    return line[0] == 'y' || line[0] == 'Y';
}

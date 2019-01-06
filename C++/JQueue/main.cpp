#include <iostream>
#include "jqueue.h"

#include <cstdlib>

using namespace std;

template <typename T>
void queueUp(const bool &input, const bool &output, JQueue<T> &que);

template <typename T>
void resizeQue(JQueue<T> &que);

void choose(const bool &input, const bool &output, JQueue<int> &intQ, JQueue<double> &doubleQ,
            JQueue<char> &charQ, JQueue<string> &strQ, JQueue<char*> &cStrQ, char type);
void getInput(char &type, string &line);
void JQueueDemo();
bool again();

string forFunFail(string& s, int len, const string &alphabets) {
    if(!len) {
        cout << "s = " << s << endl;
        return s;
    }
    s += alphabets[rand()%alphabets.length()];
    forFunFail(s, len-1, alphabets);
    return s;
}

void forFun(string &s, int len, const string &alphabets) {
    if(!len) {
        return ;
    }
    s += alphabets[rand()%alphabets.length()];
    forFun(s, len-1, alphabets);
}

int main() {
    srand(time(0));
    string s(""), s2("");
    s2 = forFunFail(s, 5, "abcde");
    cout << s2 << endl;


//    char c = "hello"[0];
//    cout << c << endl;

//    do {
//        JQueueDemo();
//    } while(again());
//    return 0;
}

template <typename T>
void queueUp(const bool &input, const bool &output, JQueue<T> &que) {
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
void resizeQue(JQueue<T> &que) {
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

void choose(const bool &input, const bool &output, JQueue<int> &intQ, JQueue<double> &doubleQ,
            JQueue<char> &charQ, JQueue<string> &strQ, JQueue<char*> &cStrQ, char type) {
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

void JQueueDemo() {
    char type;
    string line;
    bool input, output;
    JQueue<int> intQ;
    JQueue<double> doubleQ;
    JQueue<char> charQ;
    JQueue<string> strQ;
    JQueue<char*> cStrQ;
    cout << "\n************************** JQueue Demo ******************************\n";
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

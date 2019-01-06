#include <iostream>
#include "jpriorityqueue.h"

using namespace std;

template <typename D, typename P>
void priorityQueueUp(const bool &input, const bool &output, JPriorityQueue<D,P> &que);

template <typename D, typename P>
void resizeOrDequeue(JPriorityQueue<D, P> &que, char &deque);

void getInput(string& types, string& line);
void priorityQueueDemo();
void choose(const bool &input, const bool &output, const string &types);
bool again();

int main() {
    do {
        priorityQueueDemo();
    }
    while(again());
    return 0;
}


void getInput(string& types, string& line) {
    cout << "Enter type for Data and Priority ('i' for int, 'd' for double, "
         << "\n'c' for char, and 's' for string): ";
    getline(cin, types);
    cout << "Enter 'i' for getting input from a file, 'o' for outputing to a file,\n"
         << "and any other key to just continue: ";
    getline(cin, line);
}

void priorityQueueDemo() {
    string types, line;
    bool input, output;
    cout << "\n********************** JPriorityQueue Demo **************************\n";
    getInput(types, line);
    input = (line.find_first_of('i') < line.length());
    output = (line.find_first_of('o') < line.length());
    choose(input, output, types);
}


template <typename D, typename P>
void priorityQueueUp(const bool &input, const bool &output, JPriorityQueue<D,P> &que) {
    string path;
    char deque;
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
    resizeOrDequeue(que, deque);
    if(deque=='y' || deque=='Y') {
        D data;
        cout << "Start dequeuing.." << endl;
        while(!que.empty()) {
            que >> data;
            cout << data << endl;
        }
    } else
        cout << "Your Queue has " << que.size() << " items:\n" << que;
    if(output) {
        ofstream out(path);
        out << que;
        out.close();
    }
}

template <typename D, typename P>
void resizeOrDequeue(JPriorityQueue<D, P> &que, char &deque) {
    char resize;
    cout << "Do you want to resize?[Y/N] ";
    cin >> resize;
    if(resize=='y' || resize=='Y') {
        size_t s;
        cout << "Enter size: ";
        cin >> s;
        que.resize(s);
    }
    cout << "Do you want to dequeue?[Y/N] ";
    cin >> deque;
}

void choose(const bool &input, const bool &output, const string &types) {
    JPriorityQueue<int, int> intQ;
    JPriorityQueue<double, double> doubleQ;
    JPriorityQueue<char, char> charQ;
    JPriorityQueue<string, string> strQ;
    JPriorityQueue<int, double> idQ;
    JPriorityQueue<int, char> icQ;
    JPriorityQueue<int, string> isQ;
    JPriorityQueue<double, int> diQ;
    JPriorityQueue<double, string> dsQ;
    JPriorityQueue<double, char> dcQ;
    JPriorityQueue<char, int> ciQ;
    JPriorityQueue<char, string> csQ;
    JPriorityQueue<char, double> cdQ;
    JPriorityQueue<string, double> sdQ;
    JPriorityQueue<string, char> scQ;
    JPriorityQueue<string, int> siQ;
    int type = 1;
    for(size_t i=0; i<types.length(); ++i)
        type *= (i + types[i]);
    switch (type) {
    case 'i' * ('i' + 1): priorityQueueUp(input, output, intQ);
        break;
    case 'd' * ('d' + 1): priorityQueueUp(input, output, doubleQ);
        break;
    case 'c' * ('c' + 1): priorityQueueUp(input, output, charQ);
        break;
    case 's' * ('s' + 1): priorityQueueUp(input, output, strQ);
        break;
    case 'i' * ('d' + 1): priorityQueueUp(input, output, idQ);
        break;
    case 'i' * ('c' + 1): priorityQueueUp(input, output, icQ);
        break;
    case 'i' * ('s' + 1): priorityQueueUp(input, output, isQ);
        break;
    case 'd' * ('i' + 1): priorityQueueUp(input, output, diQ);
        break;
    case 'd' * ('c' + 1): priorityQueueUp(input, output, dcQ);
        break;
    case 'd' * ('s' + 1): priorityQueueUp(input, output, dsQ);
        break;
    case 'c' * ('d' + 1): priorityQueueUp(input, output, cdQ);
        break;
    case 'c' * ('i' + 1): priorityQueueUp(input, output, ciQ);
        break;
    case 'c' * ('s' + 1): priorityQueueUp(input, output, csQ);
        break;
    case 's' * ('d' + 1): priorityQueueUp(input, output, sdQ);
        break;
    case 's' * ('i' + 1): priorityQueueUp(input, output, siQ);
        break;
    case 's' * ('c' + 1): priorityQueueUp(input, output, scQ);
        break;
    default: cout << "Invalid Input!" << endl;
    }
}

bool again() {
    string line;
    cout << "Again?[Y/N] ";
    cin.ignore(32767, '\n');
    getline(cin, line);
    return line[0] == 'y' || line[0] == 'Y';
}

#include <iostream>
#include "parser.h"

using namespace std;

int main() {
    Parser *test = new Parser("/Users/J/Desktop/wp.txt");
    clock_t start;
    vector<Node<string>> v;
    double duration;
    start = clock();
    test->load();
    test->getTenMostUsedWords(v);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "--------------------------------" << endl;
    test->getWordsThatStartsWith('a', v);
    cout << "Time: " << duration << endl;
    for(size_t i=0; i<v.size(); ++i)
        cout << v[i].data << " " << v[i].count << endl;
    delete test;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <ctime>
#include "parser.h"

using namespace std;

bool f1(int n) {
    cout << "calling f1..." << endl;
    return n<10;
}

bool f2(int n) {
    cout << "calling f2!!!" << endl;
    return n<11;
}

int main() {
    Parser *parser = new Parser("/Users/j/Desktop/wp.txt");
    vector<string> w;
    clock_t start;
    double duration;
    start = clock();
    parser->loadHeap();
    parser->getTenMostUsedWords(w);
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    parser->emptyHeap();
    cout << "Time: " << duration << endl;
    cout << "Reading level: "
         << (.39 * parser->getWordCount() / parser->getSentenceCount()) +
            (11.8 * parser->getSyllableCount() / parser->getWordCount()) - 15.59 << endl;
    for(int i=0; i<w.size(); ++i) {
        cout << w[i] << endl;
    }
    delete parser;
    return 0;



//    int n=0;
//    while(f1(n) || f2(n))
//        cout << n++ << endl;


//    for(char *c=c2; *c; ++c)
//        cout << *c << " ";

//    while((c2 = strchr(c2,'i')) || (c2 = strchr(c2,'o'))) {
//        if(*(c2+1)=='i' || *(c2+1)=='o') {
//            cout << "PRINT: " << *(c2) << ", " << *(c2+1) << endl;
//            ++c2;
//        } else
//            cout << *(c2) << endl;
//        ++c2;
//    }
}



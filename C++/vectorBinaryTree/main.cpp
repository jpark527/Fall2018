#include <iostream>
#include "mybinarytree.h"

using namespace std;

int main() {
    myBinaryTree<int> bt;
    int n;
    string s;
    while(1) {
        cout << "data: ";
        getline(cin, s);
        if(s.empty())
            break;
        n = stoi(s);
        bt << n;
        bt.print(cout, 0);
    }
    while(!bt.empty()) {
        Node<int> node; // FIX HERE!!!
        bt >> node;             //cout << 2222 << endl;
        cout << node.data << endl;              //cout << 33333 << endl;
    }
    return 0;
}

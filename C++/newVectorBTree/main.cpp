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
        Node<int> node;
        bt >> node;
        cout << node.data << endl;
    }
//    cout << -1 / 2 << endl;
    return 0;
}

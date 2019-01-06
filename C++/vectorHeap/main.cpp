#include <iostream>
#include "myheap.h"

using namespace std;

int main() {
        myHeap<int> hp;
        int data, n;
        srand(time(0));
        cout << "Enter number of random numbers to insert: ";
        cin >> n;

        for(int i = 0; i < n; ++i)
        {
            data = rand()%100;
            cout<<"Inserting "<<data<<endl;
            hp << data;
        }

        myHeap<int> hp2(hp);
        cout << "\n--------------------------------------\n" << endl << "Poping all data:\n";
        while(!hp2.empty())
        {
            hp2 >> data;
            cout<<data<<endl;
        }
        return 0;
}



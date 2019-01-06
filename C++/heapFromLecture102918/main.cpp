#include <iostream>
#include "heap.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    heap<int> myHeap;
    int data, n;
    srand(time(0));
    cout << "Enter number of random numbers to insert: ";
    cin >> n;

    for(int i = 0; i < n; ++i)
    {
        data = rand()%100;
        cout<<"Inserting "<<data<<endl;
        myHeap << data;
    }

    heap<int> heapCopy(myHeap);
    cout << "\n--------------------------------------\n" << endl << "Poping all data:\n";
    while(!heapCopy.empty())
    {
        heapCopy >> data;
        cout<<data<<endl;
    }
    return 0;
}

#include <iostream>
#include <cstdarg>
#include "myswitch.h"

using namespace std;

void up();
void down();
void left();
void right();

int main() {
    cout << "--------- mySwitch class with Vararg Demo ----------\n" << endl;
    mySwitch<fptr, fptr> ms("kvkvk", up, up, down, down, up);
    ms.getValue()();
    mySwitch<int, char*> ms2("kvkvkvk", 1, "left", 2, "right", 3, "up", 2);
    cout << ms2.getValue() << endl;
    cout << "\n----------------------------------------------------" << endl;
}

void up() {
    cout << "Up!" << endl;
}

void down() {
    cout << "Down!" << endl;
}

void left() {
    cout << "Left!" << endl;
}

void right() {
    cout << "Right!" << endl;
}

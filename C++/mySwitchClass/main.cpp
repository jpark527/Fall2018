#include <iostream>
#include "myswitch.h"

using namespace std;

void up();
void down();
void left();
void right();
void dummy();

int main() {
    cout << "--------- mySwitch class Demo ----------\n" << endl;
    map<fptr, fptr> m;
    m[up] = up;
    m[down] = down;
    m[left] = left;
    m[right] = right;
    mySwitch<fptr, fptr> ms(m, up);
    ms.getValue()();

    map<string, string> m2;
    m2["left"] = "<--";
    m2["right"] = "-->";
    m2["up"] = "^";
    m2["down"] = "v";
    mySwitch<string, string> ms2(m2, "right");
    cout << ms2.getValue() << endl;
    cout << "\n----------------------------------------" << endl;
    return 0;
}

void up() {
    cout << "UP!" << endl;
}

void down() {
    cout << "DOWN!" << endl;
}

void left() {
    cout << "LEFT!" << endl;
}

void right() {
    cout << "RIGHT!" << endl;
}

void dummy() {
    cout << "DUMMY!" << endl;
}

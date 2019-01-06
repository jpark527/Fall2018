#include <iostream>
#include <map>

using namespace std;

typedef void (*fptr)();

template<typename K>
fptr mySwitch(map<K,fptr> &data, K theKey);

void jump();
void upLeft();
void upRight();
void downLeft();
void downRight();
void up();
void down();
void left();
void right();
void quit();
void fire();
void nothing();

void forStringInput(map<string, fptr> &data);
void forIntegerInput(map<int, fptr> &data);
void forCharactorInput(map<char, fptr> &data);

int main() {
    map<string, fptr> stringTest;
    map<char, fptr> charTest;
    map<int, fptr> intTest;
    forStringInput(stringTest);
    forCharactorInput(charTest);
    forIntegerInput(intTest);
    string key("up");

    mySwitch(stringTest, key)();
    mySwitch(charTest, 'a')();
    mySwitch(intTest, 3)();

    return 0;
}

template<typename K>
fptr mySwitch(map<K, fptr> &data, K theKey) {
    return data[theKey];
}

void forStringInput(map<string, fptr>& data) {
    data["left"] = left;
    data["right"] = right;
    data["up"] = up;
    data["down"] = down;
    data["jump"] = jump;
    data["upLeft"] = upLeft;
    data["upRight"] = upRight;
    data["downLeft"] = downLeft;
    data["downRight"] = downRight;
    data["quit"] = quit;
    data["fire"] = fire;
    data[""] = nothing;
}

void forIntegerInput(map<int, fptr> &data) {
    data[0] = nothing;
    data[1] = left;
    data[2] = right;
    data[3] = up;
    data[4] = down;
    data[5] = jump;
    data[6] = upLeft;
    data[7] = upRight;
    data[8] = downLeft;
    data[9] = downRight;
    data[10] = quit;
    data[11] = fire;
}

void forCharactorInput(map<char, fptr> &data) {
    data[' '] = jump;
    data['q'] = data['Q'] = upLeft;
    data['e'] = data['E'] = upRight;
    data['z'] = data['Z'] = downLeft;
    data['c'] = data['C'] = downRight;
    data['w'] = data['W'] = up;
    data['s'] = data['S'] = down;
    data['a'] = data['A'] = left;
    data['d'] = data['D'] = right;
    data[27] = quit;
    data['f'] = data['F'] = fire;
}

void jump() {
    cout<<"Jump!"<<endl;
}

void upLeft() {
    cout<<"Up and Left!"<<endl;
}

void upRight() {
    cout<<"Up and Right!"<<endl;
}

void downLeft() {
    cout<<"Down and Left!"<<endl;
}

void downRight() {
    cout<<"Down and Right!"<<endl;
}

void up() {
    cout<<"Up!"<<endl;
}

void down() {
    cout<<"Down!"<<endl;
}

void left() {
    cout<<"Left!"<<endl;
}

void right() {
    cout<<"Right!"<<endl;
}

void quit() {
    cout<<"End of Game!"<<endl;
    exit(0);
}

void fire() {
    cout<<"Fire!"<<endl;
}

void nothing() { }

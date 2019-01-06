#include "word.h"

Word::Word(string w, size_t c) {
    myWord = w;
    count = c;
}

Word::~Word() {
    myWord.clear();
    count = 0;
}

Word::Word(const Word &other) {
    myWord = other.myWord;
    count = other.count;
}

Word& Word::operator=(const Word &other) {
    if(this != &other) {
        myWord = other.myWord;
        count = other.count;
    }
    return *this;
}

bool Word::operator>(const Word &rhs) {
    return count > rhs.count;
}

bool Word::operator<(const Word &rhs) {
    return count < rhs.count;
}

bool Word::operator>=(const Word &rhs) {
    return count >= rhs.count;
}

bool Word::operator<=(const Word &rhs) {
    return count <= rhs.count;
}

bool Word::operator==(const Word &rhs) {
    return count == rhs.count;
}



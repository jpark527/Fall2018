#include "word.h"

Word::Word(const string &w, size_t paragraph, size_t line) {
    myWord = w;
    paragraphs.push_back(paragraph);
    lines.push_back(line);
}

Word::~Word() {
    myWord.clear();
    paragraphs.clear();
    lines.clear();
}

Word::Word(const Word &other) {
    myWord = other.myWord;
    copy(other.paragraphs.begin(), other.paragraphs.end(), back_inserter(paragraphs));
    copy(other.lines.begin(), other.lines.end(), back_inserter(lines));
}

Word& Word::operator=(const Word &other) {
    if(this != &other) {
        paragraphs.clear();
        lines.clear();
        myWord = other.myWord;
        copy(other.paragraphs.begin(), other.paragraphs.end(), back_inserter(paragraphs));
        copy(other.lines.begin(), other.lines.end(), back_inserter(lines));
    }
    return *this;
}

bool operator>(const Word &lhs, const Word &rhs) {
    int length = lhs.myWord.length() > rhs.myWord.length() ? rhs.myWord.length() : lhs.myWord.length();
    for(int i=0; i<length; ++i)  {
        if(lhs.myWord[i] > rhs.myWord[i])
            return true;
        else if(lhs.myWord[i] < rhs.myWord[i])
            return false;
    }
    return lhs.myWord.length() > rhs.myWord.length();
}

bool operator<(const Word &lhs, const Word &rhs) {
    int length = lhs.myWord.length() > rhs.myWord.length() ? rhs.myWord.length() : lhs.myWord.length();
    for(int i = 0; i < length; i++) {
        if(lhs.myWord[i] < rhs.myWord[i])
            return true;
        else if(lhs.myWord[i] > rhs.myWord[i])
            return false;
    }
    return lhs.myWord.length() < rhs.myWord.length();
}

bool operator>=(const Word &lhs, const Word &rhs) {
    int length = lhs.myWord.length() > rhs.myWord.length() ? rhs.myWord.length() : lhs.myWord.length();
    for(int i = 0; i < length; i++) {
        if(lhs.myWord[i] > rhs.myWord[i])
            return true;
        else if(lhs.myWord[i] < rhs.myWord[i])
            return false;
    }
    return lhs.myWord.length() >= rhs.myWord.length();
}

bool operator<=(const Word &lhs, const Word &rhs) {
    int length = lhs.myWord.length() > rhs.myWord.length() ? rhs.myWord.length() : lhs.myWord.length();
    for(int i = 0; i < length; i++) {
        if(lhs.myWord[i] < rhs.myWord[i])
            return true;
        else if(lhs.myWord[i] > rhs.myWord[i])
            return false;
    }
    return lhs.myWord.length() <= rhs.myWord.length();
}

bool operator==(const Word &lhs, const Word &rhs) {
    if(lhs.myWord.length() != rhs.myWord.length())
        return false;
    for(size_t i=0; i<lhs.myWord.length(); ++i)
        if(lhs.myWord[i] != rhs.myWord[i])
            return false;
    return true;
}

bool operator!=(const Word &lhs, const Word &rhs) {
    if(lhs.myWord.length() != rhs.myWord.length())
        return true;
    for(size_t i=0; i<lhs.myWord.length(); ++i)
        if(lhs.myWord[i] != rhs.myWord[i])
            return true;
    return false;
}

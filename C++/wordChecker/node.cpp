#include "node.h"

Node::Node(const string &w, size_t paragraph, size_t line) {
    word = w;
    paragraphNumber = paragraph;
    lineNumber = line;
}

Node::~Node() {
    word.clear();
    paragraphNumber = lineNumber = 0;
}

Node::Node(const Node &other) {
    word = other.word;
    paragraphNumber = other.paragraphNumber;
    lineNumber = other.lineNumber;
}

Node& Node::operator=(const Node &other) {
    if(this != &other) {
        word = other.word;
        paragraphNumber = other.paragraphNumber;
        lineNumber = other.lineNumber;
    }
    return *this;
}

bool Node::operator>(const Node &rhs) {
    int length = word.length() > rhs.word.length() ? rhs.word.length() : word.length();
    for(int i=0; i<length; ++i)  {
        if(word[i] > rhs.word[i])
            return true;
        else if(word[i] < rhs.word[i])
            return false;
    }
    return word.length() > rhs.word.length();
}

bool Node::operator<(const Node &rhs) {
    int length = word.length() > rhs.word.length() ? rhs.word.length() : word.length();
    for(int i = 0; i < length; i++) {
        if(word[i] < rhs.word[i])
            return true;
        else if(word[i] > rhs.word[i])
            return false;
    }
    return word.length() < rhs.word.length();
}

bool Node::operator>=(const Node &rhs) {
    int length = word.length() > rhs.word.length() ? rhs.word.length() : word.length();
    for(int i = 0; i < length; i++) {
        if(word[i] > rhs.word[i])
            return true;
        else if(word[i] < rhs.word[i])
            return false;
    }
    return word.length() >= rhs.word.length();
}

bool Node::operator<=(const Node &rhs) {
    int length = word.length() > rhs.word.length() ? rhs.word.length() : word.length();
    for(int i = 0; i < length; i++) {
        if(word[i] < rhs.word[i])
            return true;
        else if(word[i] > rhs.word[i])
            return false;
    }
    return word.length() <= rhs.word.length();
}

bool Node::operator==(const Node &rhs) {
    if(word.length() != rhs.word.length())
        return false;
    for(size_t i=0; i<word.length(); ++i)
        if(word[i] != rhs.word[i])
            return false;
    return true;
}

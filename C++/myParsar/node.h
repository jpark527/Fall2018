#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

struct Node {
    string word;
    size_t paragraphNumber;
    size_t lineNumber;

    Node(const string &w="", size_t paragraph=0, size_t line=0);
    ~Node();
    Node(const Node &other);
    Node& operator=(const Node &other);
    bool operator>(const Node &rhs);
    bool operator<(const Node &rhs);
    bool operator>=(const Node &rhs);
    bool operator<=(const Node &rhs);
    bool operator==(const Node &rhs);
};

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

struct Word {
    string myWord;
    size_t count;

    Word(string w="", size_t c=0);
    ~Word();
    Word(const Word &other);
    Word& operator=(const Word &other);
    bool operator>(const Word &rhs);
    bool operator<(const Word &rhs);
    bool operator>=(const Word &rhs);
    bool operator<=(const Word &rhs);
    bool operator==(const Word &rhs);
};

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

#endif // NODE_H

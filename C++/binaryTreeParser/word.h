#ifndef WORD_H
#define WORD_H
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct Word {
    string myWord;
    vector<size_t> paragraphs;
    vector<size_t> lines;
    Word(const string &w="", size_t paragraph=0, size_t line=0);
    ~Word();
    Word(const Word &other);
    Word& operator=(const Word &other);
    friend bool operator>(const Word &lhs, const Word &rhs);
    friend bool operator<(const Word &lhs, const Word &rhs);
    friend bool operator>=(const Word &lhs, const Word &rhs);
    friend bool operator<=(const Word &lhs, const Word &rhs);
    friend bool operator==(const Word &lhs, const Word &rhs);
    friend bool operator!=(const Word &lhs, const Word &rhs);
};

#endif // WORD_H

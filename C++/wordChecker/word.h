#ifndef WORD_H
#define WORD_H
#include <string>

using namespace std;

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

#endif // WORD_H

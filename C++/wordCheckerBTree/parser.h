#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "mybinarytree.h"
#include "word.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#define twentySix 26

enum PARSER_ERRORS{FILE_DNE};

using namespace std;

// Comparator
struct countComparator {
    bool operator()(const Node<Word> *l, const Node<Word> *r);
};

class Parser {
    string fileName;
    size_t sentenceCount, paragraphCount, lineCount, syllableCount, wordCount;
    myBinaryTree<Word> *tree;
    void cleanSplitPush(char *&w);
    void copy(const Parser &other);
    void addVowel(const string &data);
    void checkSyllables(const string &word);
    const char* checkVowel(const char *d);

public:
    Parser(const string &file="");
    ~Parser();
    Parser(const Parser &other);
    Parser &operator=(const Parser &other);
    void setFileName(const string &file);
    string getFileName() const;
    const char* readFile();
    void load();
    void getTenMostUsedWords(vector<Node<string>> &words);
    size_t getLineCount() const;
    size_t getParagraphCount() const;
    size_t getSentenceCount() const;
    size_t getSyllableCount() const;
    size_t getWordCount() const;
    double getReadingLevel() const;
    size_t getSizeOf(char letter) const;
    void getWordsThatStartsWith(char letter, vector<Node<string>> &data);
    void clear();
};

#endif // PARSER_H

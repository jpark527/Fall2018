#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "myHeap.h"
#include "node.h"
#include <algorithm>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#define twentySix 26
#define ten 10

enum PARSER_ERRORS{FILE_DNE};

using namespace std;

struct Spliter : public string {
    friend istream& operator>>(istream& in, Spliter& output);
};

istream& operator>>(istream& in, Spliter& output) {
    getline(in, output, ' ');
    return in;
}

class Parser {
    string fileName;
    size_t sentenceCount, paragraphCount, lineCount, syllableCount, wordCount;
    myHeap<Node> *heaps;
    void cleanSplitPush(string &word);
    void copy(const Parser &other);
    const char* readFile(const char *file);
    void addVowel(const string &data);
    void checkSyllables(const string &word);
    const char* checkVowel(const char *d);

public:
    Parser(const string &file);
    ~Parser();
    Parser(const Parser &other);
    Parser &operator=(const Parser &other);
    void setFileName(const string &file);
    string getFileName() const;
    void loadHeap();
    void emptyHeap();
    void getTenMostUsedWords(vector<string> &words);
    size_t getLineCount() const;
    size_t getParagraphCount() const;
    size_t getSentenceCount() const;
    size_t getSyllableCount() const;
    size_t getWordCount() const;
    void clear();
};

// Public
Parser::Parser(const string &file) {
    fileName = file;
    heaps = new myHeap<Node>[twentySix];
    sentenceCount = syllableCount = wordCount = 0;
    lineCount = paragraphCount = 1;
}

Parser::~Parser() {
    fileName.clear();
    delete[] heaps;
    sentenceCount = syllableCount = wordCount = 0;
    lineCount = paragraphCount = 1;
}

Parser::Parser(const Parser &other) {
    copy(other);
}

Parser& Parser::operator=(const Parser &other) {
    if(this != &other)
        copy(other);
    return *this;
}

void Parser::setFileName(const string &file) {
    fileName = file;
}

string Parser::getFileName() const {
    return fileName;
}

size_t Parser::getLineCount() const {
    return lineCount;
}

size_t Parser::getParagraphCount() const {
    return paragraphCount;
}

size_t Parser::getSentenceCount() const {
    return sentenceCount;
}

size_t Parser::getSyllableCount() const {
    return syllableCount;
}

size_t Parser::getWordCount() const {
    return wordCount;
}

void Parser::loadHeap() {
    string file(readFile(fileName.c_str()));
    transform(file.begin(), file.end(), file.begin(), ::tolower);
    istringstream ss(file);
    vector<string> v((istream_iterator<Spliter>(ss)), istream_iterator<Spliter>());
    addVowel(file);
    for(size_t i=0; i<v.size(); ++i)
        cleanSplitPush(v[i]);
}

void Parser::getTenMostUsedWords(vector<string> &words) {
    string prev("");
    size_t count;
    myHeap<Word> w;
    for(size_t i=0; i<twentySix; ++i) {
        myHeap<Node> *store = new myHeap<Node>(heaps[i]);
        Node data;
        while(!store->empty()) {
            *store >> data;
            if(prev != data.word) {
                w.push(Word(prev, count));
                prev = data.word;
                count = 0;
            } else
                ++count;
        }
        delete store;
    }
    for(int i=0; i<ten; ++i) {
        Word data;
        w >> data;
        if(data.myWord=="") {
            --i;
            continue;
        }
        words.push_back(data.myWord);
    }
}

void Parser::clear() {
    sentenceCount = syllableCount = wordCount = 0;
    paragraphCount = lineCount = 1;
    delete[] heaps;
    heaps = new myHeap<Node>[twentySix];
}

void Parser::emptyHeap() {
    for(int i=0; i<twentySix; ++i) {
        cout << "heaps[" << i << "].size() = " << heaps[i].size() << endl;
    }

    for(int i=0; i<twentySix; ++i) {
        while(!heaps[i].empty()) {
            Node data;
            heaps[i] >> data;
            cout <<"PRINT: "<< data.word << " " << data.paragraphNumber << " " << data.lineNumber << endl;
        }
    }

    cout << "total sentence#: " << sentenceCount << endl;
    cout << "total line#: " << lineCount << endl;
    cout << "total paragraph#: " << paragraphCount << endl;
    cout << "total syllable#: " << syllableCount << endl;
    cout << "total word#: " << wordCount << endl;
}

// Private
void Parser::cleanSplitPush(string &word) {
    size_t pos, countReturn=0;
    bool isSentence = false;
    string sub(word);
    while((pos = sub.find_first_not_of("abcdefghijklmnopqrstuvwxyz' ")) < sub.size()) {
        if(word[pos]=='.' || word[pos]=='!' || word[pos]=='?')
            isSentence = true;
        else if(word[pos]=='\n') {
            ++lineCount;
            ++countReturn;
        }                                           cout << "WORD_BEFORE: " << sub << " [" << pos <<"] = " << (int)(sub[pos]) << endl;
        if((int)(sub[pos]) >= 0)
            word.replace(pos, 1, " ");
        sub.replace(pos, 1, " ");                   cout << "WORD_AFTER: " << sub  << endl;
    }
    if(isSentence)
        ++sentenceCount;
    if(countReturn > 1)
        ++paragraphCount;
    istringstream ss(word);
    vector<string> v((istream_iterator<Spliter>(ss)), istream_iterator<Spliter>());
    for(size_t i=0; i<v.size(); ++i) {
        word = v[i];       
        if(word[0]-'a' >= 0 && word[0]-'a' < twentySix) {
            checkSyllables(word);
            word[0] = toupper(word[0]);
            heaps[(word[0]-'A')].push(Node(word, paragraphCount, lineCount));
            ++wordCount;
        }
    }
}

const char* Parser::readFile(const char *file) {
    int fd = open(file, O_RDONLY);
    struct stat sb;
    fstat(fd, &sb);
    const char* data = static_cast<const char*>(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0u));
    return data;
}

void Parser::copy(const Parser &other) {
    fileName = other.fileName;
    sentenceCount = other.sentenceCount;
    paragraphCount = other.paragraphCount;
    syllableCount = other.syllableCount;
    lineCount = other.lineCount;
    memcpy(heaps, other.heaps, sizeof(Node)*twentySix);
}

void Parser::addVowel(const string &data) {
    const char *d = data.c_str();
    while(*d && (d = checkVowel(d))) {
        if(*(d+1)=='a' || *(d+1)=='e' || *(d+1)=='i' || *(d+1)=='o' || *(d+1)=='u' || *(d+1)=='y')
            ++d;
        ++syllableCount, ++d;
    }
}

void Parser::checkSyllables(const string &word) {
    const char *data = word.c_str();
    if(strstr(data, "ao") || strstr(data, "eo") || strstr(data, "ua") || strstr(data, "uo"))
        ++syllableCount;
    if(strstr(data, "eau") || strstr(data, "iou") || (word[word.length()-1]=='e'))
        --syllableCount;
}

const char* Parser::checkVowel(const char *d) {
    while (*d && *d != 'a' && *d != 'e' && *d != 'i' && *d != 'o' && *d != 'u' && *d != 'y')
        ++d;
    return d;
}

//ai, ay, au, ae, aa, //ao
//ee, ea, ei, ey, eu, //eo
//ie, ii, io, //ia, iu, iy
//oo, ou, oe, oa, oy, oi
//ue, ui, uu, uy, //ua, uo
//ya, ye, yo, yu, yy, yi

#endif // PARSER_H

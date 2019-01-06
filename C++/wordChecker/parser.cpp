#include "parser.h"
#include <QDebug>
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
    sentenceCount = lineCount = paragraphCount = syllableCount = wordCount = 0;
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

double Parser::getReadingLevel() const {
    return (.39 * wordCount / sentenceCount) + (11.8 * syllableCount / wordCount) - 15.59;
}

size_t Parser::getSizeOf(char letter) const {
    return heaps[tolower(letter)-'a'].size();
}

const char* Parser::readFile() {
    int fd = open(fileName.c_str(), O_RDONLY);
    struct stat sb;
    fstat(fd, &sb);
    const char* data = static_cast<const char*>(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    return data;
}

void Parser::loadHeap() {
    string file(readFile());
    char *text, *w;
    transform(file.begin(), file.end(), file.begin(), ::tolower);
    future<void> vowel = async(&Parser::addVowel, ref(*this), ref(file));
    vowel.get();
    text = strdup(file.c_str());
    while((w = strtok_r(text, " \n—", &text)))
        cleanSplitPush(w);
}

void Parser::getTenMostUsedWords(vector<Word> &words) {
    string prev("");
    size_t count = 1;
    myHeap<Word> w;
    for(size_t i=0; i<twentySix; ++i) {
        myHeap<Node> *store = new myHeap<Node>(heaps[i]);
        Node data;
        while(!store->empty()) {
            *store >> data;
            if(prev != data.word) {
                w.push(Word(prev, count));
                prev = data.word;
                count = 1;
            } else
                ++count;
        }
        delete store;
    }
    for(int i=0; i<10; ++i) {
        Word data;
        w >> data;
        if(data.myWord=="") {
            --i;
            continue;
        }
        words.push_back(data);
    }
}

void Parser::clear() {
    sentenceCount = syllableCount = wordCount = 0;
    lineCount = paragraphCount = 1;
    delete[] heaps;
    heaps = new myHeap<Node>[twentySix];
}

void Parser::getWordsThatStartsWith(char letter, vector<string> &words, vector<int> &count) {
    myHeap<Node> *temp = new myHeap<Node>(heaps[tolower(letter)-'a']);
    Node node;
    string data("");
    int num=0;
    while(!temp->empty()) {
        *temp >> node;
        data.empty() ? data = node.word : data;
        if(node.word != data) {
            words.push_back(data);
            count.push_back(num);
            data = node.word;
            num=1;
        } else
            ++num;
    }
    words.push_back(data);
    count.push_back(num);
}

// Private
void Parser::cleanSplitPush(char *&w) {
    size_t pos;
    string word(w), sub(w);
    if(word=="\r")
        ++paragraphCount;
    else if(word.find_last_of(".!?") < word.size())
        ++sentenceCount;
    while((pos = sub.find_first_not_of("abcdefghijklmnopqrstuvwxyz' ")) < sub.size()) {
        if(word[pos]=='\r')
            ++lineCount;
        if((int)(word[pos]) >= 0 && (int)(word[pos]) < 128)
            word.replace(pos, 1, " ");
        sub.replace(pos, 1, " ");
    }
    while((pos = word.find_last_of(" ")) < word.size())
        word.replace(pos, 1, "");
    if(word[0]-'a' >= 0 && word[0]-'a' < twentySix) {
        checkSyllables(word);
        word[0] = toupper(word[0]);
        heaps[(word[0]-'A')].push(Node(word, paragraphCount, lineCount));
        ++wordCount;
    }
}

void Parser::copy(const Parser &other) {
    fileName = other.fileName;
    sentenceCount = other.sentenceCount;
    paragraphCount = other.paragraphCount;
    syllableCount = other.syllableCount;
    lineCount = other.lineCount;
    memcpy(heaps, other.heaps, sizeof(myHeap<Node>)*twentySix);
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

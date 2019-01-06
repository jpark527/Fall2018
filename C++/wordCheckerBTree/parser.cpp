#include "parser.h"

// Comparator
bool countComparator::operator()(const Node<Word> *l, const Node<Word> *r) {
    return l->count > r->count;
}

// Public
Parser::Parser(const string &file) {
    fileName = file;
    tree = new myBinaryTree<Word>[twentySix];
    sentenceCount = syllableCount = wordCount = 0;
    lineCount = paragraphCount = 1;
}

Parser::~Parser() {
    fileName.clear();
    delete[] tree;
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
    return tree[tolower(letter)-'a'].dataCount();
}

const char* Parser::readFile() {
    int fd = open(fileName.c_str(), O_RDONLY);
    struct stat sb;
    fstat(fd, &sb);
    const char* data = static_cast<const char*>(mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    return data;
}

void Parser::load() {
    string file(readFile());
    char *text, *w;
    transform(file.begin(), file.end(), file.begin(), ::tolower);
    addVowel(file);
    text = strdup(file.c_str());
    while((w = strtok_r(text, " \n—", &text)))
        cleanSplitPush(w);
}

void Parser::getTenMostUsedWords(vector<Node<string>> &words) {
    vector<Node<Word>*> w, all;
    countComparator cp;
    for(size_t i=0; i<twentySix; ++i) {
        if(!tree[i].empty())
            tree[i].flush(all);
        sort(all.begin(), all.end(), cp);
        for(size_t j=0; j<all.size() && j<10; ++j)
            w.push_back(all[j]);
        all.clear();
    }
    sort(w.begin(), w.end(), cp);
    for(size_t i=0; i<w.size() && i<10; ++i)
        words.push_back(Node<string>(w[i]->data.myWord, w[i]->count));
}

void Parser::clear() {
    sentenceCount = syllableCount = wordCount = 0;
    lineCount = paragraphCount = 1;
    delete[] tree;
    tree = new myBinaryTree<Word>[twentySix];
}

void Parser::getWordsThatStartsWith(char letter, vector<Node<string>> &data) {
    vector<Node<Word>*> w;
    tree[tolower(letter)-'a'].clearStatus();
    if(!tree[tolower(letter)-'a'].empty())
        tree[tolower(letter)-'a'].flush(w);
    for(size_t i=0; i<w.size(); ++i)
        data.push_back(Node<string>(w[i]->data.myWord, w[i]->count));
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
        tree[(word[0]-'A')].insert(Word(word, paragraphCount, lineCount));
        ++wordCount;
    }
}

void Parser::copy(const Parser &other) {
    fileName = other.fileName;
    sentenceCount = other.sentenceCount;
    paragraphCount = other.paragraphCount;
    syllableCount = other.syllableCount;
    lineCount = other.lineCount;
    memcpy(tree, other.tree, sizeof(myBinaryTree<Word>)*twentySix);
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

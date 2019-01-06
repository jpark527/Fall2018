#include "mydatabase.h"

// Public
myDatabase::myDatabase() {
    myData = new double[26];
    initialize();
}

myDatabase::~myDatabase() {
    clear();
    delete[] myData;
    delete[] bin;
    delete[] compute;
}

myDatabase::myDatabase(const myDatabase &other) {
    myData = new double[26];
    initialize();
    clear();
    for(size_t i=0; i<26; ++i)
        myData[i] = other.myData[i];
    myData = other.myData;
}

myDatabase& myDatabase::operator=(const myDatabase &other) {
    if(this != &other) {
        clear();
        for(size_t i=0; i<26; ++i)
            myData[i] = other.myData[i];
    }
    return *this;
}

void myDatabase::addData(char key, double value) {
    myData[key-'A'] = value;
}

double myDatabase::operator[](char key) const {
    if(key < 'A' || key > 'Z')
        throw BAD_INPUT;
    return myData[key-'A'];
}

double myDatabase::solve(const string& expression) {
    double ans = 0.;
    parser << expression;
    parser.parse();
    parser >> tokens;
    while(!tokens.empty()) {
        myPair p;
        tokens >> p;
        bin[p.type](*this, p);
        if(!ops.empty()) {
            char c;
            double x, y;
            ops >> c;
            numbers >> y >> x;
            numbers << compute[c](*this, x, y);
        }
    }
    if(numbers.size() != 1)
        throw BAD_INPUT;
    numbers >> ans;
    while(!ops.empty()) {
        char c;
        ops >> c;
        if(c != '(') {
            throw BAD_INPUT;
        }
    }
    parser.clear();
    return ans;
}

void myDatabase::clear() {
    for(size_t i=0; i<26; ++i)
        myData[i] = 0.;
}

// Private
void myDatabase::initialize() {
    for(size_t i=0; i<26; ++i)
        myData[i] = 0.;

    bin = new function<void(myDatabase&, myPair&)>[4];
    bin[NONE] = &myDatabase::junk;
    bin[CHAR] = &myDatabase::fromChar;
    bin[INT ] = &myDatabase::fromInt;
    bin[DOUBLE] = &myDatabase::fromDouble;

    compute = new function<double(myDatabase&, double, double)>[128];
    for(size_t i=0; i<128; ++i)
        compute[i] = &myDatabase::dummy;
    compute['+'] = &myDatabase::add;
    compute['-'] = &myDatabase::sub;
    compute['*'] = &myDatabase::mult;
    compute['/'] = &myDatabase::div;
    compute['^'] = &myDatabase::power;
}

void myDatabase::junk(myPair& p) { }

void myDatabase::fromChar(myPair& p) {
    char c = *(static_cast<char*>(p.data));
    ops << c;
    delete static_cast<char*>(p.data);
    p.data = nullptr;
}

void myDatabase::fromInt(myPair& p) {
    double d = (double)*(static_cast<int*>(p.data));
    numbers << d;
    delete static_cast<int*>(p.data);
    p.data = nullptr;
}

void myDatabase::fromDouble(myPair& p) {
    double d = *(static_cast<double*>(p.data));
    numbers << d;
    delete static_cast<double*>(p.data);
    p.data = nullptr;
}

double myDatabase::add(double x, double y) {
    return x + y;
}

double myDatabase::sub(double x, double y) {
    return x - y;
}

double myDatabase::mult(double x, double y) {
    return x * y;
}

double myDatabase::div(double x, double y) {
    if(!y)
        throw BAD_INPUT;
    return x / y;
}

double myDatabase::power(double x, double y) {
    return pow(x,y);
}

double myDatabase::dummy(double x, double y) {
    throw BAD_INPUT;
}

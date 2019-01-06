#ifndef MYDATABASE_H
#define MYDATABASE_H
#include "mynewtypes.h"
#include "myparser.h"
#include <math.h>

using namespace std;

class myDatabase {
    double* myData;
    myParser parser;
    myStack<double> numbers;
    myStack<char> ops;
    myQueue<myPair> tokens;
    function<void(myDatabase&, myPair&)>* bin;
    function<double(myDatabase&, double, double)>* compute;

    void initialize();
    void junk(myPair& p);
    void fromChar(myPair& p);
    void fromInt(myPair& p);
    void fromDouble(myPair& p);

    double add(double x, double y);
    double sub(double x, double y);
    double mult(double x, double y);
    double div(double x, double y);
    double power(double x, double y);
    double dummy(double x, double y);

public:
    myDatabase();
    ~myDatabase();
    myDatabase(const myDatabase &other);
    myDatabase& operator=(const myDatabase &other);

    void addData(char key, double value);
    double operator[](char key) const;
    double solve(const string& expression);
    void clear();

};

#endif // MYDATABASE_H

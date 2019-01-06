#ifndef MYPARSER_H
#define MYPARSER_H
#include "mynewtypes.h"
#include "mystack.h"
#include "myqueue.h"
#include <map>

using namespace std;

class myParser {
public:
    myParser();
    myParser(const myParser &other);
    ~myParser();
    myParser& operator=(const myParser &other);

    void parse();
    void clear();
    myParser& operator<<(const string& exp);
    myParser& operator>>(myQueue<myPair> &rpnQue);

private:
    function<void(myParser&, char)>* bin;
    myStack<char> operators, operands;
    myQueue<char> input;
    myQueue<myPair> rpn;

    map<char, int> precedence = {{'^',3}, {'*',2}, {'/',2}, {'+', 1}, {'-',1}, {'(',0}};
    bool op, number, parenthesis, zero;
    size_t intNum;
    double doubleNum;

    void initialize();
    void numbers(char c);
    void ops(char c);
    void junk(char c);

    void autoQueResizer(myStack<char> &stck);
    void autoStkResizer();
    void flushOperands();
    void sortOperators(char c);
    bool nextNumbers();

    void copy(const myParser &other);
    void pushNumbersToRPN();
    void pushOpsToRPN(char c);
};


#endif // MYPARSER_H

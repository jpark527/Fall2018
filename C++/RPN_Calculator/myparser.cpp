#include "myparser.h"

// Private
void myParser::initialize() {
    bin = new function<void(myParser&, char)>[128];
    for(size_t i=0; i<128; ++i)
        bin[i] = &myParser::junk;
    for(size_t i=48; i<58; ++i)
        bin[i] = &myParser::numbers;
    bin['.'] = &myParser::numbers;
    bin[' '] = &myParser::numbers;
    bin['^'] = &myParser::ops;
    bin['+'] = &myParser::ops;
    bin['-'] = &myParser::ops;
    bin['*'] = &myParser::ops;
    bin['/'] = &myParser::ops;
    bin['('] = &myParser::ops;
    bin[')'] = &myParser::ops;
}

void myParser::pushNumbersToRPN() {
    if(intNum) {
        int *intData = new int(intNum);
        rpn << myPair(intData, INT);
    }
    if(doubleNum) {
        double *dData = new double(doubleNum);
        rpn << myPair(dData, DOUBLE);
    }
    if(zero) {
        double *zeroData = new double(0.);
        rpn << myPair(zeroData, DOUBLE);
        zero = false;
    }
    intNum = 0;
    doubleNum = 0;
}

void myParser::pushOpsToRPN(char c) {
    char *cData = new char(c);
    rpn << myPair(cData, CHAR);
}

bool myParser::nextNumbers() {
    char peek = input.peek();
    return (peek >= '0' && peek <= '9') || peek == '.' || peek == ' ';
}

void myParser::numbers(char c) {
    operands << c;
    if(!nextNumbers()) {
        flushOperands();
        pushNumbersToRPN();
    }
    op = false;
    number = true;
}

void myParser::flushOperands() {
    size_t power = 1;
    double dividedBy = 1.;
    bool isDouble = false;
    char c;
    string zeroN("");
    while(!operands.empty()) {
        operands >> c;
        if(c==' ')
            continue;
        zeroN += c;
        if(c=='.') {
            dividedBy = power;
            isDouble = true;
            continue;
        } else if(c=='-') {
            intNum *= -1;
            break;
        } else
            intNum += ((c-48) * power);
        power *= 10;
    }
    zero = (zeroN=="0" || zeroN=="0." || zeroN=="0.0" || zeroN=="0.00");
    if(isDouble) {
        doubleNum = double(intNum) / dividedBy;
        intNum = 0;
    }
}

void myParser::ops(char c) {
    if(c=='-' && input.peek()>='0' && input.peek()<='9') {
        operands << c;
        return;
    }
    if(op)
        throw BAD_INPUT;
    else {
        sortOperators(c);
        number = false;
        if(c != ')')
            op = true;
    }
}

void myParser::junk(char c) {
    throw BAD_INPUT;
}

void myParser::sortOperators(char c) {
    char tempOp = '\0';
    if(c==')') {
        parenthesis = false;
        while(operators.size()>1) {
            tempOp = operators.pop();
            if(tempOp == '(')
                break;
            else
                pushOpsToRPN(tempOp);
        }
    } else {
        char peek = operators.peek();
        if(c == '(')
            parenthesis = true;
        else if(peek != '(' && peek != '\007' && precedence[c] <= precedence[peek])
            tempOp = operators.pop();
        operators << c;
        if(tempOp)
            pushOpsToRPN(tempOp);
    }
}

void myParser::copy(const myParser &other) {
    initialize();
    this->operators = other.operators;
    this->operands = other.operands;
    this->input = other.input;
    this->rpn = other.rpn;
    this->precedence = other.precedence;
    this->op = other.op;
    this->number = other.number;
    this->zero = other.zero;
    this->parenthesis = other.parenthesis;
    this->intNum = other.intNum;
    this->doubleNum = other.doubleNum;
}

void myParser::autoQueResizer(myStack<char> &stck) {
    if(stck.full()) {
        size_t add = int(stck.size() / 3);
        if(&stck == &operators)
            operators.resize(operators.size() + add);
         else
            operands.resize(operands.size() + add);
    }
}

void myParser::autoStkResizer() {
    if(input.full()) {
        size_t add = int(input.size() / 3);
        input.resize(input.size() + add);
    }
}

//Public
myParser::myParser() {
    doubleNum = 0;
    intNum = 0;
    initialize();
    number = true;
    zero = op = parenthesis = false;
    operators << '\007';
}

myParser::myParser(const myParser &other) {
    copy(other);
}

myParser::~myParser() {
    precedence.clear();
    zero = op = number = parenthesis = false;
    intNum = 0;
    doubleNum = 0;
    delete[] bin;
}

myParser& myParser::operator=(const myParser &other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void myParser::parse() {
    char data;
    while(!input.empty()) {
        input >> data;
        bin[data](*this, data);
        autoQueResizer(operators);
        autoQueResizer(operands);
    }
    flushOperands();
    pushNumbersToRPN();
    while(operators.size()>1) {
        operators >> data;
        if(!data)
            break;
        if(data != '(')
            pushOpsToRPN(data);
    }
    if(parenthesis)
        throw BAD_INPUT;
}

void myParser::clear() {
    doubleNum = 0;
    intNum = 0;
    number = true;
    op = parenthesis = false;
    input.clear();
    operators.clear();
    operands.clear();
    rpn.clear();
    operators << '\007';
}

myParser& myParser::operator>>(myQueue<myPair> &rpnQue) {
    rpnQue = this->rpn;
    return *this;
}

myParser& myParser::operator<<(const string& exp) {
    clear();
    int count = 0;
    for(size_t i=0; i<exp.length(); ++i) {
        input << exp.at(i);
        autoStkResizer();
        if(exp.at(i)=='(')
            ++count;
        if(exp.at(i)==')')
            --count;
    }
    if(count)
        throw BAD_INPUT;
    return *this;
}

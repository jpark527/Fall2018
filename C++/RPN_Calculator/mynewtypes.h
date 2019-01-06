#ifndef MYNEWTYPES_H
#define MYNEWTYPES_H

enum MY_TYPE { NONE, CHAR, INT, DOUBLE, STRING, C_STRING };
enum MY_ERROR { EMPTY, FULL, BAD_SIZE, BAD_INPUT };

struct myPair {
    void* data;
    MY_TYPE type;

    myPair(void* data=nullptr, MY_TYPE type=NONE);
};

#endif // MYNEWTYPES_h

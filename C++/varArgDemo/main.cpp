#include <iostream>
#include <cstdarg>

using namespace std;

// fyi: printf uses vararg.

int add(int numOfArg, ...);
int myPrintf(const char *format, ...);

int main() {
    myPrintf("10 + 20 + 30 + 40 + 50 + 60 + 70 = %d\n", add(7, 10, 20, 30, 40, 50, 60, 70));

    myPrintf("hello world!\n");
    return 0;
}

int add(int numOfArg, ...) {
    va_list args;

    int total = 0;

    va_start(args, numOfArg);
    for(int i=0; i<numOfArg; ++i) {
        int arg = va_arg(args, int);
        total += arg;
    }

    va_end(args);   // Don't usually need this, but for portability purpose..

    return total;
}

int myPrintf(const char *format, ...) {
    va_list args;
    int done;

    // Only allow to print strings that contain the word "hello".
    const char *subStr = strstr(format, "hello");
    if(subStr != format)
        return 0;

    va_start(args, format);
    done = vfprintf(stdout, format, args);

    va_end(args);

    return done;
}

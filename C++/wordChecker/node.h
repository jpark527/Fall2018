#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

struct Node {
    string word;
    size_t paragraphNumber;
    size_t lineNumber;

    Node(const string &w="", size_t paragraph=0, size_t line=0);
    ~Node();
    Node(const Node &other);
    Node& operator=(const Node &other);
    bool operator>(const Node &rhs);
    bool operator<(const Node &rhs);
    bool operator>=(const Node &rhs);
    bool operator<=(const Node &rhs);
    bool operator==(const Node &rhs);
};

#endif // NODE_H

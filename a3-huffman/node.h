#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node
{
public:
    Node();
    Node(Node* L, Node* R);
    ~Node();

    int count;
    unsigned char symbol;
    Node* left;
    Node* right;

    bool operator > (const Node &) const;
    bool operator < (const Node &) const;
};

#endif // NODE_H

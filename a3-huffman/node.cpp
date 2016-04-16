#include "node.h"

Node::Node()
{
    left = NULL;
    right = NULL;
    symbol = 0;
    count = 0;
}

Node::Node(Node *L, Node *R){
    symbol = 0;
    left = L;
    right = R;
    count = L->count + R->count;
}

bool Node::operator >(const Node & right)const{
    return count > right.count;
}

bool Node::operator <(const Node & right)const{
    return count < right.count;
}

Node::~Node()
{

}

#include "Node.h"

Node::Node() {
    //ctor
}

Node::Node(std::string _word, unsigned int _n1, unsigned int _n2) {
    word = _word;
    n1 = _n1;
    n2 = _n2;
}

Node::~Node() {
    //dtor
}

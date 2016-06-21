#include "../include/Node.h"

Node::Node() {
    //ctor
    left = NULL;
    right = NULL;
}

Node::Node(std::string _word) {
    distance = -1;
    word = _word;
    left = NULL;
    right = NULL;
}

Node::Node(unsigned int _distance, std::string _word) {
    distance = _distance;
    word = _word;
    left = NULL;
    right = NULL;
}

Node::~Node() {
    //dtor
    // delete left;
    // delete right;
}

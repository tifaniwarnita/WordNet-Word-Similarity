#include "../include/BinaryTree.h"
#include <iostream>

BinaryTree::BinaryTree()
{
    //ctor
    depth = 0;
    root = NULL;
}

BinaryTree::~BinaryTree()
{
    //dtor
    destroyTree();
}

void BinaryTree::insert(Node *newNode) {
    if (root != NULL) {
        insert(newNode, root);
    } else {
        root = newNode;
    }
}

Node *BinaryTree::search(std::string word) {
    return search(word, root);
}

void BinaryTree::destroyTree() {
    destroyTree(root);
}

void BinaryTree::printTree() {
    printTree(root);
}

void BinaryTree::destroyTree(Node *leaf) {
    if (leaf != NULL) {
        destroyTree(leaf->getLeft());
        destroyTree(leaf->getRight());
        delete leaf;
    }
}

void BinaryTree::insert(Node *newNode, Node *leaf) {
    if (newNode->getWord().compare(leaf->getWord()) < 0) {
        if (leaf->getLeft() != NULL) {
            insert(newNode, leaf->getLeft());
        } else {
            leaf->setLeft(newNode);
        }
    } else {
        if (leaf->getRight() != NULL) {
            insert(newNode, leaf->getRight());
        } else {
            leaf->setRight(newNode);
        }
    }
}

Node *BinaryTree::search(std::string word, Node *leaf) {
    if (leaf != NULL) {
        if (word.compare(leaf->getWord()) == 0) {
            return leaf;
        } else if (word.compare(leaf->getWord()) < 0) {
            return search(word, leaf->getLeft());
        } else {
            return search(word, leaf->getRight());
        }
    } else {
        return NULL;
    }
}

void BinaryTree::printTree(Node *leaf) {
    if (leaf != NULL) {
        std::cout << leaf->getWord() << ": ";
        if (leaf->getLeft() != NULL) {
            std::cout << leaf->getLeft()->getWord() << " ";
        } else {
            std::cout << "- ";
        }
        if (leaf->getRight() != NULL) {
            std::cout << leaf->getRight()->getWord() << std::endl;
        } else {
            std::cout << "-" << std::endl;
        }
        printTree(leaf->getLeft());
        printTree(leaf->getRight());
    }
}

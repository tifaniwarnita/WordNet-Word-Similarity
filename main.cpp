#include <iostream>

#include "include/BinaryTree.h"
#include "include/DatabaseHandler.h"
#include "include/Node.h"
#include "WordNetTree.h"

using namespace std;

int main()
{
    string s1 = "tomato", s2 = "carrot";
    if (!DatabaseHandler::initializeConnection())
        return (1);

    // Synsets *s = DatabaseHandler::searchHypernym(0, s1);
    // s->printSynsets();
    WordNetTree tree = WordNetTree(s1, s2);
    //tree.printTree();

    return 0;
}

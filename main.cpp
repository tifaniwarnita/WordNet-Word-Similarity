#include <iostream>

#include "include/BinaryTree.h"
#include "include/DatabaseHandler.h"
#include "include/Node.h"
#include "WordNetTree.h"

using namespace std;

int main()
{
    string s1 = "graveyard", s2 = "cemetery";
    if (!DatabaseHandler::initializeConnection())
        return (1);
    cout << "First word: ";
    cin >> s1;
    cout << "Second word: ";
    cin >> s2;

    cout << endl;
    WordNetTree tree = WordNetTree(s1, s2);
    bool found = tree.constructTree();
    cout << endl << "=====================================" << endl << endl;

    if (found) {
        cout << "LSO word: " << tree.getLSOWord() << endl;
        cout << "Common meaning(s): " << endl << DatabaseHandler::getDefinition(tree.getLSOWord()) << endl;
        cout << endl;

        cout << "N1 = " << tree.getN1() << endl;
        cout << "N2 = " << tree.getN2() << endl;
        cout << "N3 = " << tree.getN3() << endl;
        cout << "Similarity: " << tree.computeSimilarity() << endl;
    } else {
        cout << "Word not found" << endl;
    }

    return 0;
}

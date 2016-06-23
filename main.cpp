#include <iostream>
#include <vector>

#include "include/DatabaseHandler.h"
#include "include/SynsetTree.h"
#include "WordNetTree.h"

using namespace std;

int main()
{
    string w1 = "cat", w2 = "feline";
    if (!DatabaseHandler::initializeConnection())
        return (1);

    cout << "First word : ";
    cin >> w1;
    cout << "Second word: ";
    cin >> w2;
    SynsetTree tree = SynsetTree(w1, w2);
    tree.printSynsetTree();
    cout << endl << "=====================================" << endl << endl;

    cout << "W1: " << w1 << endl;
    cout << "W2: " << w2 << endl << endl;
    tree.printLSO();

    /* cout << "First word: ";
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
    } */

    return 0;
}

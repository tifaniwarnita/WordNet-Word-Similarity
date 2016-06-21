#include <iostream>

#include "include/BinaryTree.h"
#include "include/DatabaseHandler.h"
#include "include/Node.h"

using namespace std;

int main()
{
    /* cout << "Hello world!" << endl;

    string s1 = "a";
    string s2 = "b";

    cout << s1;
    if (s1.compare(s2) == 0) cout << " = ";
    else if (s1.compare(s2) < 0) cout << " < ";
    else if (s1.compare(s2) > 0) cout << " > ";
    cout << s2 << endl;

    BinaryTree b;
    Node n1 = Node("kucing");
    Node n2 = Node("meong");
    Node n3 = Node("bubu");
    Node n4 = Node("caca");
    Node n5 = Node("lala");
    b.insert(&n1);
    b.insert(&n2);
    b.insert(&n3);
    b.insert(&n4);
    b.insert(&n5);
    b.printTree();
    cout << "Search:" << endl;
    Node *ns = b.search("bubu");
    if (ns != NULL) {
        cout << "depth: " << ns->getDistance() << "; word: " << ns->getWord() << endl;
    } else {
        cout << "not found" << endl;
    }*/
    string s1 = "horse";
    if (!DatabaseHandler::initializeConnection())
        return (1);

    vector<Node> result = DatabaseHandler::searchHypernym(s1);
    /* for(std::vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
        cout << *it << " ";
    }

    BinaryTree b;
    b.insert(result);
    b.printTree();*/
    cout << endl;

    return 0;
}

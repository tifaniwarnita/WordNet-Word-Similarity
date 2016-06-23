#include "Node.h"

Node::Node() {
    //ctor
}

Node::Node(std::string _synset, unsigned int _n1, unsigned int _n2) {
    synset = _synset;
    n1 = _n1;
    n2 = _n2;
    computeSimilarity();
    definition = DatabaseHandler::getDefinitionOfSynset(synset);
}

Node::~Node() {
    //dtor
}

void Node::computeSimilarity() {
    n3 = 0;
    std::vector<std::string> hypernyms = DatabaseHandler::searchHypernyms(synset);
    while (hypernyms.size() > 0) {
        n3++;
        std::string searchSynset = hypernyms.at(0);
        // std::cout << n3 << ": " << searchSynset << std::endl ;
        hypernyms = DatabaseHandler::searchHypernyms(searchSynset);
    }
    similarity = (float) 2 * n3 / (float) (n1 + n2 + 2 * n3);
}

void Node::printNode() {
    std::cout << "Node      : " << synset << std::endl;
    std::cout << "N1        : " << n1 << std::endl;
    std::cout << "N2        : " << n2 << std::endl;
    std::cout << "N3        : " << n3 << std::endl;
    std::cout << "Definition: " << definition << std::endl;
    std::cout << std::setprecision(5) << std::fixed;
    std::cout << "Similarity: " << similarity << std::endl;
}

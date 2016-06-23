#include "SynsetTree.h"

SynsetTree::SynsetTree() {
    //ctor
    lsoWord = "";
    n1 = -1;
    n2 = -1;
    n3 = -1;
}

SynsetTree::SynsetTree(std::string _word1, std::string _word2) {
    word1 = _word1;
    word2 = _word2;
    lsoWord = "";
    n1 = -1;
    n2 = -1;
    n3 = -1;

    std::vector<std::string> synset1 = DatabaseHandler::searchSynsets(word1);
    for(std::vector<std::string>::iterator it = synset1.begin(); it != synset1.end(); ++it) {
        branch1.insert( branch1.end(), std::pair<std::string, int>((*it), 1) );
        std::cout << "[1][1] " << (*it) << std::endl;
    }
    std::vector<std::string> synset2 = DatabaseHandler::searchSynsets(word2);
    for(std::vector<std::string>::iterator it = synset2.begin(); it != synset2.end(); ++it) {
        branch2.insert( branch2.end(), std::pair<std::string, int>((*it), 1) );
        std::cout << "[2][1] " << (*it) << std::endl;
    }
    constructTree();
}

SynsetTree::~SynsetTree(){
    //dtor
}

void SynsetTree::printSynsetTree() {
    std::cout << "Word 1" << std::endl;
    for(std::unordered_map<std::string, int>::iterator it = branch1.begin(); it != branch1.end(); ++it) {
        std::cout << "[" << it->second << "] " << it->first << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Word 2" << std::endl;
    for(std::unordered_map<std::string, int>::iterator it = branch2.begin(); it != branch2.end(); ++it) {
        std::cout << "[" << it->second << "] " << it->first << std::endl;
    }
}

void SynsetTree::constructTree() {
    std::unordered_map<std::string, int>::iterator it1 = branch1.begin();
    std::unordered_map<std::string, int>::iterator it2 = branch2.begin();
    /* while(n1 < 0 || it1->second <= (n1+n2) || it2->second <= (n1+n2)) {
        // loop when lso not found
    } */
    while(it1 != branch1.end()) { //} || it2 != branch2.end()) {
        // begin with 1st branch
        std::cout << "Branch1 size: " << branch1.size() << std::endl;
        if (it1 != branch1.end()) {
            // find any lso
            std::unordered_map<std::string, int> similar = similarSynsets(it1->first, branch1);
            if (similar.size() > 0) {
                for(std::unordered_map<std::string, int>::iterator it = branch2.begin(); it != branch2.end(); ++it) {
                    lsoNodes.push_back(Node(it->first, it1->second, it->second));
                    std::cout << "Found similar : [1][" << it1->second << "] " << it1->first << " with ";
                    std::cout << "[2][" << it->second << "] " << it->first << std::endl;
                }
            } else {
                std::cout << "Not similar   : [1][" << it1->second << "] " << it1->first << std::endl;
            }
            // search the hypernyms of current synset
            std::vector<std::string> synset1 = DatabaseHandler::searchHypernyms(it1->first);
            for(std::vector<std::string>::iterator it = synset1.begin(); it != synset1.end(); ++it) {
                std::unordered_map<std::string, int>::iterator result = branch1.insert( branch1.end(), std::pair<std::string, int>((*it), it1->second + 1) );
                if (result->second > it1->second + 1) {
                    branch1[(*it)] = it1->second + 1;
                    std::cout << "Replace       : [1][" << (it1->second + 1) << "] " << (*it) << std::endl;
                } else {
                    std::cout << "Add to map    : [1][" << (it1->second + 1)<< "] " << (*it) << std::endl;
                }
            }
            ++it1;
        }

        // move to 2nd branch

    }
}

std::unordered_map<std::string, int> SynsetTree::similarSynsets(std::string word, std::unordered_map<std::string, int> wordList) {
    std::unordered_map<std::string, int> result;
    for(std::unordered_map<std::string, int>::iterator it = branch2.begin(); it != branch2.end(); ++it) {
        if (word.compare(it->first) == 0) {
            result[it->first] = it->second;
        }
    }
    return result;
}


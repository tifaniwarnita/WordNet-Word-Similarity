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
        branch1[(*it)] = 0;
        synsets1.push_back((*it));
        std::cout << "[1][1] " << (*it) << std::endl;
    }
    std::cout << std::endl;
    std::vector<std::string> synset2 = DatabaseHandler::searchSynsets(word2);
    for(std::vector<std::string>::iterator it = synset2.begin(); it != synset2.end(); ++it) {
        branch2[(*it)] = 0;
        synsets2.push_back((*it));
        std::cout << "[2][1] " << (*it) << std::endl;
    }
    constructTree();
}

SynsetTree::~SynsetTree(){
    //dtor
}

void SynsetTree::printSynsetTree() {
    std::cout << "Word 1" << std::endl;
    for(std::map<std::string, int>::iterator it = branch1.begin(); it != branch1.end(); ++it) {
        std::cout << "[" << it->second << "] " << it->first << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Word 2" << std::endl;
    for(std::map<std::string, int>::iterator it = branch2.begin(); it != branch2.end(); ++it) {
        std::cout << "[" << it->second << "] " << it->first << std::endl;
    }
}

void SynsetTree::printLSO() {
    if (lsoNodes.size() > 0) {
        Node minimum = lsoNodes.at(0);
        for(unsigned int i=1; i<lsoNodes.size(); ++i) {
            if ((minimum.getN1() + minimum.getN2()) > lsoNodes.at(i).getN1() + lsoNodes.at(i).getN2()) {
            // if (minimum.getSimilarity() < lsoNodes.at(i).getSimilarity()) {
                minimum = lsoNodes.at(i);
            }
        }
        minimum.computeSimilarity();
        std::cout << "=== Minimum LSO " << std::endl;
        minimum.printNode();
    } else {
        std::cout << "=== No LSO found" << std::endl;
        std::cout << std::setprecision(5) << std::fixed;
        std::cout << "Similarity: " << float(0) << std::endl;
    }
}

void SynsetTree::constructTree() {
    unsigned int it1 = 0;
    unsigned int it2 = 0;
    while(it1 < synsets1.size() || it2 < synsets2.size()) {
        // begin with 1st branch
        std::cout << "Branch1 size: " << branch1.size() << std::endl;
        std::cout << "Synset1 size: " << synsets1.size() << std::endl;
        if (it1 < synsets1.size()) {
            // find any lso
            std::cout << "Finding " << synsets1.at(it1) << std::endl;
            std::map<std::string, int>::iterator itvec1 = branch1.find(synsets1.at(it1));
            std::map<std::string, int> similar1 = similarSynsets(itvec1->first, branch2);
            if (similar1.size() > 0) {
                for(std::map<std::string, int>::iterator it = similar1.begin(); it != similar1.end(); ++it) {
                    std::cout << "From branch 1" << std::endl;
                    lsoNodes.push_back(Node(it->first, itvec1->second, it->second));
                    std::cout << "Found similar : [1][" << itvec1->second << "] " << itvec1->first << " with ";
                    std::cout << "[2][" << it->second << "] " << it->first << std::endl;
                }
            } else {
                std::cout << "Not similar   : [1][" << itvec1->second << "] " << itvec1->first << std::endl;
            }
            // search the hypernyms of current synset
            std::vector<std::string> synset1 = DatabaseHandler::searchHypernyms(itvec1->first);
            for(std::vector<std::string>::iterator it = synset1.begin(); it != synset1.end(); ++it) {
                std::map<std::string, int>::iterator result1 = branch1.find((*it));
                if (result1 == branch1.end()) { // not found, add new
                    branch1.insert( std::pair<std::string, int>((*it), itvec1->second + 1) );
                    synsets1.push_back((*it));
                    std::cout << "Add to map    : [1][" << (itvec1->second + 1)<< "] " << (*it) << std::endl;
                } else { // found, check the distance
                    if (result1->second > itvec1->second + 1) {
                        branch1[(*it)] = itvec1->second + 1;
                        std::cout << "Replace       : [1][" << (itvec1->second + 1) << "] " << (*it) << std::endl;
                    } else {
                        std::cout << "Same          : [1][" << result1->second << "] " << (*it) << std::endl;
                    }
                }
            }
            it1++;
        }

        // move to 2nd branch
        if (it2 < synsets2.size()) {
            // find any lso
            std::cout << "Finding " << synsets2.at(it2) << std::endl;
            std::map<std::string, int>::iterator itvec2 = branch2.find(synsets2.at(it2));
            std::map<std::string, int> similar2 = similarSynsets(itvec2->first, branch1);
            if (similar2.size() > 0) {
                for(std::map<std::string, int>::iterator it = similar2.begin(); it != similar2.end(); ++it) {
                    std::cout << "From branch 2" << std::endl;
                    lsoNodes.push_back(Node(it->first, itvec2->second, it->second));
                    std::cout << "Found similar : [1][" << itvec2->second << "] " << itvec2->first << " with ";
                    std::cout << "[2][" << it->second << "] " << it->first << std::endl;
                }
            } else {
                std::cout << "Not similar   : [1][" << itvec2->second << "] " << itvec2->first << std::endl;
            }
            // search the hypernyms of current synset
            std::vector<std::string> synset2 = DatabaseHandler::searchHypernyms(itvec2->first);
            for(std::vector<std::string>::iterator it = synset2.begin(); it != synset2.end(); ++it) {
                std::map<std::string, int>::iterator result2 = branch2.find((*it));
                if (result2 == branch2.end()) { // not found, add new
                    branch2.insert( std::pair<std::string, int>((*it), itvec2->second + 1) );
                    synsets2.push_back((*it));
                    std::cout << "Add to map    : [1][" << (itvec2->second + 1)<< "] " << (*it) << std::endl;
                } else { // found, check the distance
                    if (result2->second > itvec2->second + 1) {
                        branch2[(*it)] = itvec2->second + 1;
                        std::cout << "Replace       : [1][" << (itvec2->second + 1) << "] " << (*it) << std::endl;
                    } else {
                        std::cout << "Same          : [1][" << result2->second << "] " << (*it) << std::endl;
                    }
                }
            }
            it2++;
        }
    }
    std::cout << std::endl << std::endl << std::endl;
}

std::map<std::string, int> SynsetTree::similarSynsets(std::string word, std::map<std::string, int> wordList) {
    std::map<std::string, int> result;
    for(std::map<std::string, int>::iterator it = wordList.begin(); it != wordList.end(); ++it) {
        if (word.compare(it->first) == 0) {
            result[it->first] = it->second;
        }
    }
    return result;
}


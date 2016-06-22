#include "WordNetTree.h"

WordNetTree::WordNetTree() {
    //ctor
}

WordNetTree::WordNetTree(std::string word1, std::string word2) {
    synsets1.push_back(Synsets(0, word1));
    synsets2.push_back(Synsets(0, word2));
    constructTree();
}

WordNetTree::~WordNetTree() {
    //dtor
}

void WordNetTree::constructTree() {
    bool found = false; // variable found indicate whether the lso of two words has been found or not
    std::vector<Synsets>::iterator itSynsets1 = synsets1.begin();
    std::vector<Synsets>::iterator itSynsets2 = synsets2.begin();
    Synsets s1 = (*itSynsets1);
    Synsets s2 = (*itSynsets2);
    std::set<std::string> m1 = s1.getMember();
    std::set<std::string> m2 = s2.getMember();
    std::set<std::string>::iterator itMember1 = m1.begin();
    std::set<std::string>::iterator itMember2 = m2.begin();
    std::string w1 = (*itMember1);
    std::string w2 = (*itMember2);
    std::map<std::string, Synsets> intersection;

    // check the two words
    if (w1.compare(w2) == 0) {
        found = true;
        lsoWord = w1;
        n1 = 0;
        n2 = 0;
    }

    // find the hypernyms if not found yet
    while (!found && (itSynsets1 != synsets1.end() && (itSynsets2 != synsets2.end()))) {
        std::cout << "--not found" << std::endl;
        // expand check the first synsets
        // search the hypernym of first word
        if (itMember1 != m1.end()) {
            std::cout << "--check 1st synsets" << std::endl;
            w1 = (*itMember1);
            Synsets s1New = DatabaseHandler::searchHypernym(s1.getLevel() + 1, w1);
            synsets1.push_back(s1New);
            intersection = findIntersection(s1New, synsets2);
            if (intersection.size() > 0) {
                found = true;
                lsoWord = (intersection.begin())->first;
                n1 = s1New.getLevel();
                n2 = intersection[lsoWord].getLevel();
            } else {
                // not found, should expand and check the second synsets
                // first, move the pointer of first synsets
                std::cout << "--1st synset: not found" << std::endl;
                itMember1++;
                std::cout << "--itMember1++" << std::endl;
                if (itMember1 == m1.end()) {
                    itSynsets1++;
                    if (itSynsets1 != synsets1.end()) {
                        m1 = s1.getMember();
                        itMember1 = m1.begin();
                    }
                }
            }
        }
        // search the hypernym of second word
        if (!found && itMember2 != m2.end()) {
            std::cout << "--check 2nd synsets" << std::endl;
            w2 = (*itMember2);
            Synsets s2New = DatabaseHandler::searchHypernym(s2.getLevel() + 1, w2);
            synsets2.push_back(s2New);
            intersection = findIntersection(s2New, synsets1);
            if (intersection.size() > 0) {
                found = true;
                lsoWord = (intersection.begin())->first;
                n1 = intersection[lsoWord].getLevel();
                n2 = s2New.getLevel();
            } else {
                // not found, move the pointer of second synsets
                std::cout << "--2nd synset: not found" << std::endl;
                itMember2++;
                if (itMember2 == m2.end()) {
                    itSynsets2++;
                    if (itSynsets2 != synsets2.end()) {
                        m2 = s2.getMember();
                        itMember2 = m2.begin();
                    }
                }
            }
        }
    }

    printTree();
    if (found) {
        std::cout << "FOUND!" << std::endl;
        std::cout << "lso word: " << lsoWord << std::endl;
        std::cout << "n1: " << n1 << std::endl;
        std::cout << "n2: " << n2 << std::endl;
    }
}

void WordNetTree::printTree() {
    std::cout << "Synset 1" << std::endl;
    for(std::vector<Synsets>::iterator it = synsets1.begin(); it != synsets1.end(); ++it) {
        Synsets s = (Synsets) *it;
        s.printSynsets();
    }
    std::cout << std::endl;
    std::cout << "Synset 2" << std::endl;
    for(std::vector<Synsets>::iterator it = synsets2.begin(); it != synsets2.end(); ++it) {
        Synsets s = (Synsets) *it;
        s.printSynsets();
    }
}

int WordNetTree::isMember(std::string word, std::vector<Synsets> synsets) {
    bool isMember = false;
    std::vector<Synsets>::iterator it = synsets.begin();
    while(!isMember && it != synsets.end()) {
        Synsets s = (*it);
        std::set<std::string> m = s.getMember();
        if (m.find(word) != m.end()) {
            isMember = true;
        } else {
            it++;
        }
    }
    if (isMember)  {
        return (*it).getLevel();
    } else {
        return -1;
    }
}

std::map<std::string, Synsets> WordNetTree::findIntersection(Synsets synset, std::vector<Synsets> synsets) {
    bool found = false;
    std::vector<Synsets>::iterator it = synsets.begin();
    Synsets s2 = (*it);
    std::set<std::string> m1 = synset.getMember();
    std::set<std::string> m2 = s2.getMember();
    std::set<std::string> intersection;
    while (!found && it != synsets.end()) {
        s2 = (*it);
        std::set<std::string> m2 = s2.getMember();
        std::set_intersection(m1.begin(), m1.end(),
                              m2.begin(), m2.end(),
                              std::inserter(intersection, intersection.begin()));
        if (intersection.size() > 0) {
            found = true;
        } else {
            it++;
        }
    }
    std::map<std::string, Synsets> retval;
    if (found)  {
        std::string word = (*intersection.begin());
        retval[word] = (*it);
        return retval;
    } else {
        return retval;
    }
}

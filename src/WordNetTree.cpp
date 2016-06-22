#include "WordNetTree.h"

WordNetTree::WordNetTree() {
    //ctor
}

WordNetTree::WordNetTree(std::string word1, std::string word2) {
    synsets1.push_back(Synsets(0, word1));
    synsets2.push_back(Synsets(0, word2));
}

WordNetTree::~WordNetTree() {
    //dtor
}

bool WordNetTree::constructTree() {
    bool found = false; // variable found indicate whether the lso of two words has been found or not
    unsigned int itSynsets1 = 0;
    unsigned int itSynsets2 = 0;
    Synsets s1 = synsets1.at(itSynsets1);
    Synsets s2 = synsets2.at(itSynsets2);
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
    while (!found && (itSynsets1 < synsets1.size() && (itSynsets2 < synsets2.size()))) {
        // expand check the first synsets
        // search the hypernym of first word
        if (itMember1 != m1.end()) {
            w1 = (*itMember1);
            Synsets s1New = DatabaseHandler::searchHypernym(s1.getLevel() + 1, w1);
            if (s1New.getMember().size() == 0) break; // word not found
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
                ++itMember1;
                if (itMember1 == m1.end()) {
                    ++itSynsets1;
                    if (itSynsets1 < synsets1.size()) {
                        s1 = synsets1.at(itSynsets1);
                        m1 = s1.getMember();
                        itMember1 = m1.begin();
                    }
                }
            }
        }
        // search the hypernym of second word
        if (!found && itMember2 != m2.end()) {
            w2 = (*itMember2);
            Synsets s2New = DatabaseHandler::searchHypernym(s2.getLevel() + 1, w2);
            if (s2New.getMember().size() == 0) break; // word not found
            synsets2.push_back(s2New);
            intersection = findIntersection(s2New, synsets1);
            if (intersection.size() > 0) {
                found = true;
                lsoWord = (intersection.begin())->first;
                n1 = intersection[lsoWord].getLevel();
                n2 = s2New.getLevel();
            } else {
                // not found, move the pointer of second synsets
                itMember2++;
                if (itMember2 == m2.end()) {
                    itSynsets2++;
                    if (itSynsets2 < synsets2.size()) {
                        s2 = synsets2.at(itSynsets2);
                        m2 = s2.getMember();
                        itMember2 = m2.begin();
                    }
                }
            }
        }
    }

    std::cout << std::endl;
    printTree();
    if (found) {
        n3 = findDistanceToRoot(lsoWord);
    }
    return found;
}

float WordNetTree::computeSimilarity() {
    return (float) 2 * n3 / (float) (n1 + n2 + 2 * n3);
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
    std::cout << std::endl;
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

int WordNetTree::findDistanceToRoot(std::string word) {
    Synsets s = Synsets(0, word);
    std::cout << "Find distance to root:" << std::endl;
    s.printSynsets();
    while (s.getMember().size() > 0) {
        int nextLevel = s.getLevel() + 1;
        std::string nextWord = (*s.getMember().begin());
        s = DatabaseHandler::searchHypernym(nextLevel, nextWord);
        s.printSynsets();
    }
    return s.getLevel()-1;
}

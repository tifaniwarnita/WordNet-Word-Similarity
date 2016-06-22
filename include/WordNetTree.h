#ifndef WORDNETTREE_H
#define WORDNETTREE_H

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include "DatabaseHandler.h"
#include "Synsets.h"

class WordNetTree
{
    public:
        /** Constructors and Destructor */
        WordNetTree();
        WordNetTree(std::string word1, std::string word2);
        virtual ~WordNetTree();

        /** Getters and setters */
        std::vector<Synsets> getSynsets1() { return synsets1; }
        void setSynsets1(std::vector<Synsets> val) { synsets1 = val; }
        std::vector<Synsets> getSynsets2() { return synsets2; }
        void setSynsets2(std::vector<Synsets> val) { synsets2 = val; }

        /** Other operations */
        void constructTree();
        void printTree();

    protected:

    private:
        int isMember(std::string word, std::vector<Synsets> synsets);
        std::map<std::string, Synsets> findIntersection(Synsets synset, std::vector<Synsets> synsets);

        std::vector<Synsets> synsets1; //!< Member variable "synsets1"
        std::vector<Synsets> synsets2; //!< Member variable "synsets2"
        std::string lsoWord;
        unsigned int n1;
        unsigned int n2;
        unsigned int n3;
};

#endif // WORDNETTREE_H

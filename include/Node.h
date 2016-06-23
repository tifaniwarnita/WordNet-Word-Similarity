#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "DatabaseHandler.h"

class Node {
    public:
        /** Constructors and Destructor */
        Node();
        Node(std::string _synset, unsigned int _n1, unsigned int _n2);
        virtual ~Node();

        /** Getters and setters */
        std::string getSynset() { return synset; }
        void setSynset(std::string val) { synset = val; }
        std::string getDefinition() { return definition; }
        void setDefinition(std::string val) { definition = val; }
        unsigned int getN1() { return n1; }
        void setN1(unsigned int val) { n1 = val; }
        unsigned int getN2() { return n2; }
        void setN2(unsigned int val) { n2 = val; }
        unsigned int getN3() { return n3; }
        void setN3(unsigned int val) { n3 = val; }
        float getSimilarity() { return similarity; }
        void setSimilarity(float val) { similarity = val; }

        void computeSimilarity();
        void printNode();
    protected:

    private:
        std::string synset;
        std::string definition;
        unsigned int n1;
        unsigned int n2;
        unsigned int n3;
        float similarity;
};

#endif // NODE_H

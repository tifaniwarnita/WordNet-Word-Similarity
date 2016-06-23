#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
    public:
        /** Constructors and Destructor */
        Node();
        Node(std::string _word, unsigned int _n1, unsigned int _n2);
        virtual ~Node();

        /** Getters and setters */
        std::string getWord() { return word; }
        void setWord(std::string val) { word = val; }
        unsigned int getN1() { return n1; }
        void setN1(unsigned int val) { n1 = val; }
        unsigned int getN2() { return n2; }
        void setN2(unsigned int val) { n2 = val; }
        unsigned int getN3() { return n3; }
        void setN3(unsigned int val) { n3 = val; }
        float getSimilarity() { return similarity; }
        void setSimilarity(float val) { similarity = val; }

    protected:

    private:
        std::string word;
        unsigned int n1;
        unsigned int n2;
        unsigned int n3;
        float similarity;
};

#endif // NODE_H

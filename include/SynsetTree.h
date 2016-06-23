#ifndef SYNSETTREE_H
#define SYNSETTREE_H

#include <iomanip>
#include <map>
#include <string>
#include <vector>

#include "DatabaseHandler.h"
#include "Node.h"

class SynsetTree
{
    public:
        /** Constructors and Destructor */
        SynsetTree();
        SynsetTree(std::string _word1, std::string _word2);
        virtual ~SynsetTree();

        /** Getters and setters */
        std::string getLSOWord() { return lsoWord; }
        void setLSOWord(std::string val) { lsoWord = val; }
        int getN1() { return n1; }
        void setN1(int val) { n1 = val; }
        int getN2() { return n2; }
        void setN2(int val) { n2 = val; }
        int getN3() { return n3; }
        void setN3(int val) { n3 = val; }
        float getSimilarity() { return similarity; }
        void setSimilarity(float val) { similarity = val; }
        std::string getWord1() { return word1; }
        void setWord1(std::string val) { word1 = val; }
        std::string getWord2() { return word2; }
        void setWord2(std::string val) { word2 = val; }
        std::map<std::string, int> getBranch1() { return branch1; }
        void setBranch1(std::map<std::string, int> val) { branch1 = val; }
        std::map<std::string, int> getBranch2() { return branch2; }
        void setBranch2(std::map<std::string, int> val) { branch2 = val; }

        /** Other operations */
        void printSynsetTree();
        void printLSO();
    protected:

    private:
        void constructTree();
        std::map<std::string, int> similarSynsets(std::string word, std::map<std::string, int> wordList);

        std::string lsoWord;
        int n1;
        int n2;
        int n3;
        float similarity;

        std::vector<Node> lsoNodes;
        std::string word1;
        std::string word2;
        std::map<std::string, int> branch1;
        std::map<std::string, int> branch2;
        std::vector<std::string> synsets1;
        std::vector<std::string> synsets2;
};

#endif // SYNSETTREE_H

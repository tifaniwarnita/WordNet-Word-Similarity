#ifndef SYNSETS_H
#define SYNSETS_H

#include <iostream>
#include <set>
#include <string>

class Synsets {
public:
    /** Constructors and Destructor */
    Synsets();
    Synsets(unsigned int _level);
    Synsets(unsigned int _level, std::string word);
    virtual ~Synsets();

    /** Getters and Setters */
    unsigned int getLevel() { return level; }
    void setLevel(unsigned int val) { level = val; }
    std::set<std::string> getMember() { return member; }
    void addMember(std::string word) { member.insert(word); }
    bool isMember(std::string word) { member.find(word) != member.end(); }
    void printSynsets();

protected:

private:
    unsigned int level; //!< Member variable "level"
    std::set<std::string> member; //!< Member variable "member"
};

#endif // SYNSETS_H

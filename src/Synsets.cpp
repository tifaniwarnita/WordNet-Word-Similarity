#include "../include/Synsets.h"

Synsets::Synsets() {
    //ctor
}

Synsets::Synsets(unsigned int _level) {
    level = _level;
}

Synsets::Synsets(unsigned int _level, std::string word) {
    level = _level;
    member.insert(word);
}

Synsets::~Synsets() {
    //dtor
}

void Synsets::printSynsets() {
    std::cout << "[" << level << "]: ";
    for (std::set<std::string>::iterator it=member.begin(); it!=member.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <cstring>
#include <iostream>
#include <vector>

#include "Synsets.h"
#include "../lib/sqlite3.h"

class DatabaseHandler {
public:
    /** Default constructor */
    DatabaseHandler();
    /** Default destructor */
    virtual ~DatabaseHandler();

    static bool initializeConnection();
    static Synsets searchHypernym(unsigned int level, std::string word);
    static std::string getDefinition(std::string word);
    static std::string getDefinitionOfSynset(std::string synset);

    static std::vector<std::string> searchSynsets(std::string word);
    static std::vector<std::string> searchHypernyms(std::string synsetId);
protected:

private:
    static int callbackHypernym(void *data, int argc, char **argv, char** azColName);
    static int callbackDefinition(void *data, int argc, char **argv, char** azColName);

    static int callbackFunction(void *data, int argc, char **argv, char** azColName);

    static const std::string DB_PATH;
    static const std::string DB_NAME;
    static sqlite3 *db;
    static int rc;
    static Synsets result;
    static std::string resultString;
    static std::vector<std::string> queryResult;
};

#endif // DATABASEHANDLER_H

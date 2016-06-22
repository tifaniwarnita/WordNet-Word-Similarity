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
protected:

private:
    static int callback(void *data, int argc, char **argv, char** azColName);

    static const std::string DB_PATH;
    static const std::string DB_NAME;
    static sqlite3 *db;
    static int rc;
    static Synsets result;
};

#endif // DATABASEHANDLER_H

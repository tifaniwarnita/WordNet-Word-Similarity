#include "DatabaseHandler.h"

const std::string DatabaseHandler::DB_PATH = "db/";
const std::string DatabaseHandler::DB_NAME = "sqlite-31.db";

std::vector<std::string> DatabaseHandler::result;
sqlite3 *DatabaseHandler::db;
int DatabaseHandler::rc;

int DatabaseHandler::callback(void *data, int argc, char **argv, char** azColName) {
    for(int i=0; i<argc; i++) {
        if (argv[i])
            result.push_back(argv[i]);
    }
    return 0;
}

DatabaseHandler::DatabaseHandler() {
    //ctor
}

DatabaseHandler::~DatabaseHandler() {
    //dtor
}

bool DatabaseHandler::initializeConnection() {
    result.clear();
    int rc = sqlite3_open_v2(
        (DB_PATH + DB_NAME).c_str(),
        &db,
        SQLITE_OPEN_READONLY,
        NULL);

    if (rc) { // Error occured
        std::cerr << "Can't open database (" << DB_PATH << DB_NAME << "): ";
        std::cerr << sqlite3_errmsg(db) << std::endl;
        return false;
    } else {
        std::cout << "Opened database (" << DB_PATH << DB_NAME << ") successfully" << std::endl;
        return true;
    }
}

std::vector<std::string> DatabaseHandler::searchHypernym(std::string word) {
    result.clear(); // Clear all result from execution before

    std::string sql = "SELECT w2.lemma ";
    sql += " FROM words w1";
    sql += " LEFT JOIN senses se1 ON w1.wordid = se1.wordid";
    sql += " LEFT JOIN synsets sy1 ON se1.synsetid = sy1.synsetid";
    sql += " LEFT JOIN semlinks on sy1.synsetid = semlinks.synset1id";
    sql += " LEFT JOIN synsets sy2 ON semlinks.synset2id = sy2.synsetid";
    sql += " LEFT JOIN senses se2 ON sy2.synsetid = se2.synsetid";
    sql += " LEFT JOIN words w2 on se2.wordid = w2.wordid";
    sql += " WHERE w1.lemma = '";
    sql += word;
    sql += "'";
    sql += " AND sy1.pos = 'n'";
    sql += " AND semlinks.linkid = 1";

    const char *query = sql.c_str();
    const char* data = "Callback function called";
    char *zErrMsg = 0;

    rc = sqlite3_exec(db, query, callback, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Operation done successfully" << std::endl;
    }
    return result;
}

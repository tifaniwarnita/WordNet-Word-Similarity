#include "DatabaseHandler.h"

const std::string DatabaseHandler::DB_PATH = "db/";
const std::string DatabaseHandler::DB_NAME = "sqlite-31.db";

sqlite3 *DatabaseHandler::db;
int DatabaseHandler::rc;
Synsets DatabaseHandler::result;
std::string DatabaseHandler::resultString;
std::vector<std::string> DatabaseHandler::queryResult;

DatabaseHandler::DatabaseHandler() {
    //ctor
}

DatabaseHandler::~DatabaseHandler() {
    //dtor
}

bool DatabaseHandler::initializeConnection() {
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

Synsets DatabaseHandler::searchHypernym(unsigned int level, std::string word) {
    result = Synsets(level);
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
    char *zErrMsg = 0;

    rc = sqlite3_exec(db, query, callbackHypernym, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
    }

    return result;
}

std::string DatabaseHandler::getDefinition(std::string word) {
    resultString = "";
    std::string sql = "SELECT synsets.definition";
    sql += " FROM words JOIN senses on words.wordid = senses.wordid";
    sql += " JOIN synsets ON senses.synsetid = synsets.synsetid";
    sql += " WHERE lemma = '";
    sql += word;
    sql += "';";

    const char *query = sql.c_str();
    char *zErrMsg = 0;

    rc = sqlite3_exec(db, query, callbackDefinition, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {

    }
    return resultString;
}

std::vector<std::string> DatabaseHandler::searchSynsets(std::string word) {
    queryResult.clear();
    std::string sql = "SELECT sy1.synsetid";
    sql += " FROM words w1";
    sql += " LEFT JOIN senses se1 ON w1.wordid = se1.wordid";
    sql += " LEFT JOIN synsets sy1 ON se1.synsetid = sy1.synsetid";
    sql += " WHERE w1.lemma = '";
    sql += word;
    sql += "'";

    const char *query = sql.c_str();
    char *zErrMsg = 0;

    rc = sqlite3_exec(db, query, callbackFunction, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    return queryResult;
}

std::vector<std::string> DatabaseHandler::searchHypernyms(std::string synsetId) {
    queryResult.clear();
    std::string sql = "SELECT sy2.synsetid";
    sql += " FROM synsets sy1";
    sql += " LEFT JOIN semlinks ON sy1.synsetid = semlinks.synset1id";
    sql += " LEFT JOIN synsets sy2 ON semlinks.synset2id = sy2.synsetid";
    sql += " WHERE sy1.synsetid = '";
    sql += synsetId;
    sql += "'";
    sql += " AND sy1.pos = 'n'";
    sql += " AND semlinks.linkid = 1;";

    const char *query = sql.c_str();
    char *zErrMsg = 0;

    rc = sqlite3_exec(db, query, callbackFunction, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    return queryResult;
}


int DatabaseHandler::callbackHypernym(void *data, int argc, char **argv, char** azColName) {
    for(int i=0; i<argc; i++) {
        if (argv[i]) {
            result.addMember(argv[i]);
        }
    }
    return 0;
}

int DatabaseHandler::callbackDefinition(void *data, int argc, char **argv, char** azColName) {
    for(int i=0; i<argc; i++) {
        if (argv[i]) {
            resultString += "- ";
            resultString += argv[i];
            resultString += "\n";
        }
    }
    return 0;
}

int DatabaseHandler::callbackFunction(void *data, int argc, char **argv, char** azColName) {
    for(int i=0; i<argc; i++) {
        if (argv[i]) {
            queryResult.push_back(argv[i]);
        }
    }
    return 0;
}

/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** SqliteDataBase
*/

#include "SqliteDataBase.hpp"

std::stringstream ss;

/**
 * Creates an instance of SqlDataBase.
 */
SqliteDataBase::SqliteDataBase()
{
    int rc = 0;
    rc = sqlite3_open("../Babel_Serveur.db", &_dataBase);
    createTable();
}

SqliteDataBase::~SqliteDataBase()
{
}

SqliteDataBase &SqliteDataBase::getInstance()
{
    static SqliteDataBase instance;
    return instance;
}

// CallBack for Sqlite //

static int callbackCheckUser(void *data, int argc, char **argv, char **azColName)
{
    bool *userExist = (bool *)data;
    if (argc == 0) {
        *userExist = false;
    } else {
        *userExist = true;
    }
    for (int i = 0; i < argc; i++) {
        ss << argv[i] ? argv[i] : "NULL";
        ss << ";";
    }

    return 0;
}

static int callbackCreateUser(void *NotUsed, int argc, char **argv, char **azColName) {
   (void)NotUsed;
   (void)argc;
   (void)argv;
   (void)azColName;
   return 0;
}
// ------------------- //

void SqliteDataBase::createTable()
{
    int rc = 0;
    std::string sqlCommand = "CREATE TABLE TEST("
                             "ID INT PRIMARY KEY     NOT NULL,"
                             "LOGIN          TEXT    NOT NULL,"
                             "PASSWORD       TEXT    NOT NULL,"
                             "CONNECTED      INT     NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(_dataBase, sqlCommand.c_str(), nullptr, nullptr, nullptr);
}

/**
 * Retrieves the data from the global stringstream buffer.
 * It contains the result of the last sql command.
 *
 * It returns a std::string and then purges the stringstream.
 */
std::string SqliteDataBase::getData()
{
    std::string s = ss.str();
    ss.str("");
    if (s.size() <= 0)
        return ("NULL");
    std::cout << "SERVERSQL : " << s << std::endl;
    return (s);
}

/**
 * Check the @param login and @param pass if they match in database.
 * Returns true or false.
 */
bool SqliteDataBase::checkUserValideLogin(const std::string &login, const std::string &pass)
{
    int rc = 0;
    bool check = false;
    std::string chars = "\r\n";
    std::string s = pass;
    for (char c: chars) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }
    std::string sqlCommand = "SELECT Username, Password FROM USER WHERE Username = \"" + login + "\" AND Password = \"" + s + "\"";
    std::cout << sqlCommand << std::endl;

    rc = sqlite3_exec(_dataBase, sqlCommand.c_str(), callbackCheckUser, &check, nullptr);
    return check;
}

/**
 * Check the @param login and @param pass.
 *
 * If they match in database returns false and does nothing.
 * Returns true and creates user if they dont match.
 */
bool SqliteDataBase::createUser(const std::string &login, const std::string &pass)
{
    std::string chars = "\r\n";
    std::string s = pass;
    for (char c: chars) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }
    std::string sqlCommand = "INSERT INTO USER VALUES(\"" + login + "\", \"" + s + "\")";
    int rc = sqlite3_exec(_dataBase, sqlCommand.c_str(), callbackCreateUser, 0, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error couldn't create User shitbag" << std::endl;
        return (false);
    }
    return (true);
}

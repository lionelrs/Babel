/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** SqliteDataBase
*/

#include "SqliteDataBase.hpp"

std::stringstream ss;

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

std::string SqliteDataBase::getData()
{
    std::string s = ss.str();
    ss.clear();
    if (s.size() <= 0)
        return ("NULL");
    return (s);
}

bool SqliteDataBase::checkUserValideLogin(const std::string &login, const std::string &pass)
{
    int rc = 0;
    bool check = false;
    std::string chars = "\r\n";
    std::string s = pass;
    for (char c: chars) {
        s.erase(std::remove(s.begin(), s.end(), c), s.end());
    }
    std::string sqlCommand = "SELECT LOGIN, PASSWORD FROM USERINFO WHERE LOGIN = \"" + login + "\" AND PASSWORD = \"" + s + "\"";
    std::cout << sqlCommand << std::endl;

    rc = sqlite3_exec(_dataBase, sqlCommand.c_str(), callbackCheckUser, &check, nullptr);
    return check;
}

void SqliteDataBase::createUser(const std::string &login, const std::string &mp, const std::string &ip)
{
}

std::string SqliteDataBase::getUserInfo(const std::string &login)
{
    return "";
}

void SqliteDataBase::setUserConnected(const std::string &login, const std::string &ip)
{
}

void SqliteDataBase::setUserDisonnected(const std::string &login)
{
}

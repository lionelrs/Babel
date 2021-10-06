/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** SqliteDataBase
*/

#ifndef SQLITEDATABASE_HPP_
#define SQLITEDATABASE_HPP_

#include "sqlite3.h"

#include <iostream>

class SqliteDataBase
{
private:
    SqliteDataBase();

    // SqliteDataBase(const SqliteDataBase &) = delete;
    // SqliteDataBase &operator=(const SqliteDataBase &) = delete;

    void createTable();

    sqlite3 *_dataBase;

public:
    ~SqliteDataBase();

    static SqliteDataBase &getInstance();

    static bool checkValidPassword(const std::string &login);
    static bool checkUserExist(const std::string &login);

    static void createUser(const std::string &login, const std::string &pass, const std::string &ip);

    static std::string getUserInfo(const std::string &login);
    static std::string getUsersInfo();
    static void setUserConnected(const std::string &login, const std::string &ip);
    static void setUserDisonnected(const std::string &login);

protected:
};

#endif /* !SQLITEDATABASE_HPP_ */
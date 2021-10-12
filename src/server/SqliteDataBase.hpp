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
#include <sstream>
#include <algorithm>

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

    static std::string getData();
    bool checkUserValideLogin(const std::string &login, const std::string &pass);

    bool createUser(const std::string &login, const std::string &pass);

    std::string getUserInfo(const std::string &login);
    std::string getUsersInfo();
    void setUserConnected(const std::string &login, const std::string &ip);
    void setUserDisonnected(const std::string &login);

protected:
};

#endif /* !SQLITEDATABASE_HPP_ */
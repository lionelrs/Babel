/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** User
*/

#include "User.hpp"

User::User(std::string ip, int port, int fd) : _ip(ip), _port(port), _socket(fd)
{
    _isConnected = false;
    _username = "";
}

int User::getSocket() const
{
    return (_socket);
}

void User::disconnect()
{
    this->_socket = 0;
    this->_ip.clear();
    this->_port = 0;
    this->_isConnected = false;
}

void User::login()
{
    this->_isConnected = true;
}

bool User::isConnected() const
{
    return (_isConnected);
}

std::string User::getUserName() const
{
    return (_username);
}
void User::setUserName(std::string username)
{
    _username = username;
}

User::~User()
{
}

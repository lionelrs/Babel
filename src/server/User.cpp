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
    _id = -1;
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

int User::getId() const
{
    return (_id);
}
void User::setId(int id)
{
    _id = id;
}

User::~User()
{
}

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
    _isInCall = false;
    _calling = "";
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

std::string User::getIp() const
{
    return (_ip);
}

void User::login()
{
    this->_isConnected = true;
}

bool User::isConnected() const
{
    return (_isConnected);
}

bool User::isInCall() const
{
    return (_isInCall);
}

std::string User::getUserName() const
{
    return (_username);
}

std::string User::getCalling() const
{
    return (_calling);
}

void User::setUserName(std::string username)
{
    _username = username;
}

void User::setCalling(std::string name)
{
    _calling = name;
}

void User::setIsInCall(bool isInCall)
{
    _isInCall = isInCall;
}

User::~User()
{
}

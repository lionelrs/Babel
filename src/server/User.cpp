/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** User
*/

#include "User.hpp"

/**
 * Creates an instance of User.
 *
 * @param port Specifies his port.
 * @param ip Specifies his ip.
 * @param fd Specifies his socket file descriptor.
 */
User::User(std::string ip, int port, int fd) : _ip(ip), _port(port), _socket(fd)
{
    _isConnected = false;
    _username = "";
    _isInCall = false;
    _calling = "";
}

/**
 * Returns the user's socket.
 */
int User::getSocket() const
{
    return (_socket);
}

/**
 * Disconnects the user.
 */
void User::disconnect()
{
    this->_socket = 0;
    this->_ip.clear();
    this->_port = 0;
    this->_isConnected = false;
}

/**
 * Returns the user's ip.
 */
std::string User::getIp() const
{
    return (_ip);
}

/**
 * Set connection status to true.
 */
void User::login()
{
    this->_isConnected = true;
}

/**
 * Returns the user's status (true or false).
 */
bool User::isConnected() const
{
    return (_isConnected);
}

/**
 * Returns the user's calling status.
 */
bool User::isInCall() const
{
    return (_isInCall);
}

/**
 * Returns the user's username.
 */
std::string User::getUserName() const
{
    return (_username);
}

/**
 * Returns the username of the user in call.
 */
std::string User::getCalling() const
{
    return (_calling);
}

/**
 * Sets the user's username.
 */
void User::setUserName(std::string username)
{
    _username = username;
}

/**
 * Sets the username of the user in call.
 */
void User::setCalling(std::string name)
{
    _calling = name;
}

/**
 * Sets the user's calling status.
 */
void User::setIsInCall(bool isInCall)
{
    _isInCall = isInCall;
}

User::~User()
{
}

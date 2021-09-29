/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(const std::string ip, const int port, QObject *parent) : QObject(parent)
{
}

Socket::~Socket()
{
}

int Socket::getPort() const
{
    return _port;
}

std::string Socket::getIp() const
{
    return _ip;
}

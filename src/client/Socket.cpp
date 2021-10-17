/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Socket
*/

#include "Socket.hpp"

/**
 * Creates an instance of Socket that herited by MyTCP and MyUDP, not to be used by itself.
 *
 * @param ip Specifies the ip of the server that you want to connect to.
 * @param port Specifies the port of the server that you want to connect to.
 * @param parent Parent widget to herit from.
 */
Socket::Socket(const std::string ip, const int port, QObject *parent) : _ip(ip), _port(port), QObject(parent)
{
}

Socket::~Socket()
{
}

/**
 * Getter of the socket port.
 */
int Socket::getPort() const
{
    return _port;
}

/**
 * Getter of the socket ip.
 */
std::string Socket::getIp() const
{
    return _ip;
}

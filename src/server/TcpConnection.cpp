/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Babel singelton
*/

#include "TcpConnection.hpp"

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

TcpConnection::TcpConnection(asio::io_context &io_context)
    : _socket(io_context)
{
}

asio::ip::tcp::socket &TcpConnection::getSocket()
{
    return _socket;
}

void TcpConnection::sendMessage()
{
    _message = "";

    asio::async_write(_socket, asio::buffer("salut copain bienvenue sur le serv ;)"),
                      std::bind(&TcpConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));

    asio::async_read_until(_socket, asio::dynamic_buffer(_message), '\0',
                            std::bind(&TcpConnection::handleRead, shared_from_this(),
                                    std::placeholders::_1,
                                    std::placeholders::_2));
}

void TcpConnection::handleWrite(const asio::error_code &error, size_t size)
{
    std::cout << "le SERVEUR et pret pour parler" << std::endl;
}

void TcpConnection::handleRead(const asio::error_code &error, size_t size)
{
    std::cout << "le clilci a parler: \"";
    std::cout << _message << "\""
            << " de taille=" << size << std::endl
            << std::endl;

    _message = "";

    asio::async_read_until(_socket, asio::dynamic_buffer(_message), '\0',
                            std::bind(&TcpConnection::handleRead, shared_from_this(),
                                    std::placeholders::_1,
                                    std::placeholders::_2));
}
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

void TcpConnection::startComunication()
{
    // _message = "";

    SEPCommands test;
    test.code = 100;
    test.arg1 = "well done !";
    test.arg2 = "";
    test.arg3 = "";

    char buff[sizeof(test)];

    std::memcpy(buff, &test, sizeof(test));

    asio::async_read_until(_socket, _message, "\r\n",
                            std::bind(&TcpConnection::handleRead, shared_from_this(),
                                std::placeholders::_1,
                                std::placeholders::_2));

    asio::async_write(_socket, Serializer::serialize(test),
                        std::bind(&TcpConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));
}

void TcpConnection::handleWrite(const asio::error_code &error, size_t size)
{
    std::cout << "le SERVEUR et pret pour parler" << std::endl;

    asio::async_read_until(_socket, _message, "\r\n",
                            std::bind(&TcpConnection::handleRead, shared_from_this(),
                                    std::placeholders::_1,
                                    std::placeholders::_2));

}

void TcpConnection::handleRead(const asio::error_code &error, size_t size)
{
    if (!error) {
        std::istream is(&_message);
        std::string line;
        std::getline(is, line);
        std::cout << line << std::endl << std::endl;
    }
    std::string sendMessage = "j'ai lue";
    // std::cout << "le clilci a parler: \"";
    // std::cout << _message << "\""
    //         << " de taille=" << size << std::endl
    //         << std::endl;

    asio::async_write(_socket, asio::buffer(sendMessage),
                        std::bind(&TcpConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));
}
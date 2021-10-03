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

void testFunc()
{
    // SEPCommands test= {0};
    // test.code = 100;
    // test.arg1 = "well done !";
    // test.arg2 = "";
    // test.arg3 = "";

    // char buff[sizeof(test) + 1];
    // std::memset(buff, '\0', sizeof(test) + 1);

    // std::memcpy(buff, &test, sizeof(test));

    // asio::mutable_buffer m = Serializer::serialize(test);
    // SEPCommands *coucou = Serializer::unSerialize((char *)m.data());
    // std::cout << coucou->arg1 << std::endl;
}

void TcpConnection::startComunication()
{

    SEPCommands test= {0};
    test.port = 8888;
    test.code = 200;
    std::memset(test.ip, '\0', 5);
    std::strcpy(test.ip, "10.0.127.85");
    char buff[sizeof(test) + 1];
    std::memset(buff, '\0', sizeof(test) + 1);

    std::memcpy(buff, &test, sizeof(test));

    std::cout << ((SEPCommands *)buff)->ip << std::endl;
    asio::async_read_until(_socket, _message, "\r\n",
                            std::bind(&TcpConnection::handleRead, shared_from_this(),
                                std::placeholders::_1,
                                std::placeholders::_2));

    asio::async_write(_socket, asio::buffer(buff),
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
    std::string sendMessage = "j'ai lue\r\n";
    // std::cout << "le clilci a parler: \"";
    // std::cout << _message << "\""
    //         << " de taille=" << size << std::endl
    //         << std::endl;

    asio::async_write(_socket, asio::buffer(sendMessage),
                        std::bind(&TcpConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));
}
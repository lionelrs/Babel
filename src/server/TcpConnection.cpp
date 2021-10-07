/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Babel singelton
*/

#include "TcpConnection.hpp"

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

    asio::async_write(_socket, asio::buffer("Welcome !\r\n"),
                        std::bind(&TcpConnection::handleWrite, shared_from_this(),
                            std::placeholders::_1,
                            std::placeholders::_2));
}

void TcpConnection::handleWrite(const asio::error_code &error, size_t size)
{
    asio::async_read_until(_socket, _message, "\r\n",
                            std::bind(&TcpConnection::handleRead, shared_from_this(),
                                    std::placeholders::_1,
                                    std::placeholders::_2));

}

void TcpConnection::checkCode(std::string &data)
{
    int len = data.length();
    char local_data[len + 1];
    char *token = NULL;
    std::strcpy(local_data, data.c_str());
    token = std::strtok(local_data, " \r\n");
    std::cout << data << std::endl;
    while (token != NULL) {
        token = std::strtok(NULL, " \r\n");
        std::cout << token << std::endl;
    }
}

void TcpConnection::handleRead(const asio::error_code &error, size_t size)
{
    std::string sendMessage = "";
    std::istream is(&_message);
    std::string line;
    std::getline(is, line);

    sendMessage = processCommand(line);

    asio::async_write(_socket, asio::buffer(sendMessage),
                      std::bind(&TcpConnection::handleWrite, shared_from_this(),
                                std::placeholders::_1,
                                std::placeholders::_2));
}
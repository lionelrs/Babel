/*
** EPITECH PROJECT, 2021
** Asio
** File description:
** connection singeltone
*/

#ifndef TCPCONNECTION_HPP
#define TCPCONNECTION_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>

#include "SEPProtocol.hpp"
#include "SqliteDataBase.hpp"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>, public SEPProtocol
{
public:
    typedef std::shared_ptr<TcpConnection> pointer;

    static pointer          create(asio::io_context& io_context) {
        return pointer(new TcpConnection(io_context));
    }
    asio::ip::tcp::socket&  getSocket();

    void                    startComunication();

protected:
private:
    TcpConnection(asio::io_context & io_context);

    void    handleWrite(const asio::error_code& err, size_t size);
    void    handleRead(const asio::error_code& error, size_t size);
    void    checkCode(std::string &data);

    asio::ip::tcp::socket   _socket;
    asio::streambuf         _message;
    std::string             _finalMessage;
};

#endif /* !TCPCONNECTION_HPP */
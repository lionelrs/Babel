/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** serveur tcp asio lib
*/

#ifndef ASIOTCPSERV_HPP
#define ASIOTCPSERV_HPP

#include "TcpConnection.hpp"

class AsioTcpServ {
public:
    AsioTcpServ(asio::io_context& io_context, const int port);
    ~AsioTcpServ();

    void    start_accept();

protected:
private:
    void    handle_connexion(TcpConnection::pointer new_connection, const asio::error_code& error);

    asio::io_context& _io_context;
    asio::ip::tcp::acceptor _acceptor;
};

#endif /* !ASIOTCPSERV_HPP */

/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** asio server
*/

#include "AsioTcpServ.hpp"

AsioTcpServ::AsioTcpServ(asio::io_context &io_context, const int port)
    : _io_context(io_context), _acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
}

AsioTcpServ::~AsioTcpServ()
{
}

void AsioTcpServ::start_accept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(_io_context);

    _acceptor.async_accept(new_connection->getSocket(),
                            std::bind(&AsioTcpServ::handle_connexion, this, new_connection,
                                    std::placeholders::_1));
    std::cout << "prêt a accpeter" << std::endl;
}

void AsioTcpServ::handle_connexion(TcpConnection::pointer new_connection,
                                    const asio::error_code &error)
{
    std::cout << "client accepter" << std::endl;
    if (!error)
    {
        new_connection->startComunication();
    }

    start_accept();
}
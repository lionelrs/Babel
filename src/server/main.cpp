/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ASIO serv main
*/

#include "AsioTcpServ.hpp"

int main(int ac, char **av)
{
    asio::io_context io_context;

    AsioTcpServ server(io_context, std::atoi(av[1]));

  
    server.start_accept();

    io_context.run();

    return (0);
}
/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ASIO serv main
*/

#include "AsioTcpServ.hpp"
#include "../common/BabelException.hpp"

int main(int ac, char **av)
{
    try {
        asio::io_context io_context;
        if (ac < 2 || std::atoi(av[1]) < 1025 || std::atoi(av[1]) > 65535)
            throw Babel::BabelException("Please provide a valid port (1025 to 65535)");
        AsioTcpServ server(io_context, std::atoi(av[1]));
        server.start_accept();
        io_context.run();
        return (0);
    }
    catch(const Babel::BabelException& e)
    {
        std::cerr << WHERE << std::endl << "\t" << e.what() << std::endl;
        return (84);
    }
    return (0);
}
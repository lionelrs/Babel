/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ASIO serv main
*/

#include "SEPServer.hpp"

int main(int ac, char **av)
{
    try {
        if (ac < 2)
            throw Babel::BabelException("Please provide a valid port (1025 to 65535)");
        int port = std::atoi(av[1]);
        if (port < 1025 || port > 65535)
            throw Babel::BabelException("Please provide a valid port (1025 to 65535)");

        SEPServer server(port);
        server.initSepServer();
        server.listenOnPort();
        return (0);
    }
    catch(const Babel::BabelException& e)
    {
        std::cerr << WHERE << std::endl << "\t" << e.what() << std::endl;
        return (84);
    }
    return (0);
}
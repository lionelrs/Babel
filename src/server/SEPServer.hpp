/*
** EPITECH PROJECT, 2021
** *
** File description:
** SEPServer
*/

#ifndef SEPSERVER_HPP_
#define SEPSERVER_HPP_


#include "User.hpp"

class SEPServer {
    public:
        SEPServer(int port);
        ~SEPServer();

        void initSepServer();
        void listenOnPort();

    protected:
    private:

        void handleRead();
        void handleWrite();
        void handleConnection();
        void handleDisconnection(User *user);
        void cleanUserList();

        void sendToUser(int userFd, std::string msg);

        int _port;
        int opt = true;
        std::vector<User *> userList;
        int master_socket, addrlen, new_socket, client_socket[30],
        max_clients = 30, activity, i, valread, sd;
        int max_sd;
        struct sockaddr_in address;
        char buffer[1025];
        fd_set readfds;
};

#endif /* !SEPSERVER_HPP_ */

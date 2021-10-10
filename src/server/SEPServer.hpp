/*
** EPITECH PROJECT, 2021
** *
** File description:
** SEPServer
*/

#ifndef SEPSERVER_HPP_
#define SEPSERVER_HPP_


#include "User.hpp"

class SEPServer : public SEPProtocol {
    public:
        SEPServer(int port);
        ~SEPServer();

        void initSepServer();
        void listenOnPort();
        typedef std::string (SEPProtocol::*factoryF)(const std::vector<std::string> &arg);
    protected:
    private:

        int parseLocalCommand();
        void handleResponse(User *user);
        void handleConnection();
        void handleDisconnection(User *user);
        void cleanUserList();

        void cmdLogin();

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
        std::map<int, factoryF> _cmd;
        bool _hasDisconnected;
};

#endif /* !SEPSERVER_HPP_ */

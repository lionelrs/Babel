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
        typedef std::string (SEPServer::*factoryF)(User *user);
    protected:
    private:

        bool isLoggedIn(char *token);
        int parseLocalCommand(const char *b);
        void handleResponse(User *user);
        void handleConnection();
        void handleDisconnection(User *user);
        void cleanUserList();

        std::string cmdListAllLoggedUsers(User *User);
        std::string cmdLoginSucces(User *User);
        std::string cmdLoginFailure(User *user);
        std::string cmdCall(User *user);

        void sendToUser(int userFd, std::string msg);
        void sendDisc(std::string name);

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
        User *_currentUser;
};

#endif /* !SEPSERVER_HPP_ */

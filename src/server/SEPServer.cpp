/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SEPServer
*/

#include "SEPServer.hpp"

SEPServer::SEPServer(int port)
{
    _port = port;
    _cmd.emplace(300, &SEPServer::cmdLogin);
}

int SEPServer::parseLocalCommand()
{
    char digit[4];
    std::memset(digit, 0, sizeof(digit));
    std::strncpy(digit, buffer, 3);
    return (std::atoi(digit));
}

void SEPServer::cmdLogin()
{

}

void SEPServer::handleResponse(User *user)
{
    int cmd = parseLocalCommand();
    buffer[valread] = '\0';
    std::string response = processCommand(buffer);
    sendToUser(sd, response.c_str());
}

void SEPServer::sendToUser(int fd, std::string msg)
{
    if (send(fd, msg.c_str(), msg.size(), 0) != msg.size()) {
        throw Babel::BabelException("send");
    }
}

void SEPServer::handleConnection()
{
    if (FD_ISSET(master_socket, &readfds)) {
        if ((new_socket = accept(master_socket,
                                 (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            throw Babel::BabelException("accept error");
        }

        std::cout << "New connection, socket fd is " << new_socket <<
        ", ip is : " << inet_ntoa(address.sin_addr) << ", port : " << ntohs(address.sin_port) << std::endl;
        User *user = new User(inet_ntoa(address.sin_addr), ntohs(address.sin_port), new_socket);
        this->userList.push_back(user);

        this->sendToUser(new_socket, "Welcome to the SEP Server !");

        std::cout << "Welcome message sent successfully" << std::endl;
    }
}

void SEPServer::handleDisconnection(User *user)
{
    if ((valread = read(sd, buffer, 1024)) == 0) {

        getpeername(sd, (struct sockaddr *)&address,
                    (socklen_t *)&addrlen);
        std::cout << "Host disconnected, socket fd is " << sd <<
        ", ip is : " << inet_ntoa(address.sin_addr) << ", port : " << ntohs(address.sin_port) << std::endl;
        close(sd);
        user->disconnect();
    }
    else {
        this->handleResponse(user);
    }
}

void SEPServer::cleanUserList()
{
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getSocket() == 0) {
            delete userList[i];
            userList[i] = nullptr;
            userList.erase(userList.begin() + i);
        }
    }
}

void SEPServer::listenOnPort()
{
    std::cout << "Waiting for connections ..." << std::endl;
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (auto user : userList) {
            sd = user->getSocket();
            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > max_sd)
                max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            throw Babel::BabelException("select error");
        }

        this->handleConnection();

        //else its some IO operation on some other socket
        for (User *user : userList) {
            sd = user->getSocket();

            if (FD_ISSET(sd, &readfds)) {
                this->handleDisconnection(user);
            }
        }
        this->cleanUserList();
    }
}

void SEPServer::initSepServer()
{
    addrlen = sizeof(address);

    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw Babel::BabelException("Socket failed");
    }

    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0) {
        throw Babel::BabelException("setsockopt");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw Babel::BabelException("bind failed");
    }

    std::cout << "Server Listening on port " << _port << std::endl;

    if (listen(master_socket, 3) < 0) {
        throw Babel::BabelException("listen");
    }
}

SEPServer::~SEPServer()
{
}

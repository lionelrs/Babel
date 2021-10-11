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
    _cmd.emplace(200, &SEPServer::cmdLoginSucces);
    _cmd.emplace(430, &SEPServer::cmdCallResponse);
    _cmd.emplace(450, &SEPServer::cmdCall);
    _cmd.emplace(460, &SEPServer::cmdRefuseCall);
    _cmd.emplace(470, &SEPServer::cmdCallHangUp);
    _cmd.emplace(500, &SEPServer::cmdLoginFailure);
    _cmd.emplace(650, &SEPServer::cmdListAllLoggedUsers);
}

int SEPServer::parseLocalCommand(const char *b)
{
    char digit[4];
    std::memset(digit, 0, sizeof(digit));
    std::strncpy(digit, b, 3);
    return (std::atoi(digit));
}

std::string SEPServer::cmdListAllLoggedUsers(User *user, std::string response)
{
    std::stringstream ss;
    ss << "650 ";
    (void)response;
    for (auto itr : userList) {
        if (itr->isConnected()) {
            ss << itr->getUserName();
            ss << ";";
        }
    }
    return (ss.str());
}

std::string SEPServer::cmdRefuseCall(User *user, std::string response)
{
    std::string token, name;
    std::stringstream ss;
    std::vector<std::string> rawData = getInfosCommand(response + "\r\n");
    if (rawData.size() < 2) {
        return ("500");
    }
    token = rawData[0];
    name = rawData[1];
    name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getUserName() == name) {
            ss << token;
            sendToUser(userList[i]->getSocket(), ss.str());
            userList[i]->setIsInCall(false);
            userList[i]->setCalling("");
        }
    }
    return ("");
}

std::string SEPServer::cmdAlreadyInCall(User *user, std::string response)
{
    std::string token, port, name;
    std::stringstream ss;
    (void)response;
    std::vector<std::string> rawData = getInfosCommand(response + "\r\n");
    if (rawData.size() < 3) {
        return ("500");
    }
    token = rawData[0];
    port = rawData[1];
    name = rawData[2];
    name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    ss << "480";
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getUserName() == name) {
            sendToUser(userList[i]->getSocket(), ss.str());
        }
    }
    return ("");
}

std::string SEPServer::cmdCallHangUp(User *user, std::string response)
{
    std::string token, name;
    std::stringstream ss;
    std::vector<std::string> rawData = getInfosCommand(response + "\r\n");
    if (rawData.size() < 2) {
        return ("500");
    }
    token = rawData[0];
    name = rawData[1];
    name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getUserName() == name) {
            ss << token;
            sendToUser(userList[i]->getSocket(), ss.str());
            user->setIsInCall(false);
            user->setCalling("");
            userList[i]->setIsInCall(false);
            userList[i]->setCalling("");
        }
    }
    return ("");
}

std::string SEPServer::cmdCall(User *user, std::string response)
{
    std::string token, port, name;
    std::stringstream ss;
    (void)response;
    std::vector<std::string> rawData = getInfosCommand(response + "\r\n");
    if (rawData.size() < 3) {
        return ("500");
    }
    token = rawData[0];
    port = rawData[1];
    name = rawData[2];
    name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    ss << "450 ";
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getUserName() == name) {
            if (userList[i]->isInCall())
                return ("480");
            ss << port;
            ss << " ";
            ss << user->getUserName();
            ss << " ";
            ss << user->getIp();
            sendToUser(userList[i]->getSocket(), ss.str());
            user->setIsInCall(true);
            user->setCalling(name);
        }
    }
    return ("");
}

std::string SEPServer::cmdCallResponse(User *user, std::string response)
{
    std::string token, port, name;
    std::stringstream ss;
    (void)response;
    std::vector<std::string> rawData = getInfosCommand(response + "\r\n");
    if (rawData.size() < 3) {
        return ("500");
    }
    token = rawData[0];
    port = rawData[1];
    name = rawData[2];
    name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    ss << "430 ";
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getUserName() == name) {
            ss << port;
            ss << " ";
            ss << user->getIp();
            sendToUser(userList[i]->getSocket(), ss.str());
            user->setIsInCall(true);
            user->setCalling(name);
        }
    }
    return ("435");
}

bool SEPServer::isLoggedIn(char *token)
{
    for (auto itr : userList) {
        if (std::strcmp(itr->getUserName().c_str(), token) == 0)
            return (true);
    }
    return (false);
}

std::string SEPServer::cmdLoginSucces(User *user, std::string response)
{
    (void)response;
    std::string data = SqliteDataBase::getData();
    char sCopy[data.size() + 1];
    std::memset(sCopy, 0, sizeof(sCopy));
    std::strcpy(sCopy, data.c_str());
    char *token = NULL;
    std::stringstream ss;
    if (data != "NULL") {
        token = std::strtok(sCopy, ";");
        if (token == NULL) {
            ss << "500";
            return (ss.str());
        }
        if (isLoggedIn(token)) {
            ss << "550";
            return (ss.str());
        }
        user->setUserName(token);
        user->login();

        for (auto itr : userList) {
            if (itr != user && itr->isConnected()) {
                sendToUser(itr->getSocket(), "150 " + user->getUserName());
            }
        }
    }
    ss << "200 ";
    ss << token;
    return (ss.str());
}

std::string SEPServer::cmdLoginFailure(User *user, std::string)
{
    (void)user;
    return ("500");
}

void SEPServer::handleResponse(User *user)
{
    int cmd = parseLocalCommand(buffer);
    std::cout << "CMD" << ": " << cmd << std::endl;
    std::string response = processCommand(buffer);
    cmd = parseLocalCommand(response.c_str());
    SEPServer::factoryF func = _cmd[cmd];
    char *token = strtok(buffer, "\r\n");
    response = (this->*func)(user, std::string(token));
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
    std::memset(buffer, 0, 1024);
    if ((valread = read(sd, buffer, 1024)) == 0) {

        getpeername(sd, (struct sockaddr *)&address,
                    (socklen_t *)&addrlen);
        std::cout << "Host disconnected, socket fd is " << sd <<
        ", ip is : " << inet_ntoa(address.sin_addr) << ", port : " << ntohs(address.sin_port) << std::endl;
        close(sd);
        if (user->isInCall()) {
            user->setIsInCall(false);
            std::string buddyName = user->getCalling();
            for (auto itr : userList) {
                if (itr->getUserName() == buddyName) {
                    itr->setCalling("");
                    itr->setIsInCall(false);
                }
            }
        }
        user->disconnect();
    }
    else {
        this->handleResponse(user);
    }
}

void SEPServer::sendDisc(std::string name)
{
    for (auto user : userList) {
        if (user->isConnected()) {
            sendToUser(user->getSocket(), "250 " + name);
        }
    }
}

void SEPServer::cleanUserList()
{
    for (int i = 0; i < userList.size(); i++) {
        if (userList[i]->getSocket() == 0) {
            this->sendDisc(userList[i]->getUserName());
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
        throw Babel::BabelException("setsockopt failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw Babel::BabelException("bind failed");
    }

    std::cout << "Server Listening on port " << _port << std::endl;

    if (listen(master_socket, 3) < 0) {
        throw Babel::BabelException("listen failed");
    }
}

SEPServer::~SEPServer()
{
}

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** User
*/

#ifndef USER_HPP_
#define USER_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include <sstream> 
#include <asio.hpp>
#include "SEPProtocol.hpp"
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <vector>
#include <map>
#include "../common/BabelException.hpp"

class User {
    public:
        User(std::string ip, int port, int fd);
        ~User();

        bool isConnected() const;
        void disconnect();
        int getSocket() const;
        int getId() const;
        void setId(int id);

    protected:
    private:
        bool _isConnected;
        std::string _ip;
        int _port;
        int _socket;
        int _id;
};

#endif /* !USER_HPP_ */

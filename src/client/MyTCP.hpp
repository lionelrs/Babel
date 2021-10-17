/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyTCP
*/

#ifndef MYTCP_HPP_
#define MYTCP_HPP_

#include <QTcpServer>
#include <QTcpSocket>

#include <ctime>
#include <string>
#include <cstdint>
#include <cstring>
#include "Socket.hpp"
#include "../common/SEPCommands.hpp"
#include "../common/BabelException.hpp"

class MyTCP : public Socket {
        Q_OBJECT
    public:
        MyTCP(const std::string ip, const int port, QObject *parent = 0);
        ~MyTCP();

        QTcpSocket *getSocket() const;
        std::string getData() const;

        void writeData(Message msg);
        void openConnection();
        void readData();

    signals:
    public slots:

    private:
        SEPCommands *_command;
        QTcpSocket *_socket;
        std::string _data;
};

#endif /* !MYTCP_HPP_ */

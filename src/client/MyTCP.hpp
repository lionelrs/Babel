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

#include "Socket.hpp"
#include "../common/Serializer.hpp"
#include "../common/SEPCommands.hpp"

class MyTCP : public Socket {
    public:
        MyTCP(const std::string ip, const int port, QObject *parent = 0);
        ~MyTCP();

        QTcpSocket *getSocket() const;

        void writeData(Message msg);
        void openConnection();

    signals:
    public slots:
        void readData();

    private:
        QTcpSocket *_socket;
};

#endif /* !MYTCP_HPP_ */

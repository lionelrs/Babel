/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyTCP
*/

#ifndef MYTCP_HPP_
#define MYTCP_HPP_

#include <QObject>
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include "Message.hpp"


enum SEP {
    CONNECT_SUCCES = 0,
    CONNECT_FAILURE,
    USER_INFOS_SUCCES,
    USER_INFOS_FAILURE,
};

class MyTCP : public QObject {
        Q_OBJECT
    public:
        MyTCP(std::string ip, int port, QObject *parent = 0);
        ~MyTCP();

        QTcpSocket *getSocket() const;
        std::string getIp() const;
        int getPort() const;

    signals:
    public slots:
        void listenData();
    private:
        void writeData(Message msg);
        void connectToServ();
        QTcpSocket *_socket;
        std::string _ip;
        int _port;
};

#endif /* !MYTCP_HPP_ */

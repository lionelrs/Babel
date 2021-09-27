/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyUDP
*/

#ifndef MYUDP_HPP_
#define MYUDP_HPP_

#include <QObject>
#include <QUdpSocket>
#include <iostream>
#include "Message.hpp"

class MyUDP : public QObject
{
        Q_OBJECT
    public:
        explicit MyUDP(std::string ip, int port, QObject *parent = 0);
        ~MyUDP();

        QUdpSocket *getSocket() const;
        std::string getIp() const;
        int getPort() const;

    signals:
    public slots:
        void writeData(Message msg);
        void readData();
    private:
        QUdpSocket *_socket;
        std::string _ip;
        int _port;
};

#endif /* !MYUDP_HPP_ */

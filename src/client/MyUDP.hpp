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
        explicit MyUDP(QObject *parent = 0);
        ~MyUDP();

        QUdpSocket *getSocket() const;
        std::string getIp() const;
        int getPort() const;

    signals:
    public slots:
        void sendData();
        void readData();
    private:
        QUdpSocket *_readSocket;
        QUdpSocket *_writeSocket;

        std::string _readIp;
        std::string _writeIp;

        int _readPort;
        int _writePort;
};

#endif /* !MYUDP_HPP_ */

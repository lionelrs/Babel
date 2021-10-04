/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <QObject>
#include <iostream>

#include "Message.hpp"

class Socket : public QObject {
    Q_OBJECT
    public:
        explicit Socket(const std::string ip, const int port, QObject *parent = 0);
        ~Socket();

        int getPort() const;
        std::string getIp() const;

        virtual void writeData(Message msg) = 0;
        virtual void openConnection() = 0;

    signals:
    public slots:
        virtual void readData() = 0;

    protected:
        std::string _ip;
        int _port;
    private:
};

#endif /* !SOCKET_HPP_ */

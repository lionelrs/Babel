/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyUDP
*/

#ifndef MYUDP_HPP_
#define MYUDP_HPP_

#include <QUdpSocket>

#include "Socket.hpp"

#include "../common/PortAudio.hpp"
#include "../common/Parser.hpp"
#include <unistd.h>

class MyUDP : public Socket
{
    public:
        explicit MyUDP(const std::string ip, const int port, QObject *parent = 0);
        ~MyUDP();

        QUdpSocket *getSocket() const;

        void openConnection();
        void writeData(Message msg);
        void readData();

    signals:
    public slots:

    private:
        QUdpSocket *_socket;
        Babel::IAudio *_player;

};

#endif /* !MYUDP_HPP_ */

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyUDP
*/

#include "MyUDP.hpp"

MyUDP::MyUDP(std::string ip, int port, QObject *parent) : _ip(ip), _port(port), QObject(parent)
{
    _socket = new QUdpSocket(this);
    _socket->bind(QHostAddress(_ip.c_str()), _port);
}

MyUDP::~MyUDP()
{
}

void MyUDP::writeData(Message msg)
{
    QByteArray writeData;
    writeData.append(msg.body().toLocal8Bit());
    _socket->writeDatagram(writeData, QHostAddress(_ip.c_str()), _port);
    writeData.clear();
}

void MyUDP::readData()
{
    QByteArray readBuffer;
    readBuffer.resize(_socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    _socket->readDatagram(readBuffer.data(), readBuffer.size(), &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << readBuffer;
}

QUdpSocket *MyUDP::getSocket() const
{
    return (_socket);
}

int MyUDP::getPort() const
{
    return (_port);
}

std::string MyUDP::getIp() const
{
    return (_ip);
}
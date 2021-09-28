/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyTCP
*/

#include "MyTCP.hpp"

MyTCP::MyTCP(std::string ip, int port, QObject *parent) : _ip(ip), _port(port), QObject(parent)
{
    _socket = new QTcpSocket(this);
    _socket->bind(QHostAddress(_ip.c_str()), _port);
    this->connectToServ();
    connect(_socket, SIGNAL(readyRead()), this, SLOT(listenData()));
}

MyTCP::~MyTCP()
{
}

void MyTCP::connectToServ()
{
    std::cout << "Trying to establish connection..." << std::endl;
    QByteArray writeData;
    writeData.append("200\r\n");
    _socket->write(writeData);
    writeData.clear();
}

void MyTCP::listenData()
{
    QByteArray readBuffer;
    readBuffer.resize(_socket->bytesAvailable());

    readBuffer = _socket->read(_socket->bytesAvailable());
    qDebug() << "Message: " << readBuffer;
}

QTcpSocket *MyTCP::getSocket() const
{
    return (_socket);
}
std::string MyTCP::getIp() const
{
    return (_ip);
}
int MyTCP::getPort() const
{
    return (_port);
}
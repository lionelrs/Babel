/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyTCP
*/

#include "MyTCP.hpp"

MyTCP::MyTCP(const std::string ip, const int port, QObject *parent) : Socket(ip, port, parent)
{
}

MyTCP::~MyTCP()
{
}

void MyTCP::openConnection()
{
    _socket = new QTcpSocket();
    _socket->connectToHost(QHostAddress(_ip.c_str()), _port);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(listenData()));
}

void MyTCP::writeData(Message data)
{
    QByteArray writeData;
    writeData.append(data.getHeader().toLocal8Bit() + " " + data.getBody().toLocal8Bit());
    _socket->write(writeData);
    _socket->waitForBytesWritten();
    std::cout << "Writting to server" << std::endl;
    writeData.clear();
}

void MyTCP::readData()
{
    QByteArray readBuffer;
    readBuffer.resize(_socket->bytesAvailable());

    readBuffer = _socket->read(_socket->bytesAvailable());
    qDebug() << "Server response: " << readBuffer;
}

QTcpSocket *MyTCP::getSocket() const
{
    return _socket;
}

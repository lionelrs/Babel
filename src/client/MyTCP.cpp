/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyTCP
*/

#include "MyTCP.hpp"

MyTCP::MyTCP(const std::string ip, const int port, QObject *parent) : Socket(ip, port, parent)
{
    _command = NULL;
}

MyTCP::~MyTCP()
{
}

void MyTCP::openConnection()
{
    _socket = new QTcpSocket();
    _socket->connectToHost(QHostAddress(_ip.c_str()), _port);
    if (!_socket->waitForConnected(1000))
        throw Babel::BabelException("Cannot connect to TCP host with ip " + _ip + " and port " + std::to_string(_port) + ".");
}

void MyTCP::writeData(Message data)
{
    QByteArray writeData;
    writeData.append(data.getHeader().toLocal8Bit() + " " + data.getBody().toLocal8Bit() + "\r\n");
    _socket->write(writeData);
    _socket->waitForBytesWritten();
    std::cout << "Writting to server: " + data.getHeader().toLocal8Bit().toStdString() + " " + data.getBody().toLocal8Bit().toStdString() << std::endl;
    writeData.clear();
}

SEPCommands *MyTCP::getSEPCommand() const
{
    return _command;
}

std::string MyTCP::getData() const
{
    return _data;
}

void MyTCP::readData()
{
    QByteArray readBuffer = {0};
    readBuffer.resize(_socket->bytesAvailable());
    readBuffer = _socket->read(_socket->bytesAvailable());
    _data = readBuffer.data();
}

QTcpSocket *MyTCP::getSocket() const
{
    return _socket;
}

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
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void MyTCP::writeData(Message data)
{
    QByteArray writeData;
    writeData.append(data.getHeader().toLocal8Bit() + " " + data.getBody().toLocal8Bit() + "\r\n");
    _socket->write(writeData);
    _socket->waitForBytesWritten();
    std::cout << "Writting to server" << std::endl;
    writeData.clear();
}

SEPCommands *MyTCP::getSEPCommand() const
{
    return (_command);
}

void MyTCP::readData()
{
    QByteArray readBuffer = {0};
    readBuffer.resize(_socket->bytesAvailable());
    readBuffer = _socket->read(_socket->bytesAvailable());
    SEPCommands *data = Serializer::unSerialize(readBuffer.data());
    _command = data;
    std::cout << "SEP Command recieved !" << std::endl;
    std::cout << "code: " <<_command->code << std::endl;
    std::cout << "port: " <<_command->port << std::endl;
    std::cout << "ip: " <<_command->ip << std::endl;
}

QTcpSocket *MyTCP::getSocket() const
{
    return _socket;
}

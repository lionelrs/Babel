/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyTCP
*/

#include "MyTCP.hpp"

/**
 * Creates an instance of MyTCP that is used to establish the connection with the server.
 * Herit from the Socket class.
 *
 * @param ip Specifies the ip of the server that you want to connect to.
 * @param port Specifies the port of the server that you want to connect to.
 * @param parent Parent widget to herit from.
 */
MyTCP::MyTCP(const std::string ip, const int port, QObject *parent) : Socket(ip, port, parent)
{
    _command = NULL;
}

MyTCP::~MyTCP()
{
}


/**
 * Open the TCP connection with the server.
 */
void MyTCP::openConnection()
{
    _socket = new QTcpSocket();
    _socket->connectToHost(QHostAddress(_ip.c_str()), _port);
    if (!_socket->waitForConnected(1000))
        throw Babel::BabelException("Cannot connect to TCP host with ip " + _ip + " and port " + std::to_string(_port) + ".");
}

/**
 * Send a data to the server.
 *
 * @param data Data to be sent.
 */
void MyTCP::writeData(Message data)
{
    QByteArray writeData;
    writeData.append(data.getHeader().toLocal8Bit() + " " + data.getBody().toLocal8Bit() + "\r\n");
    _socket->write(writeData);
    _socket->waitForBytesWritten();
    std::cout << "Writting to server: " + data.getHeader().toLocal8Bit().toStdString() + " " + data.getBody().toLocal8Bit().toStdString() << std::endl;
    writeData.clear();
}

/**
 * Getter of the readed data from the server.
 */
std::string MyTCP::getData() const
{
    return _data;
}

/**
 * Read the data sent by the server.
 */
void MyTCP::readData()
{
    QByteArray readBuffer = {0};
    readBuffer.resize(_socket->bytesAvailable());
    readBuffer = _socket->read(_socket->bytesAvailable());
    _data = readBuffer.data();
}

/**
 * Getter of the TCP socket.
 */
QTcpSocket *MyTCP::getSocket() const
{
    return _socket;
}

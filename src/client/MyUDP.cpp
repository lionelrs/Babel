/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyUDP
*/

#include "MyUDP.hpp"

MyUDP::MyUDP(const std::string ip, const int port, QObject *parent) : Socket(ip, port, parent)
{
    _player = new Babel::PortAudio();
}

MyUDP::~MyUDP()
{
}

void MyUDP::openConnection()
{
    _socket = new QUdpSocket();
    _socket->bind(QHostAddress(_ip.c_str()), _port);
}

void MyUDP::writeData(Message data)
{
    QByteArray writeData;
    writeData.append(data.getBody().toLocal8Bit());
    _socket->writeDatagram(writeData, QHostAddress(_ip.c_str()), _port);
    writeData.clear();
}

void MyUDP::readData()
{
    Parser parser(_player->getBuffer().size());
    float *array;
    QByteArray readBuffer;
    readBuffer.resize(_socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    _socket->readDatagram(readBuffer.data(), readBuffer.size(), &sender, &senderPort);
    array = parser.rebuildSoundFromString(readBuffer.toStdString());
    pid_t child = fork();
    _player->getBuffer().setBuffer(array);
    if (child == 0) {
        
        _player->play();
        exit(0);
    }

    // qDebug() << "Message from: " << sender.toString();
    // qDebug() << "Message port: " << senderPort;
    // qDebug() << "Message: " << readBuffer;
}

QUdpSocket *MyUDP::getSocket() const
{
    return _socket;
}

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyUDP
*/

#include "MyUDP.hpp"

/**
 * Creates an instance of MyUDP that is used to establish the connection with another client.
 * Herit from the Socket class.
 *
 * @param ip Specifies the ip of the client that you want to connect to.
 * @param port Specifies the port of the client that you want to connect to.
 * @param parent Parent widget to herit from.
 */
MyUDP::MyUDP(const std::string ip, const int port, QObject *parent) : Socket(ip, port, parent)
{
    _player = new Babel::PortAudio();
}

MyUDP::~MyUDP()
{
}

/**
 * Bind the UDP client.
 */
void MyUDP::openConnection()
{
    _socket = new QUdpSocket();
    _socket->bind(QHostAddress(_ip.c_str()), _port);
}

/**
 * Send a data to the other client.
 *
 * @param data Data to be sent.
 */
void MyUDP::writeData(Message data)
{
    QByteArray writeData;
    writeData.append(data.getHeader().toLocal8Bit() + "/" +  data.getBody().toLocal8Bit());
    _socket->writeDatagram(writeData, QHostAddress(_ip.c_str()), _port);
    writeData.clear();
}

/**
 * Read the data sent by the other client.
 */
void MyUDP::readData()
{
    static int64_t timeSort = 0;
    std::string header = "";
    Parser parser(_player->getBuffer().size());
    float *array;
    QByteArray readBuffer;
    readBuffer.resize(_socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    _socket->readDatagram(readBuffer.data(), readBuffer.size(), &sender, &senderPort);

    size_t pos = 0;
    std::string token;
    std::string delimiter = "/";
    std::string my_string = readBuffer.toStdString();

    pos = my_string.find(delimiter);
    header = my_string.substr(0, pos);

    my_string.erase(0, pos + delimiter.length());

    if (timeSort > std::strtoll(header.c_str(), NULL, 10)) {
        std::cout << "---------------- Packet ignored ----------------\n";
        return;
    }
    timeSort = std::strtoll(header.c_str(), NULL, 10);
    array = parser.rebuildSoundFromString(my_string);
    _player->getBuffer().setBuffer(array);
    pid_t child = fork();
    if (child == 0) {
        _player->play();
        exit(child);
    }

    // qDebug() << "Message from: " << sender.toString();
    // qDebug() << "Message port: " << senderPort;
    // qDebug() << "Message: " << readBuffer;
}

/**
 * Getter of the UDP socket.
 */
QUdpSocket *MyUDP::getSocket() const
{
    return _socket;
}

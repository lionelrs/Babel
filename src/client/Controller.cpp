/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#include "Controller.hpp"

Controller::Controller(int port, char *ip) : _port(port), _ip(ip)
{
    _window = new QMainWindow();
    _window->setWindowTitle("Babel Voice Client");
    _window->resize(QSize(600, 300));
    _window->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    _loginWidget = new LoginWidget();
    _hubWidget = new HubWidget();
    _tcp = new MyTCP(ip, port);
}

Controller::~Controller()
{
}

void Controller::sendUdpData()
{
    Message data("Body", "Header");
    _writeUdp->writeData(data);
}

void Controller::sendTcpLoginForm()
{
    SEPCommands data;

    data.code = 100;
    data.port = _port;
    std::memset(data.ip, '\0', 1024);
    std::strcat(data.ip, _ip.c_str());
    std::strcat(data.ip, ";");
    std::strcat(data.ip, _loginWidget->getLoginForm().getHeader().toStdString().c_str());
    std::strcat(data.ip, ";");
    std::strcat(data.ip, _loginWidget->getLoginForm().getBody().toStdString().c_str());
    std::strcat(data.ip, "\r\n");
    Serializer::serialize(data);
    std::cout << _loginWidget->getLoginForm().getHeader().toStdString() << " " << _loginWidget->getLoginForm().getBody().toStdString() << std::endl;
    _tcp->writeData(_loginWidget->getLoginForm());
}

void Controller::callSelected()
{
    int selected = _hubWidget->getSelected();
    if (selected == -1)
        ErrorWidget("No user selected.", "Error", _hubWidget);
    else
        std::cout << "Call " + _hubWidget->getSelectedName() + " " + _hubWidget->getSelectedIp() + " " + std::to_string(_hubWidget->getSelectedPort()) << std::endl;
}

void Controller::responseSelector(const std::string response)
{
    //if (response == std::to_string(CO_ERROR))
    //    ErrorWidget("Login failed.", "Error", _loginWidget);
    if (response == std::to_string(CO_ERROR)) {
        _window->setCentralWidget(_hubWidget);

        for (int i = 0; i < 10; i++) {
            _hubWidget->addUser(std::to_string(i), "192.168.0." + std::to_string(i), i);
        }

        connect(_hubWidget->getButton(), SIGNAL(clicked()), this,  SLOT(callSelected()));
    }
}

void Controller::listenTcpData()
{
    _tcp->readData();
    std::cout << "Data received: " << _tcp->getData() << std::endl;
    responseSelector(_tcp->getData());
}

void Controller::startBabel()
{
    _window->setCentralWidget(_loginWidget);
    _tcp->openConnection();
    connect(_tcp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenTcpData()));
    connect(_loginWidget->getButton(), SIGNAL(clicked()), this,  SLOT(sendTcpLoginForm()));
    _window->show();
}
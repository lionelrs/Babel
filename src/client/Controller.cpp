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
    _loginWidget = new LoginWidget();
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
    std::cout << _loginWidget->getLoginForm().getHeader().toStdString() << " " << _loginWidget->getLoginForm().getBody().toStdString() << std::endl;
    _tcp->writeData(_loginWidget->getLoginForm());
}

void Controller::listenData()
{
    _readUdp->readData();
}

void Controller::startBabel()
{
    _window->setCentralWidget(_loginWidget);
    _tcp->openConnection();
    connect(_loginWidget->getButton(), SIGNAL(clicked()), this,  SLOT(sendTcpLoginForm()));
    _window->show();
}
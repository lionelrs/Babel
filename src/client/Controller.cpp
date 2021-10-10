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
    _tcp->writeData(_loginWidget->getLoginForm());
}

void Controller::callSelected()
{
    int selected = _hubWidget->getSelected();
    if (selected == -1)
        ErrorWidget("No user selected.", "Error", _hubWidget);
    else
        std::cout << "Calling " + _hubWidget->getSelectedName() << std::endl;
}

void Controller::responseSelector(std::string response)
{
    int code = std::atoi(response.substr(0, response.find(' ')).c_str());
    if (code == CO_ERROR)
        ErrorWidget("Login failed.", "Error", _loginWidget);
    if (code == CONNECTION_OK) {
        size_t pos = response.find(' ');
        response.erase(0, pos + 1);
        _username = response;
        _window->setCentralWidget(_hubWidget);
        _tcp->writeData(Message("", std::to_string(REQUEST_USERS).c_str()));
        connect(_hubWidget->getButton(), SIGNAL(clicked()), this,  SLOT(callSelected()));
    }
    if (code == USER_LIST) {
        size_t pos = response.find(' ');
        response.erase(0, pos + 1);
        std::string token;
        while ((pos = response.find(';')) != std::string::npos) {
            token = response.substr(0, pos);
            response.erase(0, pos + 1);
            if (token == _username) continue;
            _hubWidget->addUser(token);
        }
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
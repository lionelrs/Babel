/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#include "Controller.hpp"

Controller::Controller(int port, char *ip) : _ip(ip)
{
    srand(time(NULL));
    _window = new QMainWindow();
    _window->setWindowTitle("Babel Voice Client");
    _window->resize(QSize(600, 300));
    _hubWidget = nullptr;
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
    _tcp->writeData(_loginWidget->getLoginForm());
}

void Controller::callSelected()
{
    int selected = _hubWidget->getSelected();
    if (selected == -1)
        ErrorWidget("No user selected.", "Error", _hubWidget);
    else {
        int readPort = 1024 + rand() % 64512;
        _readUdp = new MyUDP(_ip, readPort);
        _readUdp->openConnection();
        _tcp->writeData(Message((std::to_string(readPort) + " " + _hubWidget->getSelectedName()).c_str(), std::to_string(REQUEST_CALL).c_str()));
    }
}

void Controller::responseSelector(std::string response)
{
    int code = std::atoi(response.substr(0, response.find(' ')).c_str());
    response.erase(0, response.find(' ') + 1);
    if (code == CO_ERROR)
        ErrorWidget("Login failed.", "Error", _loginWidget);
    if (code == CONNECTION_OK) {
        _username = response;
        _hubWidget = new HubWidget(_username);
        _window->setCentralWidget(_hubWidget);
        _tcp->writeData(Message("", std::to_string(REQUEST_USERS).c_str()));
        connect(_hubWidget->getButton(), SIGNAL(clicked()), this,  SLOT(callSelected()));
    }
    if (code == USER_LIST) {
        size_t pos = 0;
        std::string token;
        while ((pos = response.find(';')) != std::string::npos) {
            token = response.substr(0, pos);
            response.erase(0, pos + 1);
            if (token == _username) continue;
            _hubWidget->addUser(token);
        }
    }
    if (code == ERROR)
        ErrorWidget("Already connected.", "Error", _loginWidget);
    if (code == USER_CO) {
        if (!_hubWidget) return;
        if (response == _username) return;
        _hubWidget->addUser(response);
    }
    if (code == USER_DECO) {
        if (!_hubWidget) return;
        if (response == _username) return;
        _hubWidget->removeUser(response);
    }
    if (code == CALL) {
        std::string ip;
        std::string username;
        int writePort;
        for (size_t pos = 0, i = 0; (pos = response.find(' ')) != std::string::npos; i++) {
            if (i == 0)
                writePort = std::atoi(response.substr(0, pos).c_str());
            else if (i == 1)
                username = response.substr(0, pos).c_str();
            else
                ip = response.substr(0, pos).c_str();
            response.erase(0, pos + 1);
        }
        _writeUdp = new MyUDP(ip, writePort);
        _writeUdp->openConnection();
        int readPort = 1024 + rand() % 64512;
        _readUdp = new MyUDP(_ip, readPort);
        _readUdp->openConnection();
        _tcp->writeData(Message((std::to_string(readPort) + " " + username).c_str(), std::to_string(USERCALLBACKRESPONSE).c_str()));
    }
    if (code == USERCALLBACKCONFIRMATION) {
        std::string ip;
        int port;
        for (size_t pos = 0, i = 0; (pos = response.find(' ')) != std::string::npos; i++) {
            if (i == 0)
                port = std::atoi(response.substr(0, pos).c_str());
            else
                ip = response.substr(0, pos).c_str();
            response.erase(0, pos + 1);
        }
        _writeUdp = new MyUDP(ip, port);
        _writeUdp->openConnection();
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
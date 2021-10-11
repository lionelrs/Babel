/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#include "Controller.hpp"

Controller::Controller(int port, char *ip) : _readIp(ip)
{
    srand(time(NULL));
    _window = new QMainWindow();
    _window->setWindowTitle("Babel Voice Client");
    _window->resize(QSize(600, 300));
    _hubWidget = new HubWidget();
    _loginWidget = new LoginWidget();
    _tcp = new MyTCP(ip, port);

    _called = new QMessageBox(_hubWidget);
    _pButtonYes = _called->addButton(tr("Yes"), QMessageBox::YesRole);
    _called->addButton(tr("No"), QMessageBox::NoRole);

    QFont font;
    font.setPointSize(14);
    _called->setFont(font);
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
        _readPort = 1024 + rand() % 64512;
        _callUsername = _hubWidget->getSelectedName();
        _tcp->writeData(Message((std::to_string(_readPort) + " " + _callUsername).c_str(), std::to_string(REQUEST_CALL).c_str()));
    }
}

void Controller::responseSelector(std::string response)
{
    int code = std::atoi(response.substr(0, response.find(' ')).c_str());
    response.erase(0, response.find(' ') + 1);
    if (code == CO_ERROR)
        ErrorWidget("Login failed.", "Error", _loginWidget);
    if (code == CONNECTION_OK) {
        _myUsername = response;
        _window->setCentralWidget(_hubWidget);
        _hubWidget->setUsername(_myUsername);
        _tcp->writeData(Message("", std::to_string(REQUEST_USERS).c_str()));
        connect(_hubWidget->getButton(), SIGNAL(clicked()), this,  SLOT(callSelected()));
    }
    if (code == USER_LIST) {
        size_t pos = 0;
        std::string token;
        while ((pos = response.find(';')) != std::string::npos) {
            token = response.substr(0, pos);
            response.erase(0, pos + 1);
            if (token == _myUsername) continue;
            _hubWidget->addUser(token);
        }
    }
    if (code == ERROR)
        ErrorWidget("Already connected.", "Error", _loginWidget);
    if (code == USER_CO) {
        if (response == _myUsername) return;
        _hubWidget->addUser(response);
    }
    if (code == USER_DECO) {
        if (response == _myUsername) return;
        _hubWidget->removeUser(response);
    }
    if (code == CALL) {
        _writePort = std::atoi(response.substr(0, response.find(' ')).c_str());
        response.erase(0, response.find(' ') + 1);
        _callUsername = response.substr(0, response.find(' ')).c_str();
        response.erase(0, response.find(' ') + 1);
        _writeIp = response;
        _called->setWindowTitle((_callUsername + " is calling!").c_str());
        _called->setText("Answer?");
        _called->exec();
        if (_called->clickedButton() == _pButtonYes) {
            _readPort = 1024 + rand() % 64512;
            _tcp->writeData(Message((std::to_string(_readPort) + " " + _callUsername).c_str(), std::to_string(USERCALLBACKRESPONSE).c_str()));
        } else
            _tcp->writeData(Message(_callUsername.c_str(), std::to_string(CALLREFUSED).c_str()));
    }
    if (code == USERCALLBACKCONFIRMATION) {
        _writePort = std::atoi(response.substr(0, response.find(' ')).c_str());
        response.erase(0, response.find(' ') + 1);
        _writeIp = response;
        _readUdp = new MyUDP(_readIp, _readPort);
        _readUdp->openConnection();
        connect(_readUdp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenUdpData()));
        _writeUdp = new MyUDP(_writeIp, _writePort);
        _writeUdp->openConnection();
        //_callWidget = new CallWidget(_selectedUsername, _username, _hubWidget);
        //_window->setCentralWidget(_callWidget);
        sendUdpData();
    }
    if (code == CALL_CONFIRMATION) {
        _readUdp = new MyUDP(_readIp, _readPort);
        _readUdp->openConnection();
        connect(_readUdp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenUdpData()));
        _writeUdp = new MyUDP(_writeIp, _writePort);
        _writeUdp->openConnection();
        //_callWidget = new CallWidget(_selectedUsername, _username, _hubWidget);
        //_window->setCentralWidget(_callWidget);
        sendUdpData();
    }
    if (code == CALLREFUSED)
        ErrorWidget(_callUsername + " refused to answer", "Error", _hubWidget);
}

void Controller::listenTcpData()
{
    _tcp->readData();
    std::cout << "Data received: " << _tcp->getData() << std::endl;
    responseSelector(_tcp->getData());
}

void Controller::listenUdpData()
{
    _readUdp->readData();
}

void Controller::startBabel()
{
    _window->setCentralWidget(_loginWidget);
    _tcp->openConnection();
    connect(_tcp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenTcpData()));
    connect(_loginWidget->getButton(), SIGNAL(clicked()), this,  SLOT(sendTcpLoginForm()));
    _window->show();
}
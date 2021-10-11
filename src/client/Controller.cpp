/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#include "Controller.hpp"

Controller::Controller(int port, char *ip)
{
    srand(time(NULL));
    _window = new QMainWindow();
    _window->setWindowTitle("Babel Voice Client");
    _window->resize(QSize(650, 385));
    _hubWidget = new HubWidget();
    _loginWidget = new LoginWidget();
    _signUpWidget = new SignUpWidget();
    _tcp = new MyTCP(ip, port);
    _error = nullptr;
    _inCall = false;

    _answerBox = new QMessageBox(_window);
    _pButtonYes = _answerBox->addButton(tr("Yes"), QMessageBox::YesRole);
    _answerBox->addButton(tr("No"), QMessageBox::NoRole);

    _callBox = new QMessageBox(_window);
    _pButtonHangUp = _callBox->addButton(tr("Hang up"), QMessageBox::NoRole);

    _signSuccess = new QMessageBox(_window);
    _pButtonBack = _signSuccess->addButton(tr("Thanks!"), QMessageBox::NoRole);
    _signSuccess->setWindowTitle("Welcome!");
    _signSuccess->setText("You're now signed up!");

    QFont font;
    font.setPointSize(14);
    _answerBox->setFont(font);
    _callBox->setFont(font);
    _signSuccess->setFont(font);
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
    Message loginForm = _loginWidget->getLoginForm();
    if (loginForm.getHeader().toStdString() == "ERROR") {
        _error = new ErrorWidget("'SPACE' isn't allowed.", "Error", _window);
        _error->show();
        return;
    }
    _tcp->writeData(loginForm);
}

void Controller::callSelected()
{
    int selected = _hubWidget->getSelected();
    if (selected == -1) {
        _error = new ErrorWidget("No user selected.", "Error", _window);
        _error->show();
    }
    else {
        _readPort = 1024 + rand() % 64512;
        _callUsername = _hubWidget->getSelectedName();
        _tcp->writeData(Message((std::to_string(_readPort) + " " + _callUsername).c_str(), std::to_string(REQUEST_CALL).c_str()));
    }
}

void Controller::acceptedResponse()
{
    _readPort = 1024 + rand() % 64512;
    _tcp->writeData(Message((std::to_string(_readPort) + " " + _callUsername).c_str(), std::to_string(USERCALLBACKRESPONSE).c_str()));
}

void Controller::refusedResponse()
{
    _tcp->writeData(Message(_callUsername.c_str(), std::to_string(CALLREFUSED).c_str()));
}

void Controller::hangUp()
{
    _tcp->writeData(Message(_callUsername.c_str(), std::to_string(CALLHANGUP).c_str()));
    _inCall = false;
}

void Controller::responseSelector(std::string response)
{
    int code = std::atoi(response.substr(0, response.find(' ')).c_str());
    response.erase(0, response.find(' ') + 1);
    if (code == PING_IP)
        _readIp = response;
    if (code == CO_ERROR) {
        _error = new ErrorWidget("Login failed.", "Error", _window);
        _error->show();
    }
    if (code == SIGN_UP_OK) {
        _signSuccess->show();
        connect(_signSuccess, SIGNAL(rejected()), this,  SLOT(loginWidget()));
    }
    if (code == SIGN_UP_ALREADY_EXIST) {
        _error = new ErrorWidget("User already exist.", "Error", _window);
        _error->show();
    }
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
    if (code == ERROR) {
        _error = new ErrorWidget("Already connected.", "Error", _window);
        _error->show();
    }
    if (code == PARSE_ERROR) {
        _error = new ErrorWidget("Sorry an error occured.", "Error", _window);
        _error->show();
    }
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
        _answerBox->setWindowTitle((_callUsername + " is calling!").c_str());
        _answerBox->setText("Answer?");
        _answerBox->show();
        connect(_answerBox, SIGNAL(accepted()), this,  SLOT(acceptedResponse()));
        connect(_answerBox, SIGNAL(rejected()), this,  SLOT(refusedResponse()));
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
        _callBox->setWindowTitle("Communication");
        _callBox->setText(("In call with " + _callUsername).c_str());
        _callBox->show();
        connect(_callBox, SIGNAL(rejected()), this,  SLOT(hangUp()));
        _inCall = true;
        sendUdpData();
    }
    if (code == CALL_CONFIRMATION) {
        _readUdp = new MyUDP(_readIp, _readPort);
        _readUdp->openConnection();
        connect(_readUdp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenUdpData()));
        _writeUdp = new MyUDP(_writeIp, _writePort);
        _writeUdp->openConnection();
        _callBox->setWindowTitle("Communication");
        _callBox->setText(("In call with " + _callUsername).c_str());
        _callBox->show();
        connect(_callBox, SIGNAL(rejected()), this,  SLOT(hangUp()));
        _inCall = true;
        sendUdpData();
    }
    if (code == CALLREFUSED) {
        _error = new ErrorWidget(_callUsername + " refused to answer", "Error", _window);
        _error->show();
    }
    if (code == ALREADYINCALL) {
        _error = new ErrorWidget(_callUsername + " already in call", "Error", _window);
        _error->show();
    }
    if (code == CALLHANGUP) {
        _callBox->hide();
        _inCall = false;
    }
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

void Controller::signUpWidget()
{
    _signUpWidget = new SignUpWidget();
    _window->setCentralWidget(_signUpWidget);
    connect(_signUpWidget->getBackButton(), SIGNAL(clicked()), this,  SLOT(loginWidget()));
    connect(_signUpWidget->getValidateButton(), SIGNAL(clicked()), this,  SLOT(sendTcpSignUpForm()));
}

void Controller::loginWidget()
{
    _loginWidget = new LoginWidget();
    _window->setCentralWidget(_loginWidget);
    connect(_loginWidget->getLoginButton(), SIGNAL(clicked()), this,  SLOT(sendTcpLoginForm()));
    connect(_loginWidget->getSignUpButton(), SIGNAL(clicked()), this,  SLOT(signUpWidget()));
}

void Controller::sendTcpSignUpForm()
{
    Message SignUpForm = _signUpWidget->getSignUpForm();
    if (SignUpForm.getHeader().toStdString() == "SPACE") {
        _error = new ErrorWidget("'SPACE' isn't allowed.", "Error", _window);
        _error->show();
        return;
    }
    if (SignUpForm.getHeader().toStdString() == "EMPTY") {
        _error = new ErrorWidget("A field is empty.", "Error", _window);
        _error->show();
        return;
    }
    if (SignUpForm.getHeader().toStdString() == "MISMATCH") {
        _error = new ErrorWidget("Passwords mismatch.", "Error", _window);
        _error->show();
        return;
    }
    _tcp->writeData(SignUpForm);
}

void Controller::startBabel()
{
    _window->setCentralWidget(_loginWidget);
    _tcp->openConnection();
    connect(_tcp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenTcpData()));
    connect(_loginWidget->getLoginButton(), SIGNAL(clicked()), this,  SLOT(sendTcpLoginForm()));
    connect(_loginWidget->getSignUpButton(), SIGNAL(clicked()), this,  SLOT(signUpWidget()));
    connect(_signUpWidget->getBackButton(), SIGNAL(clicked()), this,  SLOT(loginWidget()));
    connect(_signUpWidget->getValidateButton(), SIGNAL(clicked()), this,  SLOT(sendTcpSignUpForm()));
    _window->show();
}
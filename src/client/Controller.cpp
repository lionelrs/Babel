/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#include "Controller.hpp"

Controller::Controller(Window *w, MyUDP *writeUdp, MyUDP *readUdp) : _w(w), _writeUdp(writeUdp), _readUdp(readUdp)
{
    connect(_w->getButton(), SIGNAL(clicked()), this, SLOT(sendData()));
    connect(_readUdp->getSocket(), SIGNAL(readyRead()), this, SLOT(listenData()));

}

Controller::~Controller()
{
}

void Controller::sendData()
{
    Message msg = _w->setAndGetThisMessage();
    _writeUdp->writeData(msg);
}

void Controller::listenData()
{
    _readUdp->readData();
}

void Controller::loginToServ()
{

}

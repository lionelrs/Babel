/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#include "Controller.hpp"

Controller::Controller(Window *w, MyUDP *udp) : _w(w), _udp(udp)
{
    connect(_w->getButton(), SIGNAL(clicked()), this, SLOT(communicate()));
}

Controller::~Controller()
{
}

void Controller::communicate()
{
    Message msg = _w->setAndGetThisMessage();
    _udp->sendData(msg);
}

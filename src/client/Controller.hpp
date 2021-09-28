/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "MyUDP.hpp"
#include "Window.hpp"

class Controller : public QObject {
        Q_OBJECT
    public:
        Controller(Window *w, MyUDP *writeUdp, MyUDP *readUdp);
        ~Controller();

    public slots:
        void sendData();
        void listenData();
        void loginToServ();

    protected:
    private:
        MyUDP *_readUdp;
        MyUDP *_writeUdp;
        Window *_w;

};

#endif /* !CONTROLLER_HPP_ */

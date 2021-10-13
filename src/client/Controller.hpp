/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** Controller
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <QMainWindow>

#include <unistd.h>
#include "MyUDP.hpp"
#include "MyTCP.hpp"
#include "LoginWidget.hpp"
#include "ErrorWidget.hpp"
#include "HubWidget.hpp"
#include "SignUpWidget.hpp"
#include "../common/PortAudio.hpp"
#include "../common/Parser.hpp"

class Controller : public QObject {
        Q_OBJECT
    public:
        Controller(int port, char *ip);
        ~Controller();

        void startBabel();
        void sendUdpData(Message msg);

    signals:
    public slots:
        void listenTcpData();
        void listenUdpData();
        void sendTcpLoginForm();
        void callSelected();
        void acceptedResponse();
        void refusedResponse();
        void hangUp();
        void signUpWidget();
        void loginWidget();
        void sendTcpSignUpForm();

    protected:
    private:
        QMainWindow *_window;
        LoginWidget *_loginWidget;
        SignUpWidget *_signUpWidget;
        HubWidget *_hubWidget;
        ErrorWidget *_error;

        MyUDP *_readUdp;
        int _readPort;
        std::string _readIp;
        MyUDP *_writeUdp;
        int _writePort;
        std::string _writeIp;
        bool _inCall;

        Parser *_parser;

        MyTCP *_tcp;

        Babel::IAudio *_recorder;
        Babel::IAudio *_player;

        QMessageBox *_answerBox;
        QAbstractButton *_pButtonYes;

        QMessageBox *_callBox;
        QAbstractButton *_pButtonHangUp;

        QMessageBox *_signSuccess;
        QAbstractButton *_pButtonBack;

        std::string _myUsername;
        std::string _callUsername;

        void responseSelector(std::string response);

};

#endif /* !CONTROLLER_HPP_ */

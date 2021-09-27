/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** main
*/

#include <iostream>
#include <unistd.h>
#include <QApplication>

#include "Message.hpp"
#include "Window.hpp"
#include "Controller.hpp"
#include "MyUDP.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window;
    MyUDP writeUdp("10.16.253.70", 1234);
    MyUDP readUdp("10.16.252.186", 4321);
    Controller controller(&window, &writeUdp, &readUdp);

    QStringList headers;
    headers << "Babel";
    QString body = "This is a test.\r\n";

    Message message(body, headers);
    window.setMessage(message);
    window.show();

    return app.exec();
}
/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** main
*/

#include <iostream>
#include <QApplication>
#include "Message.hpp"
#include "Window.hpp"
#include "Controller.hpp"
#include "MyUDP.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyUDP udp;
    Window window;
    QStringList headers;
    Controller controller(&window, &udp);
    headers << "Subject: Hello World"
            << "From: qt-info@nokia.com";
    QString body = "This is a test.\r\n";

    Message message(body, headers);
    window.setMessage(message);
    window.show();

    return app.exec();
}
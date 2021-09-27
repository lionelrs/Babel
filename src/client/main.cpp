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
#include "MyUDP.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window1;
    QStringList headers;
    headers << "Subject: Hello World"
            << "From: qt-info@nokia.com";
    QString body = "This is a test.\r\n";
    Message message(body, headers);
    window1.setMessage(message);

    Window window2;
    QObject::connect(&window1, SIGNAL(messageSent(Message)),
                     &window2, SLOT(setMessage(Message)));
    QObject::connect(&window2, SIGNAL(messageSent(Message)),
                     &window1, SLOT(setMessage(Message)));
    window1.show();
    window2.show();

    return app.exec();
}
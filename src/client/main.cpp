/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** main
*/

#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include "MyUDP.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
        QApplication::translate("fiak", "Top-level widget"));

    MyUDP client;
	client.sendData();

    return app.exec();
}
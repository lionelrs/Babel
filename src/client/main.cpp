/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** main
*/

#include <QApplication>

#include "Controller.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Controller controller;
    controller.startBabel();

    return app.exec();
}
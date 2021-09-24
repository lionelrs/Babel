/*
** EPITECH PROJECT, 2021
** 
** File description:
** 
*/

#include <QCoreApplication>
#include "MyUDP.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    MyUDP client;
    
    client.HelloUDP();
    
    return a.exec();
}
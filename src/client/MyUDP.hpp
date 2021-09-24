/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** MyUDP
*/

#ifndef MYUDP_HPP_
#define MYUDP_HPP_

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    //~MyUDP();
    void HelloUDP();
signals:
public slots:
    void readyRead();
private:
    QUdpSocket *socket;
};

#endif /* !MYUDP_HPP_ */

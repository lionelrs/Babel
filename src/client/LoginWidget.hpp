/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** LoginWidget
*/

#ifndef LOGINWIDGET_HPP_
#define LOGINWIDGET_HPP_

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

#include "Message.hpp"
#include "../common/SEPCommands.hpp"

class LoginWidget : public QWidget {
    Q_OBJECT
    public:
        LoginWidget(QWidget *parent = 0);
        ~LoginWidget();

        Message getLoginForm();
        QPushButton *getButton() const;

    signals:
    public slots:
    private slots:

    private:
        QLineEdit *_editUsername;
        QLineEdit *_editPassword;
        QPushButton *_loginButton;
};

#endif /* !LOGINWIDGET_HPP_ */
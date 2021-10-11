/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** SignUpWidget
*/

#ifndef SIGNUPWIDGET_HPP_
#define SIGNUPWIDGET_HPP_

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

#include "Message.hpp"
#include "../common/SEPCommands.hpp"

class SignUpWidget : public QWidget {
    public:
        Q_OBJECT
    public:
        SignUpWidget(QWidget *parent = 0);
        ~SignUpWidget();

        Message getSignUpForm();
        QPushButton *getValidateButton() const;
        QPushButton *getBackButton() const;

    signals:
    public slots:
    private slots:

    protected:
    private:
        QLineEdit *_editUsername;
        QLineEdit *_editPassword;
        QLineEdit *_editConfirmPassword;
        QPushButton *_validateButton;
        QPushButton *_backButton;

    protected:
    private:
};

#endif /* !SIGNUPWIDGET_HPP_ */

/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** LoginWidget
*/

#include "LoginWidget.hpp"

LoginWidget::LoginWidget(QWidget *parent)
{
    QGroupBox *groupBox = new QGroupBox("Sign In", parent);

    QVBoxLayout *outterLayout = new QVBoxLayout(this);
    outterLayout->addWidget(groupBox);

    QLabel *usernameLabel = new QLabel("Username", groupBox);
    _editUsername = new QLineEdit();
    QLabel *passwordLabel = new QLabel("Password", groupBox);
    _editPassword = new QLineEdit();
    _editPassword->setEchoMode(QLineEdit::Password);
    _loginButton = new QPushButton("Login");

    QVBoxLayout *innerLayout = new QVBoxLayout(groupBox);
    innerLayout->addWidget(usernameLabel, 0, Qt::AlignTop);
    innerLayout->addWidget(_editUsername, 1, Qt::AlignTop);
    innerLayout->addWidget(passwordLabel);
    innerLayout->addWidget(_editPassword);

    innerLayout->addWidget(_loginButton, 1, Qt::AlignBottom);
    outterLayout->setContentsMargins(QMargins(10, 0, 10, 10));
    innerLayout->setContentsMargins(QMargins(50, 50, 50, 50));

    QFont font;
    font.setPointSize(14);
    usernameLabel->setFont(font);
    groupBox->setFont(font);
    passwordLabel->setFont(font);
    _loginButton->setFont(font);
}

LoginWidget::~LoginWidget()
{
}

Message LoginWidget::getLoginForm()
{
    return Message(_editUsername->text() + " " + _editPassword->text(), std::to_string(REQUEST_CO).c_str());
}

QPushButton *LoginWidget::getButton() const
{
    return _loginButton;
}
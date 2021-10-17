/*
** EPITECH PROJECT, 2021
** B-CPP-500-NCE-5-1-babel-lionel.da-rocha-da-silva
** File description:
** LoginWidget
*/

#include "LoginWidget.hpp"

/**
 * Creates an instance of LoginWidget that display the login form.
 *
 * @param parent Parent widget to herit from.
 */
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
    _signUpButton = new QPushButton("Sign Up");

    QVBoxLayout *innerLayout = new QVBoxLayout(groupBox);
    innerLayout->addWidget(usernameLabel);
    innerLayout->addWidget(_editUsername);
    innerLayout->addWidget(passwordLabel);
    innerLayout->addWidget(_editPassword, 1, Qt::AlignTop);
    innerLayout->addWidget(_loginButton, 1, Qt::AlignBottom);
    innerLayout->addWidget(_signUpButton);

    outterLayout->setContentsMargins(QMargins(10, 0, 10, 10));
    innerLayout->setContentsMargins(QMargins(50, 50, 50, 50));

    QFont font;
    font.setPointSize(14);
    usernameLabel->setFont(font);
    groupBox->setFont(font);
    passwordLabel->setFont(font);
    _loginButton->setFont(font);
    _signUpButton->setFont(font);
}

LoginWidget::~LoginWidget()
{
}

/**
 * Getter of the filled form.
 */
Message LoginWidget::getLoginForm()
{
    if (_editUsername->text().toStdString().find(' ') != std::string::npos)
        return Message("FORBIDDEN CHARACTER", "ERROR");
    if (_editPassword->text().toStdString().find(' ') != std::string::npos)
        return Message("FORBIDDEN CHARACTER", "ERROR");
    return Message(_editUsername->text() + " " + _editPassword->text(), std::to_string(REQUEST_CO).c_str());
}

/**
 * Getter of the login button.
 */
QPushButton *LoginWidget::getLoginButton() const
{
    return _loginButton;
}

/**
 * Getter of the sign up button.
 */
QPushButton *LoginWidget::getSignUpButton() const
{
    return _signUpButton;
}